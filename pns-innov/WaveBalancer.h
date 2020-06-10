#pragma once
#include <functional>
#include <vector>

#include "BalancerAttribute.h"


namespace pns {
	class WaveBalancer
	{
	private:
		std::vector<BalancerAttribute> attributes;
		int attributePrioritySum{ 0 };

		int nbrOfWave;

		int currentBalancingWave{ 0 };
		//Did the bot already beat this wave ?
		bool hasWonThisWave{ false };

		std::vector<int> nbrOfBuffPerWave;

		bool finishedBalancing{ false };
	public:
		//Constructor
		//buffWave and nerfWave take for parameter the wave number and buff / nerf this wave
		WaveBalancer(const std::vector<BalancerAttribute>& attributes, int nbrOfWave);

		//Balance the actual wave
		int balanceWave(bool didBotPass);

		//Get the wave the algorithm is currently balancing
		int getCurrentBalancingWave() const { return currentBalancingWave; }

		//Get the vector indicate how many time the wave has been buffed (or nerfed)
		const std::vector<int>& getNbrOfBuffPerWave() const { return nbrOfBuffPerWave; }

		//Did the algorithme finish it's balancing
		bool didFinishBalance() const { return finishedBalancing; }

		//Restart the balance process
		void restartBalance(int waveToStartBalance) { finishedBalancing = false; currentBalancingWave = waveToStartBalance; }

		//Get the number of wave in the game
		int getNbrOfWave() const { return nbrOfWave; }
	};
}

