#include "MapStorage.h"

namespace map {
	std::map<ge::Vector2<int>, TileComponent> MapStorage::map{};

	bool MapStorage::addTile(ge::Vector2<int> position, TileComponent&& tile) {
		if (tileExist(position))
			return false;
		map.insert(std::make_pair(position, tile));
		return true;
	}

	bool MapStorage::deleteTile(ge::Vector2<int> position) {
		return map.erase(position);
	}

	void MapStorage::changeTile(ge::Vector2<int> position, TileComponent&& tile) {
		if (tileExist(position))
			deleteTile(position);
		map.insert(std::make_pair(position, tile));
	}
}
