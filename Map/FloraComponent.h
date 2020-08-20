#pragma once

#include "../GameEngine2D/Vector2.h"

#include "FloraRestriction.h"

namespace map {
	struct FloraComponent {
		//First the requirement

		//The margin in which the plante can survive
		FloraRestriction<ge::Vector2<float>> humidityMargin;

		//The max water the plant can survive in
		FloraRestriction<float> maxWater;
	};
}
