#pragma once

#include "../GameEngine2D/Vector2.h"

//Class map values
class mv {
public:

	//Size of the screen
	static constexpr int SCREEN_WIDTH{ 1400 };
	static constexpr int SCREEN_HEIGHT{ 800 };

	//The size of a tile
	static constexpr int tileSize{ 10 };

	//The size of the map, in tile
	//static constexpr ge::Vector2<int> mapSize{ 75, 50 };

	//Test for a new way to build the map, the map will be an hexagon of side mapSideSize
	static constexpr int mapSideSize{ 27 };

	//The maximum height of a tile
	static constexpr int maxHeight{ 100 };

	//The maximum humidity of a tile
	static constexpr float maxHumidity{ 2.0f };

	//The time between two update of the water system that handle the water flow in microsecond
	static constexpr long long timeBetweenWaterUpdate{ 300 * 1000 };

	//The minimum humidity level before it is considered humidity in the tile instead of water above the tile
	static constexpr float minWaterLevel{ 1 };
};
