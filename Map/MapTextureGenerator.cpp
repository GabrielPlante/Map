#include "MapTextureGenerator.h"
#include <map>

#include "../GameEngine2D/CircleCreator.h"
#include "../GameEngine2D/HexagonCreator.h"
#include "../GameEngine2D/Drawer.h"

#include "HexagonalMap.h"
#include "FloraStorage.h"
#include "MapStorage.h"
#include "MapValues.h"

namespace map {
	bool MapTextureGenerator::showWater{ true };
	bool MapTextureGenerator::showFlora{ true };

	constexpr double redHeightFactor{ 1 };
	constexpr double greenHeightFactor{ 0.6 };
	constexpr double blueHeightFactor{ 0.2 };

	constexpr float maxWaterForColor{ 3 };
	constexpr double redWaterFactor{ 0.2 };
	constexpr double greenWaterFactor{ 0.5 };
	constexpr double blueWaterFactor{ 1 };

	constexpr double redFloraFactor{ 0 };
	constexpr double greenFloraFactor{ 1 };
	constexpr double blueFloraFactor{ 0 };
	MapTextureGenerator::MapTextureGenerator(ge::Vector2<int> mapSize) {

		//Create the base hexagon. Only the color of this hexagon will be changed to render every other hexagon
		ge::TextureWrapper baseHexagon{ ge::HexagonCreator{mv::tileSize, {255, 255, 255}}.getTexture() };

		//Create the drawer and get the renderer
		ge::Drawer drawer;
		SDL_Renderer* renderer{ drawer.startDrawing({mapSize.x, mapSize.y}, {0, 0, 0}) };

		MapStorage storage;
		FloraStorage floraStorage;
		for (auto it = storage.getBeginningIterator(); !it.endReached(); it++) {
			//Set the proper color
			//If there is a flora on that tile, it is printed
			if (floraStorage.floraExist(it.getPosition())) {
				float humidityLowerMargin{ floraStorage.getTile(it.getPosition()).humidityMargin.restriction.x };

				SDL_SetTextureColorMod(baseHexagon.get(), static_cast<Uint8>((255 - (humidityLowerMargin * 255)) * redFloraFactor),
					static_cast<Uint8>((255 - (humidityLowerMargin * 255)) * greenFloraFactor), static_cast<Uint8>((255 - (humidityLowerMargin * 255)) * blueFloraFactor));
			}
			//If there is water, print it
			else if (it->water != 0 && showWater) {
				float water{ it->water };
				if (water > maxWaterForColor)
					water = maxWaterForColor;
				water = 255 - (water * 255 / (maxWaterForColor + 1));
				SDL_SetTextureColorMod(baseHexagon.get(), static_cast<Uint8>(water * redWaterFactor),
					static_cast<Uint8>(water * greenWaterFactor), static_cast<Uint8>(water * blueWaterFactor));
			}
			//Else, show the height
			else {
				SDL_SetTextureColorMod(baseHexagon.get(), static_cast<Uint8>((255 - (it->height * 255 / mv::maxHeight)) * redHeightFactor),
					static_cast<Uint8>((255 - (it->height * 255 / mv::maxHeight)) * greenHeightFactor), static_cast<Uint8>((255 - (it->height * 255 / mv::maxHeight)) * blueHeightFactor));
			}

			//Create the coordinate
			ge::Vector2<> pos{ HexagonalMap::relativeToAbsolute(it.getPosition()) };
			ge::Vector2<int> posInt{ static_cast<int>(pos.x),  static_cast<int>(pos.y) };

			baseHexagon.render(renderer, posInt);
		}
		mapTexture = drawer.finishDrawing();
	}
}
