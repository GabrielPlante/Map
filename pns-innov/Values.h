#pragma once

namespace pns {
	//The number of bot that exist and compete each generation
	constexpr int nbrOfBotPerGeneration{ 20 };

	//The percentage of bot kept at the end of each generation for the next one
	constexpr int percentageOfBotKept{ 10 };

	//The percentage of chance the bot will build a tower when it can (and it doesn't have something already planned)
	constexpr int chanceToBuildTower{ 30 };
}
