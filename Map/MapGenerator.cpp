#include "MapGenerator.h"
#include <stdlib.h>
#include <time.h>

#include "TileComponent.h"
#include "MapStorage.h"

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
		for (int i = 0; i != mapSize.x; i++) {
			for (int j = 0; j != mapSize.y; j++) {
				//If the tile is in the doubled coordinate system
				if ((i + j) % 2 == 0) {
					//Create the tile
					TileComponent tile;
					tile.height = rand() % 100;
					tile.humidity = rand() % 200 / 100.0f;
					storage.addTile({ i, j }, std::move(tile));
				}
			}
		}
	}
}
