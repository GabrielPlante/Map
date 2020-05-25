#include "Statistics.h"

#include <iostream>

namespace pns {

	Statistics::Statistics(int nbrOfBots)
		: nbrOfBots{ nbrOfBots }, genCounter(0)
	{
	}

	const int Statistics::getNbrOfBots()
	{
		return nbrOfBots;
	}

	const Container2D<int> Statistics::getFitnessValues() {
		return fitnessValues;
	}

	void Statistics::set(int generation, int bot, int value)
	{
		fitnessValues.set(generation, bot, value);
	}

	void Statistics::display()
	{
		for (int i = 0; i < genCounter; i++)
		{
			std::cout << "Generation " << i << " :" << std::endl;
			for (int j = 0; j < nbrOfBots; j++)
			{
				std::cout << j << " : " << (int) fitnessValues.get(i, j) << ", ";
			}
			std::cout << std::endl;
		}
	}
}