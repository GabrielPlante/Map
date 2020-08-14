#include "WaterSystem.h"

#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/Vector2.h"

#include "GraphicSystem.h"
#include "HexagonalMap.h"
#include "MapStorage.h"
#include "MapValues.h"

//The percentage of water that will leave this tile if other tiles are below this one (between 0 and 1)
constexpr float waterLostByTicks{ 0.25f };

//The minimum height two neighbor tiles must have for the water to flow between them
constexpr int minHeightDiffForFlow{ 0 };

//The time between two update of the water system that handle the water flow in microsecond
constexpr long long timeBetweenWaterUpdate{ 300 * 1000 };


//The amount of water a tile with water on it lose each tick
constexpr float waterEvaporationRate{ 0.005f };

namespace map {
	void applyWaterFlow(const float waterChange, std::vector<std::vector<float>>* humidityChangeMap, ge::Vector2<int> neighborPosition
		, ge::Vector2<int> tilePosition) {
		//Apply the water change on the temporary map
		//First apply the change to the neighbor tile
		(*humidityChangeMap)[neighborPosition.x][neighborPosition.y] += waterChange;
		//Then apply the change of this tile
		(*humidityChangeMap)[tilePosition.x][tilePosition.y] -= waterChange;
	}

	void WaterSystem::update() {
		timeSinceLastUpdate += ge::Engine::getInstance()->getTimeSinceLastFrame();

		//If it is time to update the water
		if (timeSinceLastUpdate > timeBetweenWaterUpdate) {
			//Update the timer
			timeSinceLastUpdate -= timeBetweenWaterUpdate;

			bool changeInMap{ false };

			//A temporary map to apply all the change at the same time (after everything is calculated)
			std::vector<std::vector<float>> waterChangeMap;

			//Fill the temporary change map
			MapStorage storage;
			for (auto it = storage.getBeginningIterator(); !it.endReached(); it++) {
				while (it.getPosition().x >= waterChangeMap.size()) {
					waterChangeMap.push_back(std::vector<float>{});
				}
				while (it.getPosition().y >= waterChangeMap[it.getPosition().x].size()) {
					waterChangeMap[it.getPosition().x].push_back(0);
				}
			}

			for (auto it = storage.getBeginningIterator(); !it.endReached(); it++) {
				//First, handle the water flow due to the height
				//If there is water above the tile
				if (it->water > 0) {
					//Handle the evaporation
					waterChangeMap[it.getPosition().x][it.getPosition().y] -= waterEvaporationRate;

					//Get the neighbors from the map with their position
					auto neighbors{ HexagonalMap{}.getNeighborsWithPos(it.getPosition()) };

					//The tile height accounting the water
					const int tileRealHeight{ it->realheight() };

					//The water present on the tile that will be lost
					const float tileWater{ (it->water + 0.05f) * waterLostByTicks };

					//The vector contain the real height (with the water accounted) of every neighbor, and it's position
					std::vector<std::pair<int, int>> neighborsHeight;

					//Check how much water will be distributed to the neighbors
					int totalHeightBelow{ 0 };
					for (int i = 0; i != neighbors.size(); i++) {
						//Find the real height of the neighbor
						int neighborHeight{ neighbors[i].second->realheight() };
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
						for (int i = 0; i != neighborsHeight.size(); i++) {
							//The water that will flow from the tile to the neighbors tile
							float waterChange{ static_cast<float>(tileRealHeight - neighborsHeight[i].second) * tileWater / totalHeightBelow };
							//If the height of the water that will flow to the neighbor tile is superior to the difference of height between the two tile
							if (waterChange * waterToHeight * 2 > tileRealHeight - neighborsHeight[i].second) {
								//Apply a diminished water to avoid the water returning to this tile on the next iteration
								applyWaterFlow((tileRealHeight - neighborsHeight[i].second) / waterToHeight / 2, &waterChangeMap, neighbors[neighborsHeight[i].first].first, it.getPosition());
							}
							//Else apply normal water flow
							else {
								//Apply the water change on the temporary map
								applyWaterFlow(waterChange, &waterChangeMap, neighbors[neighborsHeight[i].first].first, it.getPosition());
							}

							changeInMap = true;
						}
					}
				}
			}
			//Apply the change on the real map
			for (int i = 0; i != waterChangeMap.size(); i++) {
				for (int j = 0; j != waterChangeMap[i].size(); j++) {
					if (waterChangeMap[i][j] != 0) {
						storage.modifyTile({ i, j })->water += waterChangeMap[i][j];
						//The water of a tile cannot go below 0
						if (storage.getTile({ i, j }).water < 0)
							storage.modifyTile({ i, j })->water = 0;
					}
				}
			}

			//If there is change in the map, notify the graphic system to re generate the map
			if (changeInMap) {
				GraphicSystem::needGenerateMap();
			}
		}
	}
}
