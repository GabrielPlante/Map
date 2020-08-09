#include "RainSystem.h"
#include <stdlib.h>

#include "../GameEngine2D/Engine.h"

#include "MapStorage.h"

#include <iostream>

//The time between two update of the rain system that handle the rain in microsecond
constexpr long long timeBetweenRainUpdate{ 300 * 1000 };

//The maximum rain fall for a tick, divided by 1000
constexpr int maxRainFall{ 100 };

constexpr int maxTimeWithoutRain{ 200 };
constexpr int maxTimeWithRain{ 50 };

namespace map {
	void RainSystem::update() {
		//Update the timer
		/*timeSinceLastUpdate += ge::Engine::getInstance()->getTimeSinceLastFrame();

		//If it is time to update the rain
		if (timeSinceLastUpdate > timeBetweenRainUpdate) {
			//Update the timer
			timeSinceLastUpdate -= timeBetweenRainUpdate;

			//If it is raining
			if (rainDuration > 0) {
				rainDuration--;

				//Make the rain fall on every tile
				MapStorage storage;
				for (auto it = storage.getBeginningIterator(); it != storage.getEndIterator(); it++) {
					it->second.humidity += rainIntensity;
				}
			}
			//If it is not raining
			else if (rainDuration < -1) {
				rainDuration++;
			}
			//If the rain just finished, determine the time without rain
			else if (rainDuration == 0){
				rainDuration = -(rand() % maxTimeWithoutRain) - 1;
				std::cout << "Rain stop for " << abs(rainDuration) << std::endl;
			}
			//If it is time to rain again
			else if (rainDuration == -1) {
				rainDuration = rand() % maxTimeWithRain + 1;
				rainIntensity = static_cast<float>(rand() % maxRainFall) / 1000.0f;
				std::cout << "Rain start for " << rainDuration << " with intensity " << rainIntensity << std::endl;
			}
		}*/
	}
}
