#include "GraphicSystem.h"

#include "../GameEngine2D/Console.h"

namespace map {
	GraphicSystem::GraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
	{}

	void GraphicSystem::update() {
		//Update the console
		ge::Console::getInstance()->update(getWindowRenderer());

		//Clear the window
		window.clear();



		
		//Render the console
		ge::Console::getInstance()->render(getWindowRenderer());

		//Render the window
		window.render();
	}

}
