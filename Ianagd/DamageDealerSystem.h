#pragma once
#include <vector>

#include "../GameEngine2D/System.h"

namespace ian {
	class DamageDealerSystem
		:public ge::System
	{
	private:
		std::vector<unsigned int> shotRenderersId;
	public:
		//Constructor
		DamageDealerSystem() {}

		//Update the system
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
	};
}

