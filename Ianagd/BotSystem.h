#pragma once
#include <memory>

#include "../GameEngine2D/System.h"
#include "../pns-innov/BotManager.h"

namespace ian {
	class BotSystem
		: public ge::System
	{
	private:
	public:
		//Constructor
		BotSystem();

		//Update the system
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
	};

}
