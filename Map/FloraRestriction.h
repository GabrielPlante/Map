#pragma once

namespace map {
	template <typename T>
	struct FloraRestriction {
		//The restriction
		T restriction;

		//The survival time outside the restriction, in ticks
		int survivalTime;

		//The time spent outside the restriction so far
		int timeInSurvival{ 0 };

		//Constructor
		FloraRestriction(T restriction, int survivalTime) : restriction{ restriction }, survivalTime{ survivalTime } {}
		//Default constructor
		FloraRestriction() {}
	};
}
