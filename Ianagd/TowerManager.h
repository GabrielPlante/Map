#pragma once
#include <vector>

#include "../GameEngine2D/Vector2.h"

namespace ian {
	class TowerManager
	{
	private:
		std::vector<unsigned int> towersId;
	public:
		//Build a tower. Return true if the tower has been build, false otherwise
		bool buildTower(ge::Vector2<> position, int type);

		//Check if a tile is buildable and if there isn't any other tower already there
		bool isBuildable(ge::Vector2<> position) const;

		//Clear the tower
		void clear() { towersId.clear(); }
	};
}

