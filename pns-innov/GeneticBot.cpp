#include "GeneticBot.h"

#include "Random.h"
#include "Values.h"

namespace pns {
	//Get all the position of the values under a certain point
	std::vector<int> getValuesUnder(const std::vector<int>& values, int max) {
		std::vector<int> goodValues;
		for (int i = 0; i != values.size(); i++) {
			if (values[i] <= max)
				goodValues.push_back(i);
		}
		return goodValues;
	}

	GeneticBot::GeneticBot(Container2D<int> decisionMap)
		: decisionMap{ decisionMap }
	{}

	void GeneticBot::play(std::function<int()> getMoney, std::function<void(int)> placeTower,
		const std::vector<int>& towersCost, int moneyGap) {
		//Manage the money
		if (getMoney() != lastMoneyAmount) {
			//If the bot won some money, remember it
			if (getMoney() > lastMoneyAmount)
				accumulatedMoney += getMoney() - lastMoneyAmount;
			lastMoneyAmount = getMoney();
		}

		//If the bot already have a plan for this situation and this plan is to place a tower
		if (decisionMap.exist(towerPlaced, getMoney() / moneyGap) && decisionMap.get(towerPlaced, getMoney() / moneyGap) > -1) {
			placeTower(decisionMap.get(towerPlaced, getMoney() / moneyGap));
			towerPlaced++;
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
					//And build it
					placeTower(decisionMap.get(towerPlaced, getMoney() / moneyGap));
					towerPlaced++;
				}
				else {
					decisionMap.set(towerPlaced, getMoney() / moneyGap, -2);
				}
			}
			//Else indicate that the bot cannot buy any tower for future iteration
			else
				decisionMap.set(towerPlaced, getMoney() / moneyGap, -1, -1);
		}
	}

	int GeneticBot::getFitness() const {
		return accumulatedMoney + lastMoneyAmount;
	}
}
