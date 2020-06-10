#include "GeneticBot.h"

#include "Random.h"
#include "Values.h"
#include <iostream>
namespace pns {
	using std::cout;
	//Get all the position of the values under a certain point
	std::vector<int> GeneticBot::getValuesUnder(const std::vector<int>& values, int max) {
		std::vector<int> goodValues;
		for (int i = 0; i != values.size(); i++) {
			//cout << "xv(i)= " << values[i] << std::endl;
			if (values[i] <= max)
				goodValues.push_back(i);
		}
		return goodValues;
	}

	GeneticBot::GeneticBot(std::vector<int> decisionMap)
		: decisionMap{ decisionMap }
	{}

	std::vector<std::array<int, 3>> GeneticBot::play(std::function<int()> getMoney, const std::vector<int>& towersCost, const TowerManager& towerManager, int) {
		std::vector<std::array<int, 3>> towerPlacedVector;
		if (towerPlacedByType.empty()) {
			towerPlacedByType = std::vector<int>(towersCost.size(), 0);
		}
		//Manage the money
		if (getMoney() != lastMoneyAmount) {
			//If the bot won some money, remember it
			if (getMoney() > lastMoneyAmount)
				accumulatedMoney += getMoney() - lastMoneyAmount;
			lastMoneyAmount = getMoney();
		}

		//Test of a new bot memory, a simple vector with the tower to buy in order
		//If the bot don't have a plan
		if (decisionMap.size() <= towerPlaced) {
			decisionMap.push_back(Random::getRandomNumber() % towersCost.size());
		}
		//If the bot can afford the tower
		if (towersCost[decisionMap[towerPlaced]] <= getMoney()) {
			int towerType{ decisionMap[towerPlaced] };
			//Get the position of the tower that will be placed
			std::array<int, 2> towerPlacedArray{ towerManager.getBestTowerPosition(towerType, towerPlacedByType[towerType], towerAlreadyPlaced) };
			//Add it to the list of tower already placed
			towerAlreadyPlaced.insert(towerPlacedArray);
			//Add it to the vector of tower we will return
			towerPlacedVector.push_back({ towerType, towerPlacedArray[0], towerPlacedArray[1] });
			towerPlaced++;
			towerPlacedByType[towerType]++;
		}

		return towerPlacedVector;

		//If the bot already have a plan for this situation and this plan is to place a tower
		/*if (decisionMap.exist(towerPlaced, getMoney() / moneyGap) && decisionMap.get(towerPlaced, getMoney() / moneyGap) > -1) {
			int towerType{ decisionMap.get(towerPlaced, getMoney() / moneyGap) };
			placeTower(towerType, towerPlacedByType[towerType]);
			towerPlaced++;
			towerPlacedByType[towerType]++;
		}
		//If the bot doesn't have any plan
		else if (!decisionMap.exist(towerPlaced, getMoney()/moneyGap)){
			//Get all the towers we can afford
			std::vector<int> affordableTowers{ getValuesUnder(towersCost, getMoney()) };
			//If the bot can afford it
			if (!affordableTowers.empty()) {
				//If it decide to build a tower
				if (Random::getRandomNumber() % 100 < chanceToBuildTower) {
					decisionMap.set(towerPlaced, getMoney() / moneyGap, affordableTowers[Random::getRandomNumber() % affordableTowers.size()], -1);
					int towerType{ decisionMap.get(towerPlaced, getMoney() / moneyGap) };
					//And build it
					placeTower(towerType, towerPlacedByType[towerType]);
					towerPlaced++;
					towerPlacedByType[towerType]++;
				}
				else {
					decisionMap.set(towerPlaced, getMoney() / moneyGap, -2);
				}
			}
			//Else indicate that the bot cannot buy any tower for future iteration
			else
				decisionMap.set(towerPlaced, getMoney() / moneyGap, -1, -1);
		}*/
	}

	int GeneticBot::getFitness() const {
		return accumulatedMoney;
	}

	void GeneticBot::reset() {
		lastMoneyAmount = 0;
		accumulatedMoney = 0;
		towerPlaced = 0;
		towerPlacedByType.clear();
	}
}
