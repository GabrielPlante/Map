#pragma once

#include "../GameEngine2D/TextureWrapper.h"
#include "../GameEngine2D/Vector2.h"

namespace map {
	class MapTextureGenerator
	{
	private:
		static bool showWater;

		ge::TextureWrapper mapTexture;
	public:
		//Constructor, (re)generate the texture of the map
		MapTextureGenerator(ge::Vector2<int> mapSize);

		//Get the map texture generated
		ge::TextureWrapper getMapTexture() const { return mapTexture; }

		//Toggle the water
		static void toggleWater() { showWater = !showWater; }
	};
}
