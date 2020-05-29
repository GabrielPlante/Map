#pragma once

namespace pns {
	struct Random {
	private:
		static bool isInitialized;

	public:
		static int getRandomNumber();
	};
}
