#pragma once

namespace pns {
	//The number of bot that exist and compete each generation
	constexpr int nbrOfBotPerGeneration{ 20 };

	//The percentage of bot kept at the end of each generation for the next one
	constexpr int percentageOfBotKept{ 5 };

	//The percentage of parameter that change when passing over the next generation
	constexpr int percentageOfParameterChanged{ 10 };
}
