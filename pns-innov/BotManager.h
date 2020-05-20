#pragma once
#include <functional>
#include <vector>
#include <string>

#include "Container2D.h"
#include "GeneticBot.h"
#include "Statistics.h"


namespace pns {
	//BotManager
	class BotManager
	{
	private:
		//Function needed for the manager to run
		std::function<bool()> hasWaveEnded;
		std::function<void()> startNextWave;
		std::function<bool()> hasGameEnded;
		std::function<void()> startNewGame;

		//The parameter used for the bot to work
		std::function<int()> getMoney;
		std::function<void(int, int)> placeTower;
		std::vector<int> towersCost;
		int moneyGap;

		//The bots storage
		std::vector<GeneticBot> bots;
		std::vector<GeneticBot>::iterator botIt;
		Statistics stats;

		//Prepare the next generation and randomise some bots parameters
		void nextGeneration();

		//Get all the towers with a cost under diminishedPrice*priceGap
		std::vector<int> getAffordableTowers(int diminishedPrice) const;

		//Randomise a random percentage of all the valid value in the container with a value within the possible values
		void randomiseParameters(Container2D<int>* values, int randomPercent, int unvalidValue = -1);
	public:
		/*Default constructor
		* getMoney is a function that should return the money the player have
		* getCurrentWave is a function that should return the wave nbr the player currently is
		* placeTower is a function that should place a tower on an optimal position when called, the second parameter is the number of tower already placed by the bot
		* towersCost is a vector that contain each cost of each tower
		* The money gap is used if money is always the multiple of a number
		*/
		BotManager(std::function<bool()> hasWaveEnded, std::function<void()> startNextWave, std::function<bool()> hasGameEnded, std::function<void()> startNewGame,
			std::function<int()> getMoney, std::function<void(int, int)> placeTower, std::vector<int> towersCost, int moneyGap = 1);

		//Update the bot manager
		void update();
		
		//Create the bots
		void createBots();

		//Load bots from a file
		void loadBots(std::string fileName = "default_bot_file.txt");
	};
}

