#pragma once

#include "../GameEngine2D/Vector2.h"

namespace map {
	class MapGenerator
	{
	private:
		unsigned int seed;
	public:
		//Constructor, generate a map
		MapGenerator(ge::Vector2<int> mapSize, unsigned int seed = 0);

		//Get the seed of this map
		unsigned int getSeed() const { return seed; }
	};
}
