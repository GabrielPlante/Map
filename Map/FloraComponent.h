#pragma once

#include "../GameEngine2D/Vector2.h"
#include "../GameEngine2D/Color.h"

#include "FloraRestriction.h"

//The color of the flora is dependent of the humidity margin
namespace map {
	struct FloraComponent {
		//First the requirement

		//The margin in which the plante can survive
		FloraRestriction<ge::Vector2<float>> humidityMargin;

		//The max water the plant can survive in
		FloraRestriction<float> maxWater;

		//Constructor
		FloraComponent(FloraRestriction<ge::Vector2<float>> humidityMargin, FloraRestriction<float> maxWater) : humidityMargin{ humidityMargin }, maxWater{ maxWater } {}

		//Operator to know if two flora component are the same family
		bool operator!=(const FloraComponent& other) const {
			return humidityMargin.restriction != other.humidityMargin.restriction;
		}
		bool operator==(const FloraComponent& other) const {
			return humidityMargin.restriction == other.humidityMargin.restriction;
		}
	};
}
