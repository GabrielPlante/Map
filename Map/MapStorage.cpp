#include "MapStorage.h"

namespace map {
	//std::map<ge::Vector2<int>, TileComponent> MapStorage::map{};
	std::vector<std::vector<TileComponent>> MapStorage::map;

	bool MapStorage::addTile(ge::Vector2<int> position, TileComponent&& tile) {
		if (tileExist(position))
			return false;
		//map.insert(std::make_pair(position, tile));
		while (map.size() <= position.x)
			map.push_back(std::vector<TileComponent>{});
		while (map[position.x].size() <= position.y) {
			TileComponent tempTile;
			tempTile.height = -1;
			map[position.x].push_back(tempTile);
		}
		map[position.x][position.y] = tile;
		return true;
	}

	bool MapStorage::deleteTile(ge::Vector2<int> position) {
		//return map.erase(position);
		if (!tileExist(position))
			return false;
		map[position.x][position.y].height = -1;
		return true;
	}

	/*void MapStorage::changeTile(ge::Vector2<int> position, TileComponent&& tile) {
		if (tileExist(position))
			deleteTile(position);
		map.insert(std::make_pair(position, tile));
	}*/
	
}
