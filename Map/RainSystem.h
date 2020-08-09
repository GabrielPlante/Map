#pragma once
#include "..\GameEngine2D\System.h"

namespace map {
    class RainSystem :
        public ge::System
    {
    private:
        long long timeSinceLastUpdate{ 0 };

        //The duration of the rain in ticks
        int rainDuration{ 0 };
        float rainIntensity{ 0 };
    public:
        //Update the system
		void update() override;

		//As a subscriber, the system need to be able to handle message
		void handleMessage(std::shared_ptr<ge::Message> message) override {};

    };

}
