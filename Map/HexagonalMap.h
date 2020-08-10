#pragma once

#include "../GameEngine2D/Vector2.h"

#include "TileComponent.h"

namespace map {
	//Implementation of the hexagonal map
	class HexagonalMap
	{
	public:
		//Relative position to an absolute one
		static ge::Vector2<> relativeToAbsolute(ge::Vector2<int> relative);

		//Absolute position to a relative one
		//ge::Vector2<int> absoluteToRelative(ge::Vector2<> absolute) const;

		//Get the 6 neighbors of a tile
		std::vector<TileComponent*> getNeighbors(ge::Vector2<int> position) const;

		//Get the neighbors of a tile with their position
		std::vector<std::pair<ge::Vector2<int>, TileComponent*>> getNeighborsWithPos(ge::Vector2<int> position) const;

		//Get the distance between two tiles
		int distance(ge::Vector2<int> tile1, ge::Vector2<int> tile2) const;
	};
}

