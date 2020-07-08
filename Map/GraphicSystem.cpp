#include "GraphicSystem.h"

#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Circle.h"
#include "../GameEngine2D/Storage.h"

#include "HexagonalMap.h"
#include "MapStorage.h"
#include "MapValues.h"

namespace map {
	GraphicSystem::GraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
	{}

	void GraphicSystem::update() {
		//Update the console
		ge::Console::getInstance()->update(getWindowRenderer());

		//Clear the window
		window.clear();

		MapStorage storage;
		for (auto it = storage.getBeginningIterator(); it != storage.getEndIterator(); it++) {
			ge::TextureWrapper circle = ge::Circle{ mv::tileSize, {static_cast<int>(it->second.height * 200), 100, static_cast<int>(it->second.humidity * 100)}, true }.getTexture();
			SDL_Rect rect{ circle.getTextureRect() };
			ge::Vector2<> pos{ HexagonalMap::relativeToAbsolute(it->first) };
			rect.x = static_cast<int>(pos.x);
			rect.y = static_cast<int>(pos.y);
			SDL_RenderCopy(window.getRenderer(), circle.get(), NULL, &rect);
			
		}

		
		//Render the console
		ge::Console::getInstance()->render(getWindowRenderer());

		//Render the window
		window.render();
	}

}
