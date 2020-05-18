#include "GeneticBot.h"

namespace pns {
	GeneticBot::GeneticBot(std::function<int()> getMoney, std::function<int()> getCurrentWave, std::function<void(int)> placeTower, std::vector<int> towersCost,
		Container2D<int> decisionMap)
		: getMoney{ getMoney }, getCurrentWave{ getCurrentWave }, placeTower{ placeTower }, towersCost{ towersCost }, decisionMap{ decisionMap }
	{}
}
