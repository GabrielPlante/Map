#pragma once
#include <functional>

#include <iostream>

namespace pns {
	//This class is used to balance an attribute
	class BalancerAttribute {
	private:
		std::function<void(int)> buffAttribute;
		std::function<void(int)> nerfAttribute;
	public:
		//Constructor
		BalancerAttribute(std::function<void(int)> buffAttribute, std::function<void(int)> nerfAttribute)
			: buffAttribute{ buffAttribute }, nerfAttribute{ nerfAttribute }
		{}

		//Buff this attribute
		void buff(int id) { buffAttribute(id); std::cout << "Buffing " << id << std::endl; }

		//Nerf this attribute
		void nerf(int id) { nerfAttribute(id); std::cout << "Nerfing " << id << std::endl; }
	};
}
