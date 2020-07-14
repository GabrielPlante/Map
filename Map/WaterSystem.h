#pragma once
#include "..\GameEngine2D\System.h"

namespace map {
    //The water system handle the water flow across the map
    class WaterSystem :
        public ge::System
    {
    private:
        long long timeSinceLastUpdate{ 0 };
    public:
    	//Update the system
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};
    };
}
