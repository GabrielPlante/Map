#pragma once

#include "../GameEngine2D/Vector2.h"

#include "MapStorage.h"

namespace map {
	class MapGenerator
	{
	private:
		unsigned int seed;

		long long timeInTileCreation{ 0 };
	public:
		//Constructor, generate a map
		MapGenerator(int mapSize, unsigned int seed = 0);

		//Create a tile at the position with the average of the other tile given plus one random
		void createTileFractal(ge::Vector2<int> position, MapStorage storage, const std::vector<ge::Vector2<int>>& tileToAverage);

		//Get the seed of this map
		unsigned int getSeed() const { return seed; }
	};
}
