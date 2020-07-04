#include "pch.h"

#include <SDL.h>
#undef main

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	SDL_Init(SDL_INIT_VIDEO);

	return RUN_ALL_TESTS();
}