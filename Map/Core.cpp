#include "Core.h"

#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/CommandList.h"

#include "CommandQuitConsole.h"

#include "GraphicSystem.h"
#include "MapGenerator.h"
#include "WaterSystem.h"
#include "MapValues.h"

//Size of the screen
constexpr int SCREEN_WIDTH{ 1400 };
constexpr int SCREEN_HEIGHT{ 800 };

namespace map {
	void fillCommandList() {
		ge::CommandList::getInstance()->addCommand(std::move(std::unique_ptr<ge::Command>{new CommandQuitConsole{}}));
	}

	Core* Core::instance{ nullptr };

	void Core::init() { instance = new Core{}; }

	void Core::quit() {
		if (instance)
			delete instance;
	}

	Core::Core() {
		//Init the engine
		ge::Engine::init(SCREEN_WIDTH, SCREEN_HEIGHT);

		//Fill the command list
		fillCommandList();

		//Add a graphic system
		std::shared_ptr<GraphicSystem> graphicSystem{ new GraphicSystem{SCREEN_WIDTH, SCREEN_HEIGHT} };
		gRenderer = graphicSystem->getWindowRenderer();
		ge::Engine::getInstance()->addGraphicSystem(std::move(graphicSystem));

		std::shared_ptr<WaterSystem> waterSystem{ new WaterSystem{} };
		ge::Engine::getInstance()->addSystem(waterSystem);


		//Quit the console and reduce fps to reduce work load
		EXEC("quitconsole");
		EXEC_ARGS("fps", { 30 });

		MapGenerator mapGenerator{ mv::mapSize };
	}

	void Core::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}
