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
		void setCurrentUsage(int id, int usage) { objects[id].balanceObject(usage); }

		//Did the algorithme finish it's balancing
		bool didFinishBalance() const { return finishedBalancing; }
	};
}
