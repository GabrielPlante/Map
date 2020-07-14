#include "WaterSystem.h"

#include "../GameEngine2D/Engine.h"

#include "GraphicSystem.h"
#include "HexagonalMap.h"
#include "MapStorage.h"
#include "MapValues.h"

#include <iostream>

//The percentage of water that will leave this tile if other tiles are below this one (between 0 and 1)
constexpr float waterLostByTicks{ 0.25f };

//The multiplicator of the level of water to the height of the water (if humidity is 1.5, water level is 0.5, height is 0.5 * waterToHeight + the height of the tile
constexpr float waterToHeight{ 3 };

//The minimum height two neighbor tiles must have for the water to flow between them
constexpr int minHeightDiffForFlow{ 1 };

namespace map {
	void applyWaterFlow(const float waterChange, std::map<ge::Vector2<int>, float>* humidityChangeMap, std::vector<std::pair<ge::Vector2<int>, TileComponent*>>* neighbors,
		const std::vector<std::pair<int, int>>& neighborsHeight, int i, const std::pair<ge::Vector2<int>, TileComponent>& it) {
		//Apply the water change on the temporary map
		//First apply the change to the neighbor tile
		if (humidityChangeMap->find((*neighbors)[neighborsHeight[i].first].first) == humidityChangeMap->end())
			humidityChangeMap->insert(std::make_pair((*neighbors)[neighborsHeight[i].first].first, waterChange));
		else
			humidityChangeMap->find((*neighbors)[neighborsHeight[i].first].first)->second += waterChange;
		//Then apply the change of this tile
		if (humidityChangeMap->find(it.first) == humidityChangeMap->end())
			humidityChangeMap->insert(std::make_pair(it.first, -waterChange));
		else
			humidityChangeMap->find(it.first)->second -= waterChange;
	}

	void WaterSystem::update() {
		timeSinceLastUpdate += ge::Engine::getInstance()->getTimeSinceLastFrame();

		//If it is time to update the water
		if (timeSinceLastUpdate > mv::timeBetweenWaterUpdate) {
			//Update the timer
			timeSinceLastUpdate -= mv::timeBetweenWaterUpdate;

			bool changeInMap{ false };
			int nbrOfChange{ 0 };

			//A temporary map to apply all the change at the same time (after everything is calculated)
			std::map<ge::Vector2<int>, float> humidityChangeMap;

			MapStorage storage;
			for (auto it = storage.getBeginningIterator(); it != storage.getEndIterator(); it++) {
				//First, handle the water flow due to the height
				//If there is water above the tile
				if (it->second.humidity > 1) {
					//Get the neighbors from the map with their position
					auto neighbors{ HexagonalMap{}.getNeighborsWithPos(it->first) };

					//The tile height accounting the water
					const int tileRealHeight{ it->second.height + static_cast<int>((it->second.humidity - mv::minWaterLevel) * waterToHeight) };

					//The water present on the tile that will be lost
					const float tileWater{ (it->second.humidity - mv::minWaterLevel + 0.05f) * waterLostByTicks };

					//The vector contain the real height (with the water accounted) of every neighbor, and it's position
					std::vector<std::pair<int, int>> neighborsHeight;

					//Check how much water will be distributed to the neighbors
					int totalHeightBelow{ 0 };
					for (int i = 0; i != neighbors.size(); i++) {
						//Find the real height of the neighbor
						int neighborHeight;
						if (neighbors[i].second->humidity > 1)
							neighborHeight = neighbors[i].second->height + static_cast<int>((neighbors[i].second->humidity - mv::minWaterLevel) * waterToHeight);
						else
							neighborHeight = neighbors[i].second->height;
						//Check if the neighbor is below this tile
						if (neighborHeight + minHeightDiffForFlow < tileRealHeight) {
							//Add it's height to the total
							totalHeightBelow += tileRealHeight - neighborHeight;
							//Add it to the list of neighbors below the tile
							neighborsHeight.push_back(std::make_pair(i, neighborHeight));
						}
					}
					//If there are tiles below this one
					if (totalHeightBelow != 0) {
						//Distribute the water
						//If there is only one neighbor below this one, treat it separatly
						if (neighborsHeight.size() == 1) {
							//The water that will flow from the tile to the neighbor tile
							float waterChange{ static_cast<float>(tileRealHeight - neighborsHeight[0].second) * tileWater / totalHeightBelow };
							//If the height of the water that will flow to the neighbor tile is superior to the difference of height between the two tile
							if (waterChange * waterToHeight > totalHeightBelow + minHeightDiffForFlow) {
								//Apply a diminished water to avoid the water returning to this tile on the next iteration
								applyWaterFlow(static_cast<float>(totalHeightBelow / waterToHeight), &humidityChangeMap, &neighbors, neighborsHeight, 0, (*it));
							}
							//Else apply normal water flow
							else {
								applyWaterFlow(waterChange, &humidityChangeMap, &neighbors, neighborsHeight, 0, (*it));
							}
						}
						//Else handle the other normally
						else {
							for (int i = 0; i != neighborsHeight.size(); i++) {
								//The water that will flow from the tile to the neighbors tile
								float waterChange{ static_cast<float>(tileRealHeight - neighborsHeight[i].second) * tileWater / totalHeightBelow };
								//Apply the water change on the temporary map
								applyWaterFlow(waterChange, &humidityChangeMap, &neighbors, neighborsHeight, i, (*it));

								changeInMap = true;
								nbrOfChange++;
							}
						}
					}
				}
			}
			//Apply the change on the real map
			for (auto it = humidityChangeMap.begin(); it != humidityChangeMap.end(); it++) {
				storage.modifyTile(it->first)->humidity += it->second;
			}

			//If there is change in the map, notify the graphic system to re generate the map
			if (changeInMap) {
				GraphicSystem::needGenerateMap();
				std::cout << nbrOfChange << std::endl;
			}
		}
	}
}
