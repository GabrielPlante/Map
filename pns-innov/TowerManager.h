#pragma once
#include <vector>
#include <array>
#include <set>

namespace pns {
	class TowerManager
	{
	private:
		//The towers sorted by fitness. The first number is the fitness and the two other the position
		std::vector<std::vector<std::array<int, 3>>> bestTowersPosition;
	public:
		/* Constructor
		 * pathVector is the vector that contain every path on the game
		 * buildableVector contain every tile where you can build on in the game
		 * towersRange contain the range of every tower
		*/
		TowerManager(
			const std::vector<std::array<int, 2>>& pathVector, 
			const std::vector<std::array<int, 2>>& buildableVector,
			const std::vector<int>& towersRange);

		//Get the best position for a type of tower, knowing that already nbrOfTowerPlaced tower of that type are placed
		//towersAlreadyPlaced can be the list of tower already placed, so the algorithm can return a free position
		std::array<int, 2> getBestTowerPosition(int towerType, int nbrOfTowerPlaced, const std::set<std::array<int, 2>>& towersAlreadyPlaced = std::set<std::array<int, 2>>{}) const;
	};
}

