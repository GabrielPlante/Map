#pragma once

#include "../GameEngine2D/VectorOfVector.h"

#include "FloraComponent.h"

namespace map {
	class FloraStorage
	{
	private:
		static ge::VectorOfVector<FloraComponent> floraStorage;
	public:
		//Add a flora to the floraStorage. Return true if the flora was added, return false if there was already a flora
		void addFlora(ge::Vector2<int> position, FloraComponent&& flora) { floraStorage.addElement(position, std::move(flora)); }

		//Delete the flora at the position. Return true if the flora was deleted, and false if there was no flora at the position
		void deleteTile(ge::Vector2<int> position) { floraStorage.deleteElement(position); }

		//Check if there is a flora at the position specified, return true if there is one
		bool floraExist(ge::Vector2<int> position) const { return floraStorage.elementExist(position); }

		//Get a flora
		const FloraComponent& getTile(ge::Vector2<int> position) const { return floraStorage[position]; }

		//Get a pointer on the flora
		FloraComponent* modifyTile(ge::Vector2<int> position) { return &floraStorage[position]; }

		//The floraStorage iterator
		ge::VectorOfVector<FloraComponent>::Iterator getBeginningIterator() { return floraStorage.begin(); }
	};
}

