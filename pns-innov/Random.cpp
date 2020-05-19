#include "Random.h"

#include <time.h>
#include <stdlib.h>

namespace pns {
	bool Random::isInitialized{ false };

	int Random::getRandomNumber() {
		if (!isInitialized) {
			srand(static_cast<unsigned int>(time(NULL)));
			isInitialized = true;
		}
		return rand();
	}
}