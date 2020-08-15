#pragma once

#include "../GameEngine2D/Vector2.h"

//Class map values
class mv {
public:

	//Size of the screen
	static constexpr int SCREEN_WIDTH{ 1400 };
	static constexpr int SCREEN_HEIGHT{ 800 };

	//The size of a tile
	static constexpr int tileSize{ 8 };

	//The size of the map, in tile
	//static constexpr ge::Vector2<int> mapSize{ 75, 50 };

	//Test for a new way to build the map, the map will be an hexagon of side mapSideSize
	static constexpr int mapSideSize{ 33 };

	//The maximum height of a tile
	static constexpr int maxHeight{ 1000 };

	//The time between two update of each environment system
	static constexpr long long timeBetweenEnvironmentUpdate{ 300 * 1000 };

	//The maximum humidity of a tile
	static constexpr float maxHumidity{ 2.0f };
};
