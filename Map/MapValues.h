#pragma once

#include "../GameEngine2D/Vector2.h"

//Class map values
class mv {
public:
	//The size of a tile
	static constexpr int tileSize{ 10 };

	//The size of the map, in tile
	static constexpr ge::Vector2<int> mapSize{ 160, 52 };

	//The maximum height of a tile
	static constexpr int maxHeight{ 100 };

	//The maximum humidity of a tile
	static constexpr float maxHumidity{ 2.0f };

	//The time between two update of the water system that handle the water flow in microsecond
	static constexpr long long timeBetweenWaterUpdate{ 300 * 1000 };

	//The minimum humidity level before it is considered humidity in the tile instead of water above the tile
	static constexpr float minWaterLevel{ 1 };
};
