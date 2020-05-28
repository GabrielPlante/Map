#pragma once
#include <functional>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "FileWriter.h"
#include "Random.h"

namespace pns {
	//Container2D hold a 2D storage and provide a safe insert function. It cannot handle negative values
	template <typename T>
	class Container2D
	{
	private:
		std::vector<std::vector<T>> storage;
	public:
		//Set a value at the position [x, y]. If new values need to be inserted, the defaultValue is inserted
		void set(int x, int y, T value, T defaultValue = 0);

		//Get the value stored at the position [x, y]
		T get(int x, int y) const { return storage[x][y]; }

		//Get size of the storage
		int size() const { return (int) storage.size(); }
		
		//Get size of row x
		int sizeOfRow(int x) const { return (int) storage[x].size(); }

		//Is there a value at the position [x, y]
		bool exist(int x, int y) const;

		//Is there a vector at the position x
		bool exist(int x) const { return storage.size() > x; }

		//Randomise a random percentage of all the valid value of the container with a value within the possible values
		void randomiseValues(std::function<std::vector<int>(int)> possibleValues, int randomPercent, int unvalidValue = -1);

		//Print the container to a file
		const Container2D& print(const std::string& file) const;
	};

	template <typename T>
	void Container2D<T>::set(int x, int y, T value, T defaultValue) {
		//Make sure the x dimension is large enough
		while (storage.size() <= x) {
			storage.push_back(std::vector<T>{});
		}
		//Make sure the y dimension is large enough
		while (storage[x].size() <= y) {
			storage[x].push_back(defaultValue);
		}
		//Insert the element
		storage[x][y] = value;
	}

	template <typename T>
	bool Container2D<T>::exist(int x, int y) const {
		return storage.size() > x && storage[x].size() > y;
	}

	template <typename T>
	void Container2D<T>::randomiseValues(std::function<std::vector<int>(int)> possibleValues, int randomPercent, int unvalidValue) {
		//For every value in this container
		for (int i = 0; i != storage.size(); i++) {
			for (int j = 0; j != storage[i].size(); j++) {
				//If it is not the unvalid value and it is chosen for a reassignement
				if (storage[i][j] != unvalidValue && Random::getRandomNumber() % 100 < randomPercent) {
					//Change it to a valid value
					std::vector<int> validValues{ possibleValues(j) };
					storage[i][j] = validValues[Random::getRandomNumber() % validValues.size()];
				}
			}
		}
	}

	template <typename T>
	const Container2D<T>& Container2D<T>::print(const std::string& file) const {
		FileWriter fileWriter(file);
		for (int i = 0; i != storage.size(); i++) {
			for (int j = 0; j != storage[i].size(); j++) {
				fileWriter.write(std::to_string(storage[i][j]) + " ");
			}
			fileWriter.write(";");
		}
		return *this;
	}
}

