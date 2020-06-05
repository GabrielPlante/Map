#include "pch.h"

#include "../pns-innov/TowerManager.h"

TEST(TowerManagerTest, Test) {
	//Make the buildable tile vector
	std::vector<std::array<int, 2>> buildableTile{
		std::array<int, 2>{1, 0}, std::array<int, 2>{3, 0}, std::array<int, 2>{4, 0}
	};

	//Make the path tile vector
	std::vector<std::array<int, 2>> pathTile{
		std::array<int, 2>{0, 0}, std::array<int, 2>{2, 0}
	};

	std::vector<int> towersRange{ 1, 2 };

	//Make the tower manager
	pns::TowerManager towerManager{ pathTile, buildableTile, towersRange };

	//The best tower of type 0 is the one at position 1, 0
	EXPECT_EQ(1, towerManager.getBestTowerPosition(0, 0)[0]);
	EXPECT_EQ(0, towerManager.getBestTowerPosition(0, 0)[1]);

	//The second best tower of type 0 is the one at position 3, 0
	EXPECT_EQ(3, towerManager.getBestTowerPosition(0, 1)[0]);
	EXPECT_EQ(0, towerManager.getBestTowerPosition(0, 1)[1]);

	//The third best tower of type 0 is the one at position 4, 0
	EXPECT_EQ(4, towerManager.getBestTowerPosition(0, 2)[0]);
	EXPECT_EQ(0, towerManager.getBestTowerPosition(0, 2)[1]);

	//The third best tower of type 1 is the one at position 4, 0
	EXPECT_EQ(4, towerManager.getBestTowerPosition(1, 2)[0]);
	EXPECT_EQ(0, towerManager.getBestTowerPosition(1, 2)[1]);

	//The best tower of type 0 with the tile 1, 0 already occupied is the one at position 3, 0
	std::set<std::array<int, 2>> tilePlaced{ std::array<int, 2>{1, 0} };
	EXPECT_EQ(3, towerManager.getBestTowerPosition(0, 0, tilePlaced)[0]);
	EXPECT_EQ(0, towerManager.getBestTowerPosition(0, 0, tilePlaced)[1]);
}