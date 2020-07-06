#pragma once

#include "TileComponent.h"

namespace map {
	//This class is used to create a tile
	class TileFactory
	{
	private:
		TileComponent tile;
		ge::Vector2<int> tilePosition;
	public:
		//Constructor
		TileFactory(ge::Vector2<int> tilePosition, int tileHeight = 0);

		//Add the tile to the map, return true if the tile is added
		bool finishTile() const;
	};
}

