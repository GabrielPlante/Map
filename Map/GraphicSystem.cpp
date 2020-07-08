#include "GraphicSystem.h"

#include "../GameEngine2D/Console.h"
#include "../GameEngine2D/Circle.h"

namespace map {
	GraphicSystem::GraphicSystem(int screenWidth, int screenHeight)
		: window{ screenWidth, screenHeight }
	{}

	void GraphicSystem::update() {
		//Update the console
		ge::Console::getInstance()->update(getWindowRenderer());

		//Clear the window
		window.clear();


		ge::TextureWrapper circle = ge::Circle{ 30, {100, 100, 100}, false }.getTexture();
		SDL_Rect rect{ circle.getTextureRect() };
		SDL_RenderCopy(window.getRenderer(), circle.get(), NULL, &rect);

		
		//Render the console
		ge::Console::getInstance()->render(getWindowRenderer());

		//Render the window
		window.render();
	}

}
