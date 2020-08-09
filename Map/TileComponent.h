#pragma once
#include "../GameEngine2D/Vector2.h"

//The minimum humidity level before it is considered humidity in the tile instead of water above the tile
static constexpr float minWaterLevel{ 1 };

//The multiplicator of the level of water to the height of the water (if humidity is 1.5, water level is 0.5, height is 0.5 * waterToHeight + the height of the tile
constexpr float waterToHeight{ 5 };

namespace map {
	//Hold every information about a tile
	struct TileComponent {
		//At wich height the tile lies
		int height;

		//The height lost due to water flow
		int heightLost{ 0 };

		//The humidity of the tile. Above 1 the tile is flooded
		float humidity;

		//Return the real height of the tile, taking into account the water above the tile.
		int realheight() const {
			//If there is water above the tile
			if (humidity > minWaterLevel)
				return height + static_cast<int>((humidity - minWaterLevel) * waterToHeight) - heightLost;
			else
				return height - heightLost;
		}
	};
}
