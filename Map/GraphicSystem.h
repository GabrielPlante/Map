#pragma once
#include "../GameEngine2D/System.h"
#include "../GameEngine2D/Window.h"

namespace map {
	/// <summary>
	/// The grapic system
	/// </summary>
	/// <seealso cref="ge::System" />
	class GraphicSystem :
		public ge::System
	{
	private:
		ge::Window window;
	public:
		//Constructor
		GraphicSystem(int screenWidth, int screenHeight);

		//Update the system
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};

		//Get the renderer from the window
		SDL_Renderer* getWindowRenderer() const { return window.getRenderer(); }
	};
}
