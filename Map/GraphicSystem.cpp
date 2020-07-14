#include "GraphicSystem.h"

#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Storage.h"

#include "MapTextureGenerator.h"
#include "HexagonalMap.h"
#include "MapStorage.h"
#include "MapValues.h"

namespace map {
	bool GraphicSystem::generateMap{ true };

	GraphicSystem::GraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
	{}

	void GraphicSystem::update() {
		if (generateMap) {
			MapTextureGenerator generator{ mv::mapSize };
			mapTexture = generator.getMapTexture();
			generateMap = false;
		}
		//Update the console
		ge::Console::getInstance()->update(getWindowRenderer());

		//Clear the window
		window.clear();

		//Render the map texture
		mapTexture.render(window.getRenderer());
		
		//Render the console
		ge::Console::getInstance()->render(getWindowRenderer());

		//Render the window
		window.render();
	}

}
