#pragma once
#include <stdlib.h>

namespace map {
	//Get a random number with a higher chance of getting a number in the middle of the interval
	int randomNumberHarmonised(int max, int min = 0) {
		return (rand() % (max - min) / 2) + (rand() % (max - min) / 2) + min;
	}
}
