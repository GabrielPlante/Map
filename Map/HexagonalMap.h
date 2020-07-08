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
	};
}

