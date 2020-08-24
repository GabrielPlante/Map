#include "FloraStorage.h"

namespace map {
	FloraComponent defaultComponent() {
		return FloraComponent{ FloraRestriction<ge::Vector2<float>>{}, FloraRestriction<float>{-1, 0} };
	}
	bool isValid(const FloraComponent& flora) {
		return flora.maxWater.restriction != -1;
	}
	ge::VectorOfVector<FloraComponent> FloraStorage::floraStorage{ defaultComponent, isValid };
}
