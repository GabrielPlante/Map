#include "HumiditySystem.h"

#include "../GameEngine2D/Engine.h"

#include "HexagonalMap.h"
#include "MapStorage.h"

//The time between two update of the water system that handle the water flow in microsecond
constexpr long long timeBetweenHumidityUpdate{ 300 * 1000 };

//The amount of water a tile can absorb and convert into humidity each tick
constexpr float waterAbsorbtion{ 0.02f };
//The percent of humidity that goes from a dry tile to a dry neighbor tile each tick
constexpr float humidityFlowPercent{ 0.01f };
//The percent of humidity a dry tile lose each tick
constexpr float humidityDissipationPercent{ 0.01f };

namespace map {
	void HumiditySystem::update() {

		timeSinceLastUpdate += ge::Engine::getInstance()->getTimeSinceLastFrame();

		//If it is time to update the water
		if (timeSinceLastUpdate > timeBetweenHumidityUpdate) {
			//Update the timer
			timeSinceLastUpdate -= timeBetweenHumidityUpdate;

			//A temporary map to apply all the change at the same time (after everything is calculated)
			std::vector<std::vector<float>> humidityChangeMap;

			//Fill the temporary change map
			MapStorage storage;
			for (auto it = storage.getBeginningIterator(); !it.endReached(); it++) {
				while (it.getPosition().x >= humidityChangeMap.size()) {
					humidityChangeMap.push_back(std::vector<float>{});
				}
				while (it.getPosition().y >= humidityChangeMap[it.getPosition().x].size()) {
					humidityChangeMap[it.getPosition().x].push_back(0);
				}
			}


			for (auto it = storage.getBeginningIterator(); !it.endReached(); it++) {
				//First handle the water absorption
				if (it->water >= waterAbsorbtion) {
					humidityChangeMap[it.getPosition().x][it.getPosition().y] += waterAbsorbtion;
					//Change directly the water as we will not be touching it later
					it->water -= waterAbsorbtion;
				}
				//Else if the tile does have water but in little quantity
				else if (it->water > 0) {
					humidityChangeMap[it.getPosition().x][it.getPosition().y] += it->water;
					it->water = 0;
				}
				//If the tile does not have water above it, some of it's humidity disappear
				else {
					humidityChangeMap[it.getPosition().x][it.getPosition().y] -= humidityDissipationPercent * it->humidity;
				}

				//Handle the humidity given to the neighbors tile
				auto neighbors{ HexagonalMap{}.getNeighborsWithPos(it.getPosition()) };
				for (auto jt = neighbors.begin(); jt != neighbors.end(); jt++) {
					//If this tile got more humidity than it's neighbor, make the humidity flow between the two tile
					if (it->humidity > jt->second->humidity) {
						humidityChangeMap[it.getPosition().x][it.getPosition().y] -= humidityFlowPercent * it->humidity;
						humidityChangeMap[jt->first.x][jt->first.y] += humidityFlowPercent * it->humidity;
					}
				}
			}

			//Apply the change on the real map
			for (int i = 0; i != humidityChangeMap.size(); i++) {
				for (int j = 0; j != humidityChangeMap[i].size(); j++) {
					if (humidityChangeMap[i][j] != 0) {
						storage.modifyTile({ i, j })->humidity += humidityChangeMap[i][j];
						//The humidity of a tile cannot go below 0 or above 1
						if (storage.getTile({ i, j }).humidity < 0)
							storage.modifyTile({ i, j })->humidity = 0;
						else if (storage.getTile({ i, j }).humidity > 1) {
							//The surplus goes into the water
							storage.modifyTile({ i, j })->water += storage.getTile({ i, j }).humidity - 1;
							storage.modifyTile({ i, j })->humidity = 1;
						}
					}
				}
			}
		}
	}
}
