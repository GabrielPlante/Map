#pragma once
#include <map>

#include "../GameEngine2D/Vector2.h"

#include "TileComponent.h"

namespace map {
	//Store every tile component that compose the map
	class MapStorage
	{
	private:
		//The map storage, static so the map is unique
		static std::map<ge::Vector2<int>, TileComponent> map;
	public:
		//Add a tile to the map. Return true if the tile was added, return false if there was already a tile
		bool addTile(ge::Vector2<int> position, TileComponent&& tile);

		//Delete the tile at the position. Return true if the tile was deleted, and false if there was no tile at the position
		bool deleteTile(ge::Vector2<int> position);

		//Change a tile, or add the tile if no tile was there
		void changeTile(ge::Vector2<int> position, TileComponent&& tile);

		//Check if there is a tile at the position specified, return true if there is one
		bool tileExist(ge::Vector2<int> position) const { return map.find(position) != map.end(); }
	};
}

