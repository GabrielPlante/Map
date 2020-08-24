#include "FloraSystem.h"

#include "../GameEngine2D/Engine.h"

#include "HexagonalMap.h"
#include "FloraStorage.h"
#include "MapStorage.h"
#include "MapValues.h"

namespace map {
	//The humidity range of the plant
	constexpr float humidityRange{ 0.1f };
	//The amount of time the plant can survive outside it's humidity range
	constexpr int humiditySurvivalTime{ 10 };

	//The max water the plant can handle
	constexpr float maxWater{ 0.3f };
	//The amount of time the plant can survive above it's max water
	constexpr int waterSurvivalTime{ 10 };

	//The chance a plant have to invade a neigbor tile with good condition
	constexpr int percentOfReproduction{ 10 };
	//The chance a plant have to be invaded by common neighbor flora
	constexpr int nbrOfFloraToInvade{ 4 };

	/* A flora type and color is defined by it's humidity range
	 * For each flora, check the neighbor. Any neighbor without flora that fit the flora restriction have percentOfReproduction chance to be populated by that flora.
	 * Any flora with at leat nbrOfFloraToInvade neighbor of the same flora is invaded by that flora.
	*/

	void FloraSystem::update() {
		//Update the timer
		timeSinceLastUpdate += ge::Engine::getInstance()->getTimeSinceLastFrame();

		//If it is time to update the rain
		if (timeSinceLastUpdate > mv::timeBetweenEnvironmentUpdate) {
			//Update the timer
			timeSinceLastUpdate -= mv::timeBetweenEnvironmentUpdate;


			FloraStorage floraStorage;
			MapStorage storage;

			//First update the existing flora
			for (auto it = floraStorage.getBeginningIterator(); !it.endReached(); it++) {
				float tileHumidity{ storage.getTile(it.getPosition()).humidity };
				float tileWater{ storage.getTile(it.getPosition()).water };
				//Check if the humidity is within the restriction
				if (tileHumidity < it->humidityMargin.restriction.x || tileHumidity > it->humidityMargin.restriction.y) {
					//If it's not, update the flora
					it->humidityMargin.timeInSurvival++;
					//If the flora spent too much time outside it's restriction, it dies
					if (it->humidityMargin.timeInSurvival > it->humidityMargin.survivalTime) {
						floraStorage.deleteTile(it.getPosition());
						continue;
					}
				}
				//Else reset it's time spent outside it's survival zone
				else {
					it->humidityMargin.timeInSurvival = 0;
				}
				//Check if the water is below the restriction
				if (tileWater > it->maxWater.restriction) {
					//If not, update the flora
					it->maxWater.timeInSurvival++;
					//If the flora spent too much time outside it's restriction, it dies
					if (it->maxWater.timeInSurvival > it->maxWater.survivalTime) {
						floraStorage.deleteTile(it.getPosition());
						continue;
					}
				}
				//Else reset it's time spent outside it's survival zone
				else {
					it->maxWater.timeInSurvival = 0;
				}

				//Handle neighbors checking

				//The number of each of every type of neighbor
				std::map<ge::Vector2<float>, int> neighborsNbr;
				//Get the neighbors
				auto neighbors{ HexagonalMap{}.getNeighborsWithPos(it.getPosition()) };
				for (auto jt = neighbors.begin(); jt != neighbors.end(); jt++) {
					//If there is no flora on the neighbor, that it's humidity and water are within the margin of this plant, and the random work
					if (!floraStorage.floraExist(jt->first) && jt->second->humidity > it->humidityMargin.restriction.x && jt->second->humidity < it->humidityMargin.restriction.y
						&& jt->second->water < it->maxWater.restriction && rand() % 100 < percentOfReproduction) {
						//Copy the actual flora to it's neighbor
						FloraComponent flora{ *it };
						floraStorage.addFlora(jt->first, std::move(flora));
					}
					//Count the number of neighbors sharing the same type
					if (floraStorage.floraExist(jt->first)) {
						auto kt{ neighborsNbr.find(floraStorage.getTile(jt->first).humidityMargin.restriction) };
						if (kt != neighborsNbr.end())
							kt->second++;
						else
							neighborsNbr.insert(std::make_pair(floraStorage.getTile(jt->first).humidityMargin.restriction, 1));
					}
				}
				//If one of the species has enough neighbors to invade, then it invade the tile
				for (auto jt = neighborsNbr.begin(); jt != neighborsNbr.end(); jt++) {
					if (jt->second >= nbrOfFloraToInvade) {
						floraStorage.modifyTile(it.getPosition())->humidityMargin.restriction = jt->first;
						break;
					}
				}
			}

			//Get the tile randomly selected
			int tileToAddFlora{ rand() % mv::nbrOfTile };
			auto it{ storage.getBeginningIterator() };
			for (int i = 0; i < tileToAddFlora; i++) {
				it++;
			}
			//If there isn't already a tile here and there is no water
			if (!floraStorage.floraExist(it.getPosition()) && it->water == 0) {
				//Create the flora and add it
				FloraComponent flora{ FloraRestriction<ge::Vector2<float>>{ge::Vector2<float>{it->humidity - humidityRange / 2, it->humidity + humidityRange / 2}, humiditySurvivalTime},
				FloraRestriction<float>{maxWater, waterSurvivalTime} };
				floraStorage.addFlora(it.getPosition(), std::move(flora));
			}
		}
	}
}
