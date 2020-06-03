#include "Statistics.h"
#include "FileWriter.h"

#include <iostream>
#include <direct.h>

namespace pns {

	Statistics::Statistics(int nbrOfBots)
		: nbrOfBots{ nbrOfBots }, genCounter(0), balanceCounter(0)
	{
		fitnessValues.push_back(Container2D<int>());
		std::cout << mkdir("../pns-innov/runs/fitness") << std::endl;
		std::cout << mkdir("../pns-innov/runs/wave_balancing") << std::endl;

	}

	const int Statistics::getNbrOfBots()
	{
		return nbrOfBots;
	}

	const std::vector<Container2D<int>> Statistics::getFitnessValues() {
		return fitnessValues;
	}

	void Statistics::setFitnessValue(int balance, int generation, int bot, int value)
	{
		fitnessValues[balance].set(generation, bot, value);
	}

	void Statistics::displayFitnessValues(int balance, int generation)
	{
		std::cout << "Balance : " << balanceCounter + 1 << ", Generation : " << genCounter + 1 << std::endl;
		for (int i = 0; i < (int) nbrOfBots - 1; i++)
		{
			std::cout << i << " : " << (int) fitnessValues[balance].get(generation, i) << ", ";
		}
		std::cout << nbrOfBots - 1 << " : " << (int)fitnessValues[balance].get(generation, nbrOfBots - 1) << std::endl;
	}

	void Statistics::displayAllFitnessValues()
	{
		for (int k = 0; k < balanceCounter; k++) 
		{
			std::cout << std::endl;
			std::cout << "Balance " << k + 1 << " :" << std::endl;

			for (int i = 0; i < fitnessValues[k].size(); i++)
			{
				std::cout << "Generation " << i + 1 << " :" << std::endl;
				for (int j = 0; j < nbrOfBots; j++)
				{
					std::cout << j + 1<< " : " << (int)fitnessValues[k].get(i, j) << ", ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}

	void Statistics::nextBalance() {
		fitnessValues.push_back(Container2D<int>());
		balanceCounter++;
		genCounter = 0;
	}

	const std::vector<Container2D<int>>& Statistics::printFitnessValues(const std::string& file) const{
		FileWriter fileWriter(file);
		for (int k = 0; k < fitnessValues.size(); k++) {
			for (int i = 0; i != fitnessValues[k].size(); i++) {
				for (int j = 0; j != nbrOfBots; j++) {
					fileWriter.write(std::to_string(fitnessValues[k].get(i, j)) + " ");
				}
				fileWriter.write(";");
			}
			fileWriter.write("\n");
		}
		return fitnessValues;
	}

	void Statistics::setWaveBalancingValue(int wave, int value) {
		waveBalancingValues.add(wave, value);
	}

	void Statistics::displayAllWaveBalancingValues() {
		for (int i = 0; i < waveBalancingValues.size(); i++)
		{
			std::cout << "wave " << i << ":" << std::endl;
			for (int j = 0; j < waveBalancingValues.sizeOfRow(i); j++)
			{
				std::cout << waveBalancingValues.get(i, j) << " ";
			}
			std::cout << std::endl;
		}
	}


	const Container2D<int>& Statistics::printWaveBalancingValues(const std::string& file) const {
		FileWriter fileWriter(file);
		for (int k = 0; k < waveBalancingValues.size(); k++) {
			for (int i = 0; i != waveBalancingValues.sizeOfRow(k); i++) {
				fileWriter.write(std::to_string(waveBalancingValues.get(k, i)) + " ");
			}
			fileWriter.write("\n");
		}
		return waveBalancingValues;
	}

}