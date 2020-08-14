#pragma once
#include <map>

#include "../GameEngine2D/Vector2.h"

#include "TileComponent.h"

namespace map {
	//Store every tile component that compose the map
	class MapStorage
	{
		friend class Iterator;
	private:
		//The map storage, static so the map is unique
		static std::vector<std::vector<TileComponent>> map;
	public:
		//Add a tile to the map. Return true if the tile was added, return false if there was already a tile
		bool addTile(ge::Vector2<int> position, TileComponent&& tile);

		//Delete the tile at the position. Return true if the tile was deleted, and false if there was no tile at the position
		bool deleteTile(ge::Vector2<int> position);

		//Change a tile, or add the tile if no tile was there
		//void changeTile(ge::Vector2<int> position, TileComponent&& tile);

		//Check if there is a tile at the position specified, return true if there is one
		bool tileExist(ge::Vector2<int> position) const { return map.size() > position.x && map[position.x].size() > position.y && map[position.x][position.y].height != -1; }

		//Get a tile
		const TileComponent& getTile(ge::Vector2<int> position) const { return map[position.x][position.y]; }

		//Get a pointer on the tile
		TileComponent* modifyTile(ge::Vector2<int> position) { return &map[position.x][position.y]; }

		class Iterator {
		private:
			MapStorage* mapStorage;
			ge::Vector2<int> position{ 0, 0 };
			bool hasEnded{ false };
		public:
			//Constructor
			Iterator(MapStorage* mapStorage, ge::Vector2<int> startPosition = { 0, 0 }) : mapStorage{ mapStorage }, position{ startPosition } {
				if (!mapStorage->tileExist(position)) {
					(*this)++;
				}
			}

			//Increment the iterator to the next tile
			Iterator operator++(int) {
				position.y++;
				//While there are still line to explore in the vector
				while (mapStorage->map.size() > position.x) {
					//While there are still position to explore in the line
					while (mapStorage->map[position.x].size() > position.y) {
						//If the tile exist, we found the next tile
						if (mapStorage->tileExist(position))
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
			bool endReached() {
				return hasEnded;
			}

			TileComponent* operator->() const {
				return mapStorage->modifyTile(position);
			}

			//Get the position of the iterator
			ge::Vector2<int> getPosition() const { return position; }

			//Check if the iterator is the same as a vector2D
			bool operator!=(ge::Vector2<int> other) { return other != position; }
		};

		//The map iterator
		MapStorage::Iterator getBeginningIterator() { return Iterator{ this }; }


	};
}

