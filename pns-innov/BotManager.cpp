#include "BotManager.h"
#include <algorithm>
#include <string>
#include <ctime>

#include "Values.h"

#include <iostream>
#include <fstream>
#include <sstream>

using std::ifstream;

namespace pns {
	//Struct to make possible sorting the fitness of every bot and keep their position
	struct SortWithPos {
		int fitness, position;
		
		//Constructor to make thing easier
		SortWithPos(int fitness, int position) : fitness{ fitness }, position{ position } {}

		//Override operator < for the std::sort algorithm
		bool operator<(const SortWithPos& other) const { return fitness < other.fitness; }
	};

	const std::vector<GeneticBot>& BotManager::getBots() const { return bots; }

	BotManager::BotManager(std::function<bool()> hasWaveEnded, std::function<void()> startNextWave, std::function<bool()> hasGameEnded, std::function<void()> startNewGame,
		std::function<int()> getMoney, std::function<void(int, std::array<int, 2>)> placeTower, std::vector<int> towersCost, TowerManager towerManager, int moneyGap)
		: hasWaveEnded{ hasWaveEnded }, startNextWave{ startNextWave }, hasGameEnded{ hasGameEnded }, startNewGame{ startNewGame },
		getMoney{ getMoney }, placeTower{ placeTower }, towersCost{ towersCost }, towerManager{ towerManager }, moneyGap{ moneyGap }, stats{ nbrOfBotPerGeneration }
	{
	}

	bool BotManager::update() {
		//If no bots were created or loaded, create default bots
		if (bots.empty())
			createBots();

		//If the game ended, go to the next bot
		if (hasGameEnded()) {
			//If there is a wave balancer check if a bot did finish the game
			if (waveNbr > bestBotWave)
				bestBotWave = waveNbr;
			botIt++;
			waveNbr = -1;
			//If there is no more bots that need to play, go to the next generation
			if (botIt == bots.end()) {
				nextGeneration();
			}
			startNewGame();
		}
		//If the wave ended, go to the next one
		else if (hasWaveEnded()) {
			//If there is a wave balancer setup and the bot pass the wave it is working on,
			//balance the wave and start a new game with the same bot
			if (waveBalancer && waveBalancer->getCurrentBalancingWave() == waveNbr) {
				int balancedWave = waveBalancer->balanceWave(true);
				stats.setWaveBalancingValue(balancedWave, waveBalancer->getNbrOfBuffPerWave()[balancedWave]);
				startNewGame();
				waveNbr = -1;
				//Reset the bot
				botIt->reset();
			}
			else {
				startNextWave();
				waveNbr++;
			}
		}
		//Finally, if nothing special happened, let the bot play
		else {
			std::vector<std::array<int, 3>> towerToPlace{ botIt->play(getMoney, towersCost, towerManager, moneyGap) };
			if (!towerToPlace.empty()) {
				placeTower(towerToPlace[0][0], std::array<int, 2>{towerToPlace[0][1], towerToPlace[0][2]});
			}
		}
		//Return if the algorithm finish balancing the game
		if (towerBalancer && waveBalancer)
			return towerBalancer->didFinishBalance() && waveBalancer->didFinishBalance();
		else if (towerBalancer)
			return towerBalancer->didFinishBalance();
		else if (waveBalancer)
			return waveBalancer->didFinishBalance();
		else
			return false;
	}

