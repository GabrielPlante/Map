#include "MapGenerator.h"
#include <stdlib.h>
#include <time.h>

#include "MapTextureGenerator.h"
#include "TileComponent.h"
#include "HexagonalMap.h"
#include "MapValues.h"

namespace map {
	MapGenerator::MapGenerator(ge::Vector2<int> mapSize, unsigned int seed) {
		//Set the seed for the random number generator
		if (seed != 0)
			srand(seed);
		else {
			seed = static_cast<unsigned int>(time(NULL));
			srand(seed);
		}
		this->seed = seed;

		MapStorage storage;
		for (int i = 0; i != mapSize.y; i++) {
			for (int j = 0; j != mapSize.x; j++) {
				createTile({ j, i }, storage);
			}
		}
	}

	void MapGenerator::createTile(ge::Vector2<int> position, MapStorage storage) const {
		//If the tile is in the doubled coordinate system
		if ((position.x + position.y) % 2 == 0) {
			//Get the neighbors tile
			std::vector<TileComponent*> neighbors{ HexagonalMap{}.getNeighbors(position) };
			
			//Make statistics
			int averageHeight{ 0 };
			float averageHumidity{ 0 };
			constexpr int nbrOfSum{ 4 };
			for (int i = 0; i != nbrOfSum; i++) {
				//If there is no more neighbor to check
				if (i >= neighbors.size()) {
					int height{ rand() % mv::maxHeight };
					averageHeight += height;
					//If the tile is too high, there isn't water on top of it
					if (height > 2 * mv::maxHeight / 3)
						averageHumidity += rand() % static_cast<int>((mv::maxHumidity - mv::minWaterLevel) * 100) / 100.0f;
					else
						averageHumidity += rand() % static_cast<int>(mv::maxHumidity * 100) / 100.0f;
				}
				else {
					averageHeight += neighbors[i]->height;
					averageHumidity += neighbors[i]->humidity;
				}
			}
			//Create the tile
			TileComponent tile;
			tile.height = averageHeight / nbrOfSum;
			//tile.humidity = averageHumidity / nbrOfSum;
			tile.humidity = 1.5f;
			storage.addTile({ position.x, position.y }, std::move(tile));
		}

	}
}
