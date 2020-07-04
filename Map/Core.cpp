#include "Core.h"

#include "../GameEngine2D/Engine.h"

#include "GraphicSystem.h"

//Size of the screen
constexpr int SCREEN_WIDTH{ 1400 };
constexpr int SCREEN_HEIGHT{ 800 };

namespace map {
	Core* Core::instance{ nullptr };

	void Core::init() { instance = new Core{}; }

	void Core::quit() {
		if (instance)
			delete instance;
	}

	Core::Core() {
		ge::Engine::init(SCREEN_WIDTH, SCREEN_HEIGHT);

		std::shared_ptr<GraphicSystem> graphicSystem{ new GraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT} };
		gRenderer = graphicSystem->getWindowRenderer();
		ge::Engine::getInstance()->addGraphicSystem(std::move(graphicSystem));

	}

	void Core::run() {
		ge::Engine::getInstance()->mainLoop();
	}

}
