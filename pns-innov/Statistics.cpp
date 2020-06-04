#include "Statistics.h"
#include "FileWriter.h"

#include <iostream>
#include <direct.h>

namespace pns {

	Statistics::Statistics(int nbrOfBots)
		: nbrOfBots{ nbrOfBots }, genCounter(0), balanceCounter(0)
	{
		fitnessValues.push_back(Container2D<int>());
		mkdir("../pns-innov/runs/fitness");
		mkdir("../pns-innov/runs/wave_balancing");
		mkdir("../pns-innov/runs/tower_balancing");
		mkdir("../pns-innov/runs/tower_usage");
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

	void Statistics::printWaveBalancingValues(const std::string& file) const {
		waveBalancingValues.print(file);
	}

	void Statistics::setTowerBalancingValue(std::vector<int> balancingValues) {
		for (int i = 0; i < balancingValues.size(); i++)
		{
			towerBalancingValues.add(balanceCounter, balancingValues[i]);
		}
	}

	void Statistics::displayAllTowerBalancingValues() {
		for (int i = 0; i < towerBalancingValues.size(); i++)
		{
			std::cout << std::endl;
			for (int j = 0; j < towerBalancingValues.sizeOfRow(i); j++)
			{
				std::cout << towerBalancingValues.get(i, j) << " ";
			}
			std::cout << std::endl;
		}

	}

	void Statistics::printTowerBalancingValues(const std::string& file) const {
		towerBalancingValues.print(file);
	}

	void Statistics::setTowerUsageValue(std::vector<double> towerUsage) {
		for (int i = 0; i < towerUsage.size(); i++)
		{
			towerUsageValues.add(balanceCounter, towerUsage[i]);
		}
	}

	void Statistics::displayAllTowerUsageValues() {
		for (int i = 0; i < towerUsageValues.size(); i++)
		{
			std::cout << std::endl;
			for (int j = 0; j < towerUsageValues.sizeOfRow(i); j++)
			{
				std::cout << towerUsageValues.get(i, j) << " ";
			}
			std::cout << std::endl;
		}
	}

	void Statistics::printTowerUsageValues(const std::string& file) const {
		towerUsageValues.print(file);
	}

}