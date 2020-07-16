#include "MapTextureGenerator.h"
#include <map>

#include "../GameEngine2D/CircleCreator.h"
#include "../GameEngine2D/HexagonCreator.h"
#include "../GameEngine2D/Drawer.h"

#include "HexagonalMap.h"
#include "MapStorage.h"
#include "MapValues.h"

#include "../GameEngine2D/Clock.h"

namespace map {
	MapTextureGenerator::MapTextureGenerator(ge::Vector2<int> mapSize) {

		//Create the base hexagon. Only the color of this hexagon will be changed to render every other hexagon
		ge::TextureWrapper baseHexagon{ ge::HexagonCreator{mv::tileSize, {255, 255, 255}}.getTexture() };

		//Create the drawer and get the renderer
		ge::Drawer drawer;
		SDL_Renderer* renderer{ drawer.startDrawing({mapSize.x, mapSize.y}, {0, 0, 0}) };

		MapStorage storage;
		for (auto it = storage.getBeginningIterator(); it != storage.getEndIterator(); it++) {
			//Set the proper color
			if (it->second.humidity < 1)
				//SDL_SetTextureColorMod(baseHexagon.get(), static_cast<Uint8>(200 - it->second.height * 2), 50, 0);
				SDL_SetTextureColorMod(baseHexagon.get(), static_cast<Uint8>(255 - (it->second.height * 255 / mv::maxHeight)),
					static_cast<Uint8>(255 - (it->second.height * 255 / mv::maxHeight)), static_cast<Uint8>(255 - (it->second.height * 255 / mv::maxHeight)));
			else {
				int blue{ static_cast<int>((it->second.humidity - 1) * 200) };
				if (blue > 200) blue = 200;
				SDL_SetTextureColorMod(baseHexagon.get(), 0, 50, 255 - static_cast<Uint8>(blue));
			}

			//Create the coordinate
			ge::Vector2<> pos{ HexagonalMap::relativeToAbsolute(it->first) };
			ge::Vector2<int> posInt{ static_cast<int>(pos.x),  static_cast<int>(pos.y) };

			baseHexagon.render(renderer, posInt);
			//Insert it into the map
			//tileVector.insert(std::make_pair(posInt, hexagon));
		}
		mapTexture = drawer.finishDrawing();
	}
}