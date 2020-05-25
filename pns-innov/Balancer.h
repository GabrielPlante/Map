#pragma once
#include <functional>
#include <vector>

#include "BalancerObject.h"

namespace pns {
	class Balancer
	{
	private:
		std::vector<BalancerObject> objects;

	public:
		//Constructor
		Balancer(const std::vector<BalancerObject>& objects) : objects{ objects } {}

		//Set the current usage for an object
		void setCurrentUsage(int id, int usage) { objects[id].balanceObject(usage); }
	};
}
