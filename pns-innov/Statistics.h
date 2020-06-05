#pragma once

#include <vector>
#include <string>
#include <ctime>
#pragma warning(disable : 4996)
#include "FileWriter.h"
#include "Container2D.h"


namespace pns {
	class Statistics
	{
	private:

		//number of bots per generation
		int nbrOfBots;
		std::vector<Container2D<int>> fitnessValues;
		Container2D<int> waveBalancingValues;
		Container2D<int> towerBalancingValues;
		Container2D<double> towerUsageValues;


		//to store statistics of each run in different files
		time_t now = time(0);
		std::string getFileId() {
			tm* ltm = localtime(&now);
			std::string date = std::to_string(ltm->tm_mday) + "-" + std::to_string(ltm->tm_mon) + "-" + std::to_string(ltm->tm_year + 1900);
			std::string hour = std::to_string(ltm->tm_hour) + "h" + std::to_string(ltm->tm_min) + "m" + std::to_string(ltm->tm_sec) + "s";
			return "_" + date + "_" + hour;
		}

	public:
		int genCounter;
		int balanceCounter;
		std::string fitnessValuesFile = "../pns-innov/runs/fitness/fitness_values" + getFileId() + ".txt";
		std::string waveBalancingValuesFile = "../pns-innov/runs/wave_balancing/wave_balancing_values" + getFileId() + ".txt";
		std::string towerBalancingValuesFile = "../pns-innov/runs/tower_balancing/tower_balancing_values" + getFileId() + ".txt";
		std::string towerUsageValuesFile = "../pns-innov/runs/tower_usage/tower_usage_values" + getFileId() + ".txt";

		Statistics(int nbrOfBots);

		const int getNbrOfBots();

		const std::vector<Container2D<int>> getFitnessValues();

		void setFitnessValue(int balance, int generation, int bot, int value);

		void displayFitnessValues(int balance, int generation);

		void displayAllFitnessValues();

		//reset genCounter, create a new container to store values of next balance
		void nextBalance(); 

		//store fitness values in a file
		const std::vector<Container2D<int>>& printFitnessValues(const std::string& file) const;

		void setWaveBalancingValue(int wave, int value);

		void displayAllWaveBalancingValues();

		//store wave balancing values in a file
		void printWaveBalancingValues(const std::string& file) const;

		void setTowerBalancingValue(std::vector<int> balancingValues);

		void displayAllTowerBalancingValues();

		//store tower balancing values in a file
		void printTowerBalancingValues(const std::string& file) const;

		void setTowerUsageValue(std::vector<double> towerUsage);

		void displayAllTowerUsageValues();

		//store tower usage values in a file
		void printTowerUsageValues(const std::string& file) const;
	};
}