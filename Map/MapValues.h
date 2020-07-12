#pragma once

#include "../GameEngine2D/Vector2.h"

//Class map values
class mv {
public:
	//The size of a tile
	static constexpr int tileSize{ 26 };

	//The size of the map, in tile
	static constexpr ge::Vector2<int> mapSize{ 62, 20 };

	//The maximum height of a tile
	static constexpr int maxHeight{ 100 };

	//The maximum humidity of a tile
	static constexpr float maxHumidity{ 2.0f };
};
