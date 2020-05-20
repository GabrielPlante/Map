#pragma once
#include <functional>
#include <vector>

#include "Container2D.h"

namespace pns {
	class GeneticBot
	{
	private:
		//Where every decision is stored, with the x == the wave number and y == the money
		Container2D<int> decisionMap;

		int lastMoneyAmount{ 0 };
		int accumulatedMoney{ 0 };
		int towerPlaced{ 0 };

		std::vector<int> towerPlacedByType;
	public:
		/*Default constructor
		* decisionMap is the map of every decision the bot can take
		*/
		GeneticBot(Container2D<int> decisionMap = Container2D<int>{});

		//Make the bot play for this instant. The money gap is used if money is always the multiple of a number
		void play(std::function<int()> getMoney, std::function<void(int, int)> placeTower,
			const std::vector<int>& towersCost, int moneyGap = 1);

		//Get the decision map the bot updated
		const Container2D<int> getDecisionMap() const { return decisionMap; }

		//Get the fitness this bot reached
		int getFitness() const;
	};
}
