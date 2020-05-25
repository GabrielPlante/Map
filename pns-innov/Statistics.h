#pragma once

#include <vector>
#include <string>

#include "Container2D.h"


namespace pns {
	class Statistics
	{
	private:

		int nbrOfBots;
		Container2D<int> fitnessValues;

	public:
		int genCounter;

		Statistics(int nbrOfBots);

		const int getNbrOfBots();

		const Container2D<int> getFitnessValues();

		void set(int generation, int bot, int value);

		void display();

	};
}