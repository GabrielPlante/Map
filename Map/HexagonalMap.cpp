#include "HexagonalMap.h"

#include "MapStorage.h"
#include "MapValues.h"

/* The map use doubled coordinate internaly, but the user of this class should not be aware of this
 * Changing to the axial system of coordinate because it is easier to work with hexagonal grid with the axial system
 * All the work to convert coordinates is done here
 * More information here : https://www.redblobgames.com/grids/hexagons/
*/
namespace map {
	const double tileWidth{ sqrt(3.0) * mv::tileSize };//Sqrt isn't constexpr
	constexpr double tileHeight{ mv::tileSize * 2.0 };

	//Relative position to an absolute one
	ge::Vector2<> HexagonalMap::relativeToAbsolute(ge::Vector2<int> relative) {
		return { static_cast<long>((relative.x + relative.y / 2.0) * tileWidth), static_cast<long>(relative.y * tileHeight * 3 / 4) };
	}

	//Absolute position to a relative one
	/*ge::Vector2<int> HexagonalMap::absoluteToRelative(ge::Vector2<> absolute) const {
		return { static_cast<int>(absolute.x * 2.0 / tileWidth), static_cast<int>(absolute.y * 4 / 3 / tileHeight) };
	}*/

	std::vector<TileComponent*> HexagonalMap::getNeighbors(ge::Vector2<int> position) const {
		MapStorage storage;
		std::vector<TileComponent*> neighbors;
		if (storage.tileExist({ position.x + 1, position.y }))
			neighbors.push_back(storage.modifyTile({ position.x + 1, position.y }));
		if (storage.tileExist({ position.x + 1, position.y - 1 }))
			neighbors.push_back(storage.modifyTile({ position.x + 1, position.y - 1 }));
		if (storage.tileExist({ position.x, position.y - 1 }))
			neighbors.push_back(storage.modifyTile({ position.x, position.y - 1 }));
		if (storage.tileExist({ position.x - 1, position.y }))
			neighbors.push_back(storage.modifyTile({ position.x - 1, position.y }));
		if (storage.tileExist({ position.x - 1, position.y + 1 }))
			neighbors.push_back(storage.modifyTile({ position.x - 1, position.y + 1 }));
		if (storage.tileExist({ position.x, position.y + 1 }))
			neighbors.push_back(storage.modifyTile({ position.x, position.y + 1 }));

		return neighbors;
	}

	std::vector<std::pair<ge::Vector2<int>, TileComponent*>> HexagonalMap::getNeighborsWithPos(ge::Vector2<int> position) const {
		MapStorage storage;
		std::vector<std::pair<ge::Vector2<int>, TileComponent*>> neighbors;
		if (storage.tileExist({ position.x + 1, position.y }))
			neighbors.push_back(std::make_pair(ge::Vector2<int>{ position.x + 1, position.y }, storage.modifyTile({ position.x + 1, position.y })));
		if (storage.tileExist({ position.x + 1, position.y - 1 }))
			neighbors.push_back(std::make_pair(ge::Vector2<int>{ position.x + 1, position.y - 1 }, storage.modifyTile({ position.x + 1, position.y - 1 })));
		if (storage.tileExist({ position.x, position.y - 1 }))
			neighbors.push_back(std::make_pair(ge::Vector2<int>{ position.x, position.y - 1 }, storage.modifyTile({ position.x, position.y - 1 })));
		if (storage.tileExist({ position.x - 1, position.y }))
			neighbors.push_back(std::make_pair(ge::Vector2<int>{ position.x - 1, position.y }, storage.modifyTile({ position.x - 1, position.y })));
		if (storage.tileExist({ position.x - 1, position.y + 1 }))
			neighbors.push_back(std::make_pair(ge::Vector2<int>{ position.x - 1, position.y + 1 }, storage.modifyTile({ position.x - 1, position.y + 1 })));
		if (storage.tileExist({ position.x, position.y + 1 }))
			neighbors.push_back(std::make_pair(ge::Vector2<int>{ position.x, position.y + 1 }, storage.modifyTile({ position.x, position.y + 1 })));

		return neighbors;

	}
}
