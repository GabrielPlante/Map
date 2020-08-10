#include "Core.h"

#include "../GameEngine2D/Engine.h"
#include "../GameEngine2D/CommandList.h"

#include "CommandQuitConsole.h"

#include "GraphicSystem.h"
#include "MapGenerator.h"
#include "WaterSystem.h"
#include "RainSystem.h"
#include "MapValues.h"


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
		ge::Engine::init(mv::SCREEN_WIDTH, mv::SCREEN_HEIGHT);

		//Fill the command list
		fillCommandList();

		//Add a graphic system
		std::shared_ptr<GraphicSystem> graphicSystem{ new GraphicSystem{mv::SCREEN_WIDTH, mv::SCREEN_HEIGHT} };
		gRenderer = graphicSystem->getWindowRenderer();
		ge::Engine::getInstance()->addGraphicSystem(std::move(graphicSystem));

		//Add the other systems
		std::shared_ptr<WaterSystem> waterSystem{ new WaterSystem{} };
		ge::Engine::getInstance()->addSystem(waterSystem);
		std::shared_ptr<RainSystem> rainSystem{ new RainSystem{} };
		ge::Engine::getInstance()->addSystem(rainSystem);


		//Quit the console and reduce fps to reduce work load
		EXEC("quitconsole");
		EXEC_ARGS("fps", { 10 });

		MapGenerator mapGenerator{ mv::mapSideSize };
	}

	void Core::run() {
		ge::Engine::getInstance()->mainLoop();
	}
}
