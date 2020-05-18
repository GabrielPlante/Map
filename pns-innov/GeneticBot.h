#pragma once
#include <functional>
#include <vector>

#include "Container2D.h"

namespace pns {
	class GeneticBot
	{
	private:
		//The parameter used for the bot to work
		std::function<int()> getMoney;
		std::function<int()> getCurrentWave;
		std::function<void(int)> placeTower;
		std::vector<int> towersCost;

		//Where every decision is stored
		Container2D<int> decisionMap;
	public:
		/*Default constructor
		* getMoney is a function that should return the money the player have
		* getCurrentWave is a function that should return the wave nbr the player currently is
		* placeTower is a function that should place a tower on an optimal position when called
		* towersCost is a vector that contain each cost of each tower
		* decisionMap is the map of every 
		*/
		GeneticBot(std::function<int()> getMoney, std::function<int()> getCurrentWave, std::function<void(int)> placeTower, std::vector<int> towersCost,
			Container2D<int> decisionMap = Container2D<int>{});

		//Update the bot, allowing him to play
		void update();

		//Get the decision map the bot updated
		const Container2D<int> getDecisionMap() const { return decisionMap; }
	};
}
