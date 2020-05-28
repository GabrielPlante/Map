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

		int nbrOfBuff{ 0 };
	public:
		//Constructor
		BalancerObject(const BalancerAttribute& attribute, std::array<int, 2> desiredUsageRange, int id)
			: attribute{ attribute }, desiredUsageRange{ desiredUsageRange }, id{ id } {}

		//Balance this object based on the current win rate of this object. Return true if the object is balanced
		bool balanceObject(int currentUsage) {
			if (currentUsage > desiredUsageRange[1]) {
				attribute.nerf(id);
				nbrOfBuff--;
			}
			else if (currentUsage < desiredUsageRange[0]) {
				attribute.buff(id);
				nbrOfBuff++;
			}
			else
				return true;
			return false;
		}

		//Get the number of buff (or nerf) this object had
		int getNbrOfBuff() const { return nbrOfBuff; }
	};

}
