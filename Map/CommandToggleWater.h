#pragma once
#include "../GameEngine2D/Command.h"
#include "../GameEngine2D/Engine.h"

#include "MapTextureGenerator.h"
#include "MapValues.h"

namespace map {
	class CommandToggleWater
		: public ge::Command
	{
	private:
	public:
		//Constructor
		CommandToggleWater()
			: Command{ "toggle_water" }
		{}

		//Execute
		void execute(const std::vector<float>&) override {
			MapTextureGenerator::toggleWater();
		}
	};
}

