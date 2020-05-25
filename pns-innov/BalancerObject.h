#pragma once
#include <array>

#include "BalancerAttribute.h"

namespace pns {
	//This class represent a game object that hold some attribute. For the first sprint it only store one attribute
	class BalancerObject {
	private:
		BalancerAttribute attribute;
		std::array<int, 2> desiredUsageRange;
		int id;
	public:
		//Constructor
		BalancerObject(const BalancerAttribute& attribute, std::array<int, 2> desiredUsageRange, int id)
			: attribute{ attribute }, desiredUsageRange{ desiredUsageRange }, id{ id } {}

		//Balance this object based on the current win rate of this object
		void balanceObject(int currentUsage) {
			if (currentUsage > desiredUsageRange[1])
				attribute.nerf(id);
			else if (currentUsage < desiredUsageRange[0])
				attribute.buff(id);
		}
	};

}
