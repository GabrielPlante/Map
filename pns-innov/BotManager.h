#pragma once
#include <functional>
#include <vector>
#include <string>
#include <algorithm>

#include "TowerBalancer.h"
#include "WaveBalancer.h"
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

		//to store statistics of each run in different files
		time_t now = time(0);
		std::string getDate() {
			tm* ltm = localtime(&now);
			std::string date = std::to_string(ltm->tm_mday) + "-" + std::to_string(ltm->tm_mon) + "-" + std::to_string(ltm->tm_year + 1900);
			std::string hour = std::to_string(ltm->tm_hour) + "h" + std::to_string(ltm->tm_min) + "m" + std::to_string(ltm->tm_sec) + "s";
			return "_" + date + "_" + hour;
		}

		//The towerBalancer
		std::unique_ptr<TowerBalancer> towerBalancer;

		//The wave balancer
		std::unique_ptr<WaveBalancer> waveBalancer;
		int waveNbr{ -1 };

		//The parameter for the towerBalancer
		int bestFitness{ 0 };
		int nbrOfGenerationSinceImprovement{ 0 };
		std::vector<GeneticBot> bestBots;

		//Prepare the next generation and randomise some bots parameters
		void nextGeneration();

		//Get all the towers with a cost under diminishedPrice*priceGap
		std::vector<int> getAffordableTowers(int diminishedPrice) const;

		//Randomise a random percentage of all the valid value in the container with a value within the possible values
		void randomiseParameters(std::vector<int>* values, int randomPercent);

		void balanceGame(const std::vector<GeneticBot>& bots);

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

		//Update the bot manager, return true if the game is balanced
		bool update();

		//Get the bot list
		const std::vector<GeneticBot>& getBots() const;
		
		//Create the bots
		void createBots();

		//Load bots from a file
		void loadBots(std::string fileName = "default_bot_file.txt");

		//Setup the towerBalancer to allow it to execute
		/* buff and nerf attribute are function that take in parameter the tower to change
		 * desiredTowerUsage is the percent wanted for the tower usage (between 0 and 100)
		*/
		void setupTowerBalancer(std::function<void(int)> buffAttribute, std::function<void(int)> nerfAttribute, std::vector<std::array<int, 2>> desiredTowerUsageRange);

		//Setup the wave towerBalancer
		//buffWave and nerfWave take for parameter the wave number and buff / nerf this wave
		//nbrOfWave is the total number of wave present in the game
		void setupWaveBalancer(std::function<void(int)> buffWave, std::function<void(int)> nerfWave, int nbrOfWave);

		//Get the number of buff (or nerf) per tower or per wave. Does not check if the wave / tower balancer is set up
		std::vector<int> getNbrOfBuffPerWave() const { return waveBalancer->getNbrOfBuffPerWave(); }
		std::vector<int> getNbrOfBuffPerTower() const { return towerBalancer->getNbrOfBuffPerTower(); }
	};
}

