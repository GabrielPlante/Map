#pragma once
#include "../GameEngine2D/Vector2.h"

//The multiplicator of the level of water to the height of the water (if humidity is 1.5, water level is 0.5, height is 0.5 * waterToHeight + the height of the tile
constexpr float waterToHeight{ 5 };

namespace map {
	//Hold every information about a tile
	struct TileComponent {
		//At wich height the tile lies
		int height;

		//The humidity of the tile, between 0 and 1. Above 1 the tile is flooded
		float humidity;

		//The water level of the tile
		float water{ 0 };

		//Return the real height of the tile, taking into account the water above the tile.
		int realheight() const {
			return height + static_cast<int>(water * waterToHeight);
		}
	};
}
