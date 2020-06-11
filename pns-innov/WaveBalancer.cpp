#include "WaveBalancer.h"

#include "Random.h"

#include <iostream>

namespace pns {
	WaveBalancer::WaveBalancer(const std::vector<BalancerAttribute>& attributes, int nbrOfWave)
		: attributes{ attributes }, nbrOfWave{ nbrOfWave }
	{
		for (int i = 0; i != attributes.size(); i++) {
			attributePrioritySum += attributes[i].getPriority();
		}
	}

	int WaveBalancer::balanceWave(bool didBotPass) {
		int attributeId{ 0 };

		//Choose a random number to get the attribute to balance
		int randomNumber{ Random::getRandomNumber() % attributePrioritySum };

		int priority{ 0 };
		//Find at wich attribute the random number belong
		for (int i = 0; i != attributes.size(); i++) {
			priority += attributes[i].getPriority();
			if (randomNumber < priority) {
				attributeId = i;
				break;
			}
		}

		int balancedWave = currentBalancingWave;
		if (nbrOfBuffPerWave.size() <= currentBalancingWave)
			nbrOfBuffPerWave.push_back(0);
		if (didBotPass) {
			attributes[attributeId].buff(currentBalancingWave);
			std::cout << "Buffing the wave number: " << currentBalancingWave << std::endl;
			nbrOfBuffPerWave[currentBalancingWave]++;
			hasWonThisWave = true;
		}
		else {
			attributes[attributeId].nerf(currentBalancingWave);
			std::cout << "Nerfing the wave number: " << currentBalancingWave << std::endl;
			nbrOfBuffPerWave[currentBalancingWave]--;
			if (hasWonThisWave) {
				currentBalancingWave++;
				if (currentBalancingWave == nbrOfWave) {
					finishedBalancing = true;
				}
				hasWonThisWave = false;
			}
		}
		return balancedWave;
	}
}
