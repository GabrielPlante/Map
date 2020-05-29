#pragma once

#include "../GameEngine2D/Command.h"
#include "../GameEngine2D/Console.h"

#include "GameCore.h"

namespace ian {
	class CommandPlaceTower :
		public ge::Command
	{
	public:
		//Constructor
		CommandPlaceTower() : ge::Command("place_tower") {}

		//Execute the command
		void execute(const std::vector<float>& args) override {
			if (args.size() == 3) {
				ge::Vector2<> towerPosition{ static_cast<long>(args[0]), static_cast<long>(args[1]) };
				if (!GameCore::getInstance()->getTowerManager()->buildTower(towerPosition, static_cast<int>(args[2])))
					CONSOLE_LOG_ERROR("Could not build tower of type " + std::to_string(args[2]) + " at place : " + std::to_string(args[0]) + " ; " + std::to_string(args[1]))
			}
			else
				CONSOLE_LOG_ERROR("Invalid number of argument. Required: " + std::to_string(3) + ", got: " + std::to_string(args.size()));
		}
	};
}
