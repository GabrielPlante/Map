#include "BotManager.h"
#include <algorithm>

#include "Values.h"

#include <iostream>

namespace pns {
	//Struct to make possible sorting the fitness of every bot and keeping their position
	struct SortWithPos {
		int fitness, position;
		
		//Constructor to make thing easier
		SortWithPos(int fitness, int position) : fitness{ fitness }, position{ position } {}

		//Override operator < for the std::sort algorithm
		bool operator<(const SortWithPos& other) const { return fitness < other.fitness; }
	};

	BotManager::BotManager(std::function<bool()> hasWaveEnded, std::function<void()> startNextWave, std::function<bool()> hasGameEnded, std::function<void()> startNewGame,
		std::function<int()> getMoney, std::function<void(int)> placeTower, std::vector<int> towersCost, int moneyGap)
		: hasWaveEnded{ hasWaveEnded }, startNextWave{ startNextWave }, hasGameEnded{ hasGameEnded }, startNewGame{ startNewGame },
		getMoney{ getMoney }, placeTower{ placeTower }, towersCost{ towersCost }, moneyGap{ moneyGap }
	{
	}

	void BotManager::update() {
		//If no bots were created or loaded, create default bots
		if (bots.empty())
			createBots();
		//If the game ended, go to the next bot
		if (hasGameEnded()) {
			botIt++;
			//If there is no more bots that need to play, go to the next generation
			if (botIt == bots.end()) {
				nextGeneration();
			}
			startNewGame();
		}
		//If the wave ended, go to the next one
		else if (hasWaveEnded()) {
			startNextWave();
		}
		//Finally, if nothing special happened, let the bot play
		else {
			botIt->play(getMoney, placeTower, towersCost, moneyGap);
		}
	}

	void BotManager::nextGeneration() {
		std::cout << "New generation" << std::endl;
		//Make a sorted vector with all the fitness of all the bot
		std::vector<SortWithPos> fitnessVector;
		for (int i = 0; i != bots.size(); i++) {
			fitnessVector.push_back({ bots[i].getFitness(), i });
		}
		std::sort(fitnessVector.begin(), fitnessVector.end());

		//The bot of the next generation
		std::vector<GeneticBot> newBots;
		//Where we start to take the best bots in the fitness vector
		int bestBotStart{ static_cast<int>(fitnessVector.size() - percentageOfBotKept * nbrOfBotPerGeneration / 100) };
		int i{ bestBotStart };
		while (newBots.size() < nbrOfBotPerGeneration) {
			//Randomise the bot parameters
			Container2D<int> newBotParameters{ bots[fitnessVector[i].position].getDecisionMap() };
			randomiseParameters(&newBotParameters, percentageOfBotKept);
			GeneticBot bot{ newBotParameters };
			newBots.push_back(bot);
			//Increment i and check to not get out of the vector bound
			i++;
			if (i >= fitnessVector.size())
				i = bestBotStart;
		}
		//Set the real bot list to the new bot list
		bots = newBots;
		botIt = bots.begin();
	}

	std::vector<int> BotManager::getAffordableTowers(int diminishedPrice) const {
		std::vector<int> goodValues;
		for (int i = 0; i != towersCost.size(); i++) {
			if (towersCost[i] <= diminishedPrice * moneyGap)
				goodValues.push_back(i);
		}
		return goodValues;
	}

	void BotManager::randomiseParameters(Container2D<int>* values, int randomPercent, int unvalidValue) {
		//For every value in this container
		for (int i = 0; values->exist(i); i++) {
			for (int j = 0; values->exist(i, j); j++) {
				//If it is not the unvalid value and it is chosen for a reassignement
				if (values->get(i, j) != unvalidValue && Random::getRandomNumber() % 100 < randomPercent) {
					//Change it to a random valid value
					std::vector<int> validValues{ getAffordableTowers(j) };
					//Add the "don't build a tower" option
					validValues.push_back(-2);
					values->set(i, j, validValues[Random::getRandomNumber() % validValues.size()]);
				}
			}
		}
	}

	void BotManager::createBots() {
		std::cout << "Creating bots" << std::endl;
		for (int i = 0; i != nbrOfBotPerGeneration; i++) {
			bots.push_back(GeneticBot{});
		}
		botIt = bots.begin();
	}

}
