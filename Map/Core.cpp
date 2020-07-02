#include "Core.h"

namespace map {
	Core* Core::instance{ nullptr };

	void Core::init() { instance = new Core{}; }

	void Core::quit() {
		if (instance)
			delete instance;
	}

	void Core::run() {

	}

}
