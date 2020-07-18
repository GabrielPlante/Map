#pragma once
#include <vector>

#include "../GameEngine2D/Vector2.h"

namespace map {
	//An array2D is used to store coordinate of a vector2D<int> in a efficient way
	class Array2D
	{
		friend class Iterator;
	private:
		std::vector<std::vector<bool>> container;

		size_t sizeC{ 0 };
	public:
		class Iterator {
		private:
			Array2D* array2D;
			ge::Vector2<int> position{ 0, 0 };
			bool hasEnded{ false };
		public:
			//Constructor
			Iterator(Array2D* array2D, ge::Vector2<int> startPosition = { 0, 0 }) : array2D{ array2D }, position{ startPosition } {
				if (!array2D->positionExist(position)) {
					(*this)++;
				}
			}

			//Return false if the iterator is at the end
			Iterator operator++(int) {
				position.y++;
				//While there are still line to explore in the vector
				while (array2D->container.size() > position.x) {
					//While there are still position to explore in the line
					while (array2D->container[position.x].size() > position.y) {
						if (array2D->container[position.x][position.y])
							return *this;
						position.y++;
					}
					position.x++;
					position.y = 0;
				}
				hasEnded = true;
				return *this;
			}

			//Return true if the iterator is at the end
			bool end() {
				return hasEnded;
			}

			//Get the position of the pointer
			ge::Vector2<int> get() {
				return position;
			}

			//Check if the iterator is the same as a vector2D
			bool operator!=(ge::Vector2<int> other) { return other != position; }
			bool operator!=(Iterator other) { return other.get() != position; }
		};

		//Add a position to the array
		void addPosition(ge::Vector2<int> position) {
			while (container.size() <= position.x)
				container.push_back(std::vector<bool>{});
			while (container[position.x].size() <= position.y)
				container[position.x].push_back(false);
			container[position.x][position.y] = true;
			//Update the size
			sizeC++;
		}

		//Delete a position on the array
		void deletePosition(ge::Vector2<int> position) {
			if (container.size() > position.x && container[position.x].size() > position.y && container[position.x][position.y]) {
				container[position.x][position.y] = false;
				//Update the size
				sizeC--;
			}
		}

		//Check if a position exist
		bool positionExist(ge::Vector2<int> position) {
			return container.size() > position.x && container[position.x].size() > position.y && container[position.x][position.y];
		}

		//Get the size of the vector
		size_t size() {
			return sizeC;
		}

		//Get the begin iterator
		Array2D::Iterator begin() {
			return Iterator{ this };
		}
	};
}
