#pragma once
#include <functional>
#include <vector>

#include "BalancerObject.h"

namespace pns {
	class TowerBalancer
	{
	private:
		std::vector<BalancerObject> objects;

		bool finishedBalancing{ false };
	public:
		//Constructor
		TowerBalancer(const std::vector<BalancerObject>& objects) : objects{ objects } {}

		//Set the current usage for an object
		bool setCurrentUsage(int id, int usage) { return objects[id].balanceObject(usage); }

		//Balance a set of tower
		void balanceTowers(const std::vector<double>& towersUsage);

		//Did the algorithme finish it's balancing
		bool didFinishBalance() const { return finishedBalancing; }

		//Get the number of buff (or nerf) every tower had
		std::vector<int> getNbrOfBuffPerTower() const;

		//Get the change for each attribute of each tower
		std::vector<std::vector<std::array<int, 2>>> getEnhancedChange() const;
	};
}
