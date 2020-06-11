#pragma once
#include <array>
#include <vector>

#include "BalancerAttribute.h"

namespace pns {
	//This class represent a game object that hold some attribute. For the first sprint it only store one attribute
	class BalancerObject {
	private:
		std::vector<BalancerAttribute> attribute;
		std::array<int, 2> desiredUsageRange;
		int id;

		int attributePrioritySum{ 0 };

		int nbrOfBuff{ 0 };
	public:
		//Constructor
		BalancerObject(const std::vector<BalancerAttribute>& attribute, std::array<int, 2> desiredUsageRange, int id);

		//Balance this object based on the current win rate of this object. Return true if the object is balanced
		bool balanceObject(int currentUsage);

		//Get the number of buff (or nerf) this object had
		int getNbrOfBuff() const { return nbrOfBuff; }
	};

}
