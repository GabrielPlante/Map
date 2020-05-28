#pragma once
#include <functional>
#include <vector>


namespace pns {
	class WaveBalancer
	{
	private:
		std::function<void(int)> buffWave;
		std::function<void(int)> nerfWave;

		int nbrOfWave;

		int currentBalancingWave{ 0 };
		//Did the bot already beat this wave ?
		bool hasWonThisWave{ false };

		std::vector<int> nbrOfBuffPerWave;

		bool finishedBalancing{ false };
	public:
		//Constructor
		//buffWave and nerfWave take for parameter the wave number and buff / nerf this wave
		WaveBalancer(std::function<void(int)> buffWave, std::function<void(int)> nerfWave, int nbrOfWave);

		//Balance the actual wave
		void balanceWave(bool didBotPass);

		//Get the wave the algorithm is currently balancing
		int getCurrentBalancingWave() const { return currentBalancingWave; }

		//Get the vector indicate how many time the wave has been buffed (or nerfed)
		const std::vector<int>& getNbrOfBuffPerWave() const { return nbrOfBuffPerWave; }

		//Did the algorithme finish it's balancing
		bool didFinishBalance() const { return finishedBalancing; }
	};
}

