#include "MapTextureGenerator.h"
#include <map>

#include "../GameEngine2D/CircleCreator.h"
#include "../GameEngine2D/HexagonCreator.h"
#include "../GameEngine2D/Drawer.h"

#include "HexagonalMap.h"
#include "MapStorage.h"
#include "MapValues.h"

namespace map {
	MapTextureGenerator::MapTextureGenerator(ge::Vector2<int> mapSize) {

		//Map to store every circle
		std::map<ge::Vector2<int>, ge::TextureWrapper> tileVector;

		MapStorage storage;
		for (auto it = storage.getBeginningIterator(); it != storage.getEndIterator(); it++) {
			//Create the texture
			ge::TextureWrapper hexagon;
			if (it->second.humidity < 1)
				hexagon = ge::HexagonCreator{ mv::tileSize, {200 - it->second.height * 2, 50, 0} }.getTexture();
			else
				hexagon = ge::HexagonCreator{ mv::tileSize, {0, 50, 255 - static_cast<int>((it->second.humidity - 1) * 200)} }.getTexture();

			//Create the coordinate
			ge::Vector2<> pos{ HexagonalMap::relativeToAbsolute(it->first) };
			ge::Vector2<int> posInt{ static_cast<int>(pos.x),  static_cast<int>(pos.y) };
			//Insert it into the map
			tileVector.insert(std::make_pair(posInt, hexagon));
		}

		ge::Drawer drawer;
		ge::Vector2<> realMapSize{ HexagonalMap::relativeToAbsolute(mapSize) };
		SDL_Renderer* renderer{ drawer.startDrawing({static_cast<int>(realMapSize.x) + mv::tileSize, static_cast<int>(realMapSize.y) + mv::tileSize}, {0, 0, 0}) };

		//Render every circle
		for (auto it = tileVector.begin(); it != tileVector.end(); it++) {
			it->second.render(renderer, it->first);
		}

		mapTexture = drawer.finishDrawing();
	}
}
