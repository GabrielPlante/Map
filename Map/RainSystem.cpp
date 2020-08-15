#include "RainSystem.h"
#include <stdlib.h>

#include "../GameEngine2D/Engine.h"

#include "MapStorage.h"
#include "MapValues.h"
#include "Random.h"

#include <iostream>

/*
Water evaporation rate : 0.005
Humidity dissipation percent : 0.01
Wanted humidity average : 0.5
Wanted humidity average dissipation rate : 0.005
Wanted average rain : 0.005
*/

//The maximum rain fall for a tick, divided by 1000
constexpr int maxRainFall{ 40 };

constexpr int maxTimeWithoutRain{ 150 };
constexpr int maxTimeWithRain{ 50 };

constexpr bool disableRain{ false };

namespace map {
	void printStats() {
		MapStorage storage;
		double humiditySum{ 0 };
		double waterSum{ 0 };
		int tileSum{ 0 };
		for (auto it = storage.getBeginningIterator(); !it.endReached(); it++) {
			humiditySum += it->humidity;
			waterSum += it->water;
			tileSum++;
		}
		std::cout << " Average humidity: " << humiditySum / tileSum << " ; average water: " << waterSum / tileSum << std::endl;
	}

	void RainSystem::update() {
		//Update the timer
		timeSinceLastUpdate += ge::Engine::getInstance()->getTimeSinceLastFrame();

		//If it is time to update the rain
		if (timeSinceLastUpdate > mv::timeBetweenEnvironmentUpdate){
			//Update the timer
			timeSinceLastUpdate -= mv::timeBetweenEnvironmentUpdate;

			//If it is raining
			if (rainDuration > 0) {
				rainDuration--;

				//Make the rain fall on every tile
				MapStorage storage;
				for (auto it = storage.getBeginningIterator(); !it.endReached(); it++) {
					it->water += rainIntensity;
				}
			}
			//If it is not raining
			else if (rainDuration < -1) {
				rainDuration++;
			}
			//If the rain just finished, determine the time without rain
			else if (rainDuration == 0 && !disableRain){
				rainDuration = -(randomNumberHarmonised(maxTimeWithoutRain)) - 1;
				std::cout << "Rain stop for " << abs(rainDuration) << std::endl;
				printStats();
			}
			//If it is time to rain again
			else if (rainDuration == -1 && !disableRain) {
				rainDuration = randomNumberHarmonised(maxTimeWithRain) + 1;
				rainIntensity = static_cast<float>(randomNumberHarmonised(maxRainFall)) / 1000.0f;
				std::cout << "Rain start for " << rainDuration << " with intensity " << rainIntensity << std::endl;
				printStats();
			}
		}
	}
}
