#include "BalancerObject.h"

#include "Random.h"

namespace pns {
	BalancerObject::BalancerObject(const std::vector<BalancerAttribute>& attribute, std::array<int, 2> desiredUsageRange, int id)
		: attribute{ attribute }, desiredUsageRange{ desiredUsageRange }, id{ id } {
		//Sum the attribute priority and keep it
		for (int i = 0; i != attribute.size(); i++) {
			attributePrioritySum += attribute[i].getPriority();
		}
	}

	bool BalancerObject::balanceObject(int currentUsage) {
		int attributeId{ 0 };

		//Choose a random number to get the attribute to balance
		int randomNumber{ Random::getRandomNumber() % attributePrioritySum };

		int priority{ 0 };
		//Find at wich attribute the random number belong
		for (int i = 0; i != attribute.size(); i++) {
			priority += attribute[i].getPriority();
			if (randomNumber < priority) {
				attributeId = i;
				break;
			}
		}

		if (currentUsage > desiredUsageRange[1]) {
			attribute[attributeId].nerf(id);
			nbrOfBuff--;
		}
		else if (currentUsage < desiredUsageRange[0]) {
			attribute[attributeId].buff(id);
			nbrOfBuff++;
		}
		else
			return true;
		return false;
	}
}
