#pragma once

#include "../GameEngine2D/Vector2.h"

#include "MapStorage.h"

namespace map {
	class MapGenerator
	{
	private:
		unsigned int seed;
	public:
		//Constructor, generate a map
		MapGenerator(int mapSize, unsigned int seed = 0);

		//Create a tile
		void createTile(ge::Vector2<int> position, MapStorage storage) const;

		//Get the seed of this map
		unsigned int getSeed() const { return seed; }
	};
}
