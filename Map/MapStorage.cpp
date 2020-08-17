#include "MapStorage.h"

namespace map {
	TileComponent getDefaultTile() {
		TileComponent tile;
		tile.height = -1;
		return tile;
	}
	bool isTileValid(const TileComponent& tile) {
		return tile.height != -1;
	}
	//std::map<ge::Vector2<int>, TileComponent> MapStorage::map{};
	ge::VectorOfVector<TileComponent> MapStorage::map{ getDefaultTile, isTileValid };
}
