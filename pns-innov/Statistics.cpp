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

	void Statistics::set(int generation, int bot, int value)
	{
		fitnessValues.set(generation, bot, value);
	}

	void Statistics::display()
	{
		for (int i = 0; i < genCounter; i++)
		{
			cout << "Generation " << i << " :" << endl;
			for (int j = 0; j < nbrOfBots; j++)
			{
				cout << j << " : " << (int) fitnessValues.get(i, j) << ", ";
			}
			cout << endl;
		}
	}
}