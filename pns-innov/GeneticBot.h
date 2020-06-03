#pragma once
#include <functional>
#include <vector>
#include <string>

#include "TowerManager.h"

namespace pns {
	class GeneticBot
	{
	private:
		//Where every decision is stored, with the x == the wave number and y == the money
		std::vector<int> decisionMap;

		int lastMoneyAmount{ 0 };
		int accumulatedMoney{ 0 };
		int towerPlaced{ 0 };

		std::vector<int> towerPlacedByType;
		//The position of the tower already placed
		std::set<std::array<int, 2>> towerAlreadyPlaced;
	public:
		/*Default constructor
		* decisionMap is the map of every decision the bot can take
		*/
		GeneticBot(std::vector<int> decisionMap = std::vector<int>{});

		//Make the bot play for this instant. The money gap is used if money is always the multiple of a number
		std::vector<std::array<int, 3>> play(std::function<int()> getMoney, const std::vector<int>& towersCost, const TowerManager& towerManager, int moneyGap = 1);

		//Get the decision map the bot updated
		const std::vector<int> getDecisionMap() const { return decisionMap; }

		//Get the fitness this bot reached
		int getFitness() const;

		//Print this bot in a file
		void print(const std::string& file) const;

		//Reset the bot except his decision map
		void reset();
	};
}
