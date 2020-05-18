#pragma once
#include <vector>

namespace pns {
	//Container2D hold a 2D storage and provide a safe insert function. It cannot handle negative values
	template <typename T>
	class Container2D
	{
	private:
		std::vector<std::vector<T>> storage;
	public:
		//Insert a value at the position [x, y]. If new values need to be inserted, the defaultValue is inserted
		void insert(int x, int y, T value, T defaultValue = 0);

		//Get the value stored at the position [x, y]
		T get(int x, int y) const { return storage[x][y]; }

		//Is there a value at the position [x, y]
		bool exist(int x, int y) const;
	};

	template <typename T>
	void Container2D<T>::insert(int x, int y, T value, T defaultValue) {
		//Make sure the x dimension is large enough
		while (storage.size() <= x) {
			storage.push_back(std::vector<T>{});
		}
		//Make sure the y dimension is large enough
		while (storage[x].size() <= y) {
			storage[x].push_back(defaultValue);
		}
		//Insert the element
		storage[x].insert(storage[x].begin() + y, value);
	}

	template <typename T>
	bool Container2D<T>::exist(int x, int y) const {
		return storage.size() > x && storage[x].size() > y;
	}
}

