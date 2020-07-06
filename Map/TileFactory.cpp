#include "TileFactory.h"

#include "MapStorage.h"

namespace map {
	TileFactory::TileFactory(ge::Vector2<int> tilePosition, int tileHeight)
		: tilePosition{ tilePosition }
	{
		tile.height = tileHeight;
	}

	bool TileFactory::finishTile() const {
		//Create a temporary tile that can be moved
		TileComponent tempTile{ tile };

		//Store the tile
		MapStorage mapStorage;
		return mapStorage.addTile(tilePosition, std::move(tempTile));
	}
}