	void BotManager::nextGeneration() {
		std::cout << "New generation";
		//Make a sorted vector with all the fitness of all the bot
		std::vector<SortWithPos> fitnessVector;
		for (int i = 0; i != bots.size(); i++) {
			fitnessVector.push_back({ bots[i].getFitness(), i });
			//Store fitness values for statistics
			stats.setFitnessValue(stats.balanceCounter, stats.genCounter, i, bots[i].getFitness());
		}
		//stats.displayFitnessValues(stats.balanceCounter, stats.genCounter);
		stats.displayAllWaveBalancingValues();
		stats.printFitnessValues(stats.fitnessValuesFile);
		stats.printWaveBalancingValues(stats.waveBalancingValuesFile);
		//increment necessary to record fitness values of next generation
		stats.genCounter++;
		//Sort the bots by increasing fitness
		std::sort(fitnessVector.begin(), fitnessVector.end());

		//If the best bot of this generation is improving compared to the last generation
		if (fitnessVector[fitnessVector.size() - 1].fitness > bestFitness) {
			std::cout << "Fitness improvement ! Previous: " << bestFitness;
			bestFitness = fitnessVector[fitnessVector.size() - 1].fitness;
			std::cout << ", actual: " << bestFitness;
			nbrOfGenerationSinceImprovement = 0;
			bestBots.push_back(bots[fitnessVector[fitnessVector.size() - 1].position]);
		}
		else
			nbrOfGenerationSinceImprovement++;

		for (int i = static_cast<int>(bots.size() - 1); bots[i].getFitness() == bestFitness; i--) {
			bestBots.push_back(bots[i]);
		}

		std::cout << std::endl;

		//If it is time to balance the bots
		if (nbrOfGenerationSinceImprovement == nbrOfStaleGenerationForReset) {
			balanceGame(bestBots);
			//Reset everything else
			bots.clear();
			createBots();
			nbrOfGenerationSinceImprovement = 0;
			bestFitness = 0;
			bestBots.clear();
			stats.nextBalance();
		}
		else {

			//The bot of the next generation
			std::vector<GeneticBot> newBots;
			//Where we start to take the best bots in the fitness vector
			int bestBotStart{ static_cast<int>(fitnessVector.size() - percentageOfBotKept * nbrOfBotPerGeneration / 100) };
			int i{ bestBotStart };
			while (newBots.size() < nbrOfBotPerGeneration) {
				//Randomise the bot parameters
				std::vector<int> newBotParameters{ bots[fitnessVector[i].position].getDecisionMap() };
				randomiseParameters(&newBotParameters, percentageOfParameterChanged);
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
	}

	void BotManager::balanceGame(const std::vector<GeneticBot>& newBots) {
		//If there is a wave balancer that did finish the balance but no bot finished the game, it's time to restart balancing
		if (waveBalancer && waveBalancer->didFinishBalance() && bestBotWave == waveBalancer->getNbrOfWave() - 1) {
			waveBalancer->restartBalance(bestBotWave);
			std::cout << "The bot can't finish the game ! Restarting the wave balancing proccess" << std::endl;
		}
		//Make the wave balancing if setup
		if (waveBalancer && !waveBalancer->didFinishBalance()) {
			int balancedWave = waveBalancer->balanceWave(false);
			stats.setWaveBalancingValue(balancedWave, waveBalancer->getNbrOfBuffPerWave()[balancedWave]);
		}
		//Make the tower balancing if setup with the new bots
		else if (towerBalancer && !towerBalancer->didFinishBalance()) {
			//Calculate the usage of each and every tower
			std::vector<double> towerUsage(towersCost.size(), 0);
			for (int i = 0; i != newBots.size(); i++) {
				for (int j = 0; j != newBots[i].getDecisionMap().size(); j++) {
					towerUsage[newBots[i].getDecisionMap()[j]]++;
				}
			}
			towerBalancer->balanceTowers(towerUsage);
		}
	}

	void BotManager::randomiseParameters(std::vector<int>* values, int randomPercent) {
		for (int i = 0; i != values->size(); i++) {
			if (Random::getRandomNumber() % 100 < randomPercent) {
				(*values)[i] = Random::getRandomNumber() % towersCost.size();
			}
		}
	}

	void BotManager::createBots() {
		std::cout << "Creating bots, with ";
		std::cout << stats.getNbrOfBots() << " bots per generation." << std::endl;
		for (int i = 0; i != nbrOfBotPerGeneration; i++) {
			bots.push_back(GeneticBot{});
		}
		botIt = bots.begin();
	}

	void BotManager::loadBots(std::string fileName) {
		ifstream ifs(fileName, ifstream::in);
		std::string line;
		std::vector<int> decisionMap = std::vector<int>();
		GeneticBot temp;
		if (ifs.is_open()) {
			while (!ifs.eof()) {
				getline(ifs, line, '\n');
				std::stringstream sep(line);
				std::string field;
				sep.str(line);
				while (getline(sep, field, ',')) {
					decisionMap.push_back(std::stoi(field));
				}
				bots.push_back(GeneticBot(decisionMap));
				decisionMap.clear();
			}
			ifs.close();
		}
		else {
			std::cerr << "cannot open file: " << fileName << std::endl;
		}
	}

	void BotManager::setupTowerBalancer(std::function<void(int)> buffAttribute, std::function<void(int)> nerfAttribute, std::vector<std::array<int, 2>> desiredTowerUsageRange) {
		//Create the list of towerBalancer objects
		std::vector<BalancerObject> balancerObjects;
		for (int i = 0; i != desiredTowerUsageRange.size(); i++) {
			BalancerAttribute attribute{ buffAttribute, nerfAttribute };
			BalancerObject object{ attribute, desiredTowerUsageRange[i], i };
			balancerObjects.push_back(object);
		}
		//Setup the towerBalancer
		towerBalancer = std::unique_ptr<TowerBalancer>{ new TowerBalancer{balancerObjects} };
	}

	void BotManager::setupWaveBalancer(std::function<void(int)> buffWave, std::function<void(int)> nerfWave, int nbrOfWave) {
		waveBalancer = std::unique_ptr<WaveBalancer>{ new WaveBalancer{buffWave, nerfWave, nbrOfWave} };
	}

}
