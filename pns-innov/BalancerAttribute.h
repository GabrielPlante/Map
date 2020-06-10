#pragma once
#include <functional>

#include <iostream>

namespace pns {
	//This class is used to balance an attribute
	class BalancerAttribute {
	private:
		std::function<void(int)> buffAttribute;
		std::function<void(int)> nerfAttribute;

		int priority;
	public:
		//Constructor
		BalancerAttribute(std::function<void(int)> buffAttribute, std::function<void(int)> nerfAttribute, int priority = 1)
			: buffAttribute{ buffAttribute }, nerfAttribute{ nerfAttribute }, priority{ priority }
		{}

		//Buff this attribute
		void buff(int id) { buffAttribute(id); std::cout << "Buffing " << id << std::endl; }

		//Nerf this attribute
		void nerf(int id) { nerfAttribute(id); std::cout << "Nerfing " << id << std::endl; }

		//Get the priority of this attribute
		int getPriority() const { return priority; }
	};
}
