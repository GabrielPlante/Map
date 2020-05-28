#include "WaveBalancer.h"

#include <iostream>

namespace pns {
	WaveBalancer::WaveBalancer(std::function<void(int)> buffWave, std::function<void(int)> nerfWave, int nbrOfWave)
		: buffWave{ buffWave }, nerfWave{ nerfWave }, nbrOfWave{ nbrOfWave }
	{}

	void WaveBalancer::balanceWave(bool didBotPass) {
		if (nbrOfBuffPerWave.size() <= currentBalancingWave)
			nbrOfBuffPerWave.push_back(0);
		if (didBotPass) {
			buffWave(currentBalancingWave);
			std::cout << "Buffing the wave number: " << currentBalancingWave << std::endl;
			nbrOfBuffPerWave[currentBalancingWave]++;
			hasWonThisWave = true;
		}
		else {
			nerfWave(currentBalancingWave);
			std::cout << "Nerfing the wave number: " << currentBalancingWave << std::endl;
			nbrOfBuffPerWave[currentBalancingWave]--;
			if (hasWonThisWave) {
				currentBalancingWave++;
				if (currentBalancingWave == nbrOfWave)
					finishedBalancing = true;
				hasWonThisWave = false;
			}
		}
	}
}
