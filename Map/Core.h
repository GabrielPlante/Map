#pragma once

struct SDL_Renderer;
namespace map {
	class Core
	{
	private:
		static Core* instance;

		//Constructor private for singleton
		Core();

		SDL_Renderer* gRenderer;

	public:
		//Init the singleton
		static void init();

		//Quit the singleton
		static void quit();

		//Get the core instance
		static Core* getInstance() { return instance; }

		//Run the core
		void run();
	};

}
