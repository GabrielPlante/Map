#pragma once

#include "../GameEngine2D/Color.h"

namespace ian {
	class TileComponent
	{
	public:
		ge::Color color;

		//Can a entity walk over this tile
		bool isWalkable{ true };
	};
}