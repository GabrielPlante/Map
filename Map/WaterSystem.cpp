#include "WaterSystem.h"

#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/Vector2.h"

#include "GraphicSystem.h"
#include "HexagonalMap.h"
#include "MapStorage.h"
#include "MapValues.h"

#include <iostream>

//The percentage of water that will leave this tile if other tiles are below this one (between 0 and 1)
constexpr float waterLostByTicks{ 0.25f };

//The minimum height two neighbor tiles must have for the water to flow between them
constexpr int minHeightDiffForFlow{ 0 };

//The rate at wich the water erode the height of a tile. If the rate is 10, for each 0.1 of water, it will erode 1 height of the tile.
//constexpr float waterErosionRate{ 10 };

//The time between two update of the water system that handle the water flow in microsecond
constexpr long long timeBetweenWaterUpdate{ 300 * 1000 };


//The amount of humidity that goes from a water tile to a dry neighbor tile each tick
constexpr float waterToDryHumidityFlow{ 0.01f };

//The percent of humidity that goes from a dry tile to a dry neighbor tile each tick
constexpr float dryToDryHumidityFlowPercent{ 0.01f };

//The amount of water a tile with water on it lose each tick
constexpr float waterEvaporationRate{ 0.005f };

//The amount of humidity a dry tile lose each tick
constexpr float humidityDissipationRate{ 0.002f };

namespace map {
	void applyWaterFlow(const float waterChange, std::map<ge::Vector2<int>, float>* humidityChangeMap, ge::Vector2<int> neighborPosition
		, ge::Vector2<int> tilePosition) {
		//Apply the water change on the temporary map
		//First apply the change to the neighbor tile
		humidityChangeMap->find(neighborPosition)->second += waterChange;
		//Then apply the change of this tile
		humidityChangeMap->find(tilePosition)->second -= waterChange;
	}

	void WaterSystem::update() {
		timeSinceLastUpdate += ge::Engine::getInstance()->getTimeSinceLastFrame();

		//If it is time to update the water
		if (timeSinceLastUpdate > timeBetweenWaterUpdate) {
			//Update the timer
			timeSinceLastUpdate -= timeBetweenWaterUpdate;

			bool changeInMap{ false };

			//A temporary map to apply all the change at the same time (after everything is calculated)
			std::map<ge::Vector2<int>, float> humidityChangeMap;

			//Fill the humidity change map
			MapStorage storage;
			for (auto it = storage.getBeginningIterator(); it != storage.getEndIterator(); it++) {
				humidityChangeMap.insert(std::make_pair(it->first, 0.0f));
			}

			for (auto it = storage.getBeginningIterator(); it != storage.getEndIterator(); it++) {
				//First, handle the water flow due to the height
				//If there is water above the tile
				if (it->second.humidity > 1) {
					//Handle the evaporation
					humidityChangeMap.find(it->first)->second -= waterEvaporationRate;

					//Get the neighbors from the map with their position
					auto neighbors{ HexagonalMap{}.getNeighborsWithPos(it->first) };

					//The tile height accounting the water
					const int tileRealHeight{ it->second.realheight() };

					//The water present on the tile that will be lost
					const float tileWater{ (it->second.humidity - minWaterLevel + 0.05f) * waterLostByTicks };

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
						//If the neighbor is a dry tile and no water will flow to this tile and the tile will not overflow
						else if (neighbors[i].second->humidity + humidityChangeMap.find(neighbors[i].first)->second < 1 - waterToDryHumidityFlow) {
							//Add the humidity given to the neighbor
							humidityChangeMap.find(neighbors[i].first)->second += waterToDryHumidityFlow;
							//Substract the humidity lost by this tile
							humidityChangeMap.find(it->first)->second -= waterToDryHumidityFlow;
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
								applyWaterFlow((tileRealHeight - neighborsHeight[i].second) / waterToHeight / 2, &humidityChangeMap, neighbors[neighborsHeight[i].first].first, it->first);
							}
							//Else apply normal water flow
							else {
								//Apply the water change on the temporary map
								applyWaterFlow(waterChange, &humidityChangeMap, neighbors[neighborsHeight[i].first].first, it->first);
							}

							changeInMap = true;
						}
					}
				}
				//Handle the humidity change of a dry tile
				else if (it->second.humidity > 0) {
					//Handle the dissipation 
					humidityChangeMap.find(it->first)->second -= humidityDissipationRate;

					//Get the neighbors from the map with their position
					auto neighbors{ HexagonalMap{}.getNeighborsWithPos(it->first) };

					for (int i = 0; i != neighbors.size(); i++) {
						//If the neighbor have less humidity than this tile and the tile will not overflow due to the transfert of humidity
						if (neighbors[i].second->humidity < it->second.humidity
							&& neighbors[i].second->humidity + humidityChangeMap.find(neighbors[i].first)->second < 1 - dryToDryHumidityFlowPercent * it->second.humidity) {
							//Add the humidity given to the neighbor
							humidityChangeMap.find(neighbors[i].first)->second += dryToDryHumidityFlowPercent * it->second.humidity;
							//Substract the humidity lost by this tile
							humidityChangeMap.find(it->first)->second -= dryToDryHumidityFlowPercent * it->second.humidity;
						}
					}
				}
			}
			//Apply the change on the real map
			for (auto it = humidityChangeMap.begin(); it != humidityChangeMap.end(); it++) {
				storage.modifyTile(it->first)->humidity += it->second;
				//The humidity of a tile cannot go below 0
				if (storage.getTile(it->first).humidity < 0)
					storage.modifyTile(it->first)->humidity = 0;
			}

			//If there is change in the map, notify the graphic system to re generate the map
			if (changeInMap) {
				GraphicSystem::needGenerateMap();
			}
		}
	}
}
