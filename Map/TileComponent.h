#pragma once
#include "../GameEngine2D/Vector2.h"

namespace map {
	//Hold every information about a tile
	struct TileComponent {
		//At wich height the tile lies
		int height;

		//The humidity of the tile. Above 1 the tile is flooded
		float humidity;
	};
}
