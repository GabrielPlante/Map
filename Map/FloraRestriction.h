#pragma once

namespace map {
	template <typename T>
	struct FloraRestriction {
		//The restriction
		T restriction;

		//The survival time outside the restriction, in ticks
		int survivalTime;
	};
}
