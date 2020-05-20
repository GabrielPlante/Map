#pragma once

namespace pns {
	//The number of bot that exist and compete each generation
	constexpr int nbrOfBotPerGeneration{ 100 };

	//The percentage of bot kept at the end of each generation for the next one
	constexpr int percentageOfBotKept{ 10 };

	//The percentage of parameter that change when passing over the next generation
	constexpr int percentageOfParameterChanged{ 25 };

	//The percentage of chance the bot will build a tower when it can (and it doesn't have something already planned)
	constexpr int chanceToBuildTower{ 30 };
}
