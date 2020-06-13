#include "TowerManager.h"
#include <cmath>


namespace pns {
	using std::pow;

	TowerManager::TowerManager(const std::vector<std::array<int, 2>>& pathVector, const std::vector<std::array<int, 2>>& buildableVector, const std::vector<int>& towersRange) {
		//Build the bestTowersPosition vector
		//For every tower
		for (int i = 0; i != towersRange.size(); i++) {
			bestTowersPosition.push_back(std::vector<std::array<int, 3>>{});
			//For every buildable tile
			for (int j = 0; j != buildableVector.size(); j++) {
				//The fitness of the tile
				int fitness{ 0 };
				//For every path
				for (int k = 0; k != pathVector.size(); k++) {
					int x{ pathVector[k][0] };
					int y{ pathVector[k][1] };

					int circleX{ buildableVector[j][0] };
					int circleY{ buildableVector[j][1] };

					//If the path is in range of this tile, with the range of the tower
					if (pow(x - circleX, 2) + pow(y - circleY, 2) <= pow(towersRange[i], 2)) {
						fitness++;
					}
				}

				//Here we insert this position into the vector at the correct position, so the vector is sorted
				//The array that will go into the bestTowersPosition vector
				std::array<int, 3> towerArray{ fitness, buildableVector[j][0], buildableVector[j][1] };
				//If it is the first tower to be added
				if (bestTowersPosition[i].empty()) {
					bestTowersPosition[i].push_back(towerArray);
				}
				else {
					for (int towerI = 0; towerI != bestTowersPosition[i].size(); towerI++) {
						//If we reached the correct place for this tower
						if (bestTowersPosition[i][towerI][0] < fitness) {
							bestTowersPosition[i].insert(bestTowersPosition[i].begin() + towerI, towerArray);
							break;
						}
						//Else if we reached the end of the list (ie this tower placement is the worst one yet)
						else if (towerI == bestTowersPosition[i].size() - 1) {
							bestTowersPosition[i].push_back(towerArray);
							break;
						}
					}
				}
			}
		}
	}

	std::array<int, 2> TowerManager::getBestTowerPosition(int towerType, int nbrOfTowerPlaced, const std::set<std::array<int, 2>>& towersAlreadyPlaced) const {
		std::array<int, 2> towerPosition{ bestTowersPosition[towerType][nbrOfTowerPlaced][1], bestTowersPosition[towerType][nbrOfTowerPlaced][2] };
		//While the position of this tower is already occupied
		while (towersAlreadyPlaced.find(towerPosition) != towersAlreadyPlaced.end()) {
			//Get the next position
			nbrOfTowerPlaced++;
			//Boundaries check
			if (nbrOfTowerPlaced == bestTowersPosition[towerType].size())
				break;
			//Get the new tower
			towerPosition = std::array<int, 2>{bestTowersPosition[towerType][nbrOfTowerPlaced][1], bestTowersPosition[towerType][nbrOfTowerPlaced][2]};
		}
		return towerPosition;
	}
}
