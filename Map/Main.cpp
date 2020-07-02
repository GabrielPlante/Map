#include "Core.h"
#undef main

#include <stdexcept>
#include <iostream>


int main() {

	try {
		map::Core::init();

		map::Core::getInstance()->run();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}

	//std::cin.get();

	return 0;
}