#include "TowerBalancer.h"

namespace pns {

	void TowerBalancer::balanceTowers(const std::vector<double>& towersUsage) {
		//Calculate the total number of tower used
		double nbrOfTowerUsed{ 0 };
		for (int i = 0; i != towersUsage.size(); i++) {
			nbrOfTowerUsed += towersUsage[i];
		}
		//Var to know if every is balanced
		bool isBalanced{ true };
		//Set the current usage for every tower so the balancer can do his stuff
		for (int i = 0; i != towersUsage.size(); i++) {
			double towerUsage{ towersUsage[i] * 100 / nbrOfTowerUsed };
			std::cout << "Tower usage of " << i << ": " << towerUsage << ".";
			isBalanced &= setCurrentUsage(i, static_cast<int>(towerUsage));
		}
		finishedBalancing = isBalanced;
	}

	std::vector<int> TowerBalancer::getNbrOfBuffPerTower() const {
		std::vector<int> nbrOfBuffPerTower;
		for (int i = 0; i != objects.size(); i++) {
			nbrOfBuffPerTower.push_back(objects[i].getNbrOfBuff());
		}
		return nbrOfBuffPerTower;
	}

	std::vector<std::vector<std::array<int, 2>>> TowerBalancer::getEnhancedChange() const {
		std::vector<std::vector<std::array<int, 2>>> vec;
		for (int i = 0; i != objects.size(); i++) {
			vec.push_back(objects[i].getEnhancedChange());
		}
		return vec;
	}
}
