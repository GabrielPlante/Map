#include "pch.h"

#include "../pns-innov/TowerBalancer.h"

std::vector<bool> isBuffed{ false, false };
std::vector<bool> isNerfed{ false, false };
void buff(int id) { isBuffed[id] = true; }
void nerf(int id) { isNerfed[id] = true; }

TEST(TestTowerBalancer, TestAll) {
	pns::BalancerAttribute attribute{ buff, nerf };
	pns::BalancerObject object1{ {attribute}, {60, 70}, 0 };
	pns::BalancerObject object2{ {attribute }, { 30, 40 }, 1 };
	pns::TowerBalancer tower{ {object1, object2} };

	EXPECT_EQ(0, tower.getNbrOfBuffPerTower()[0]);
	EXPECT_EQ(0, tower.getNbrOfBuffPerTower()[1]);

	EXPECT_FALSE(isBuffed[0]);
	EXPECT_FALSE(isNerfed[0]);

	tower.balanceTowers({ 1, 1 });

	EXPECT_TRUE(isBuffed[0]);
	isBuffed[0] = false;
	EXPECT_TRUE(isNerfed[1]);
	isNerfed[1] = false;
	EXPECT_FALSE(isNerfed[0]);
	EXPECT_FALSE(isBuffed[1]);

	EXPECT_EQ(1, tower.getNbrOfBuffPerTower()[0]);
	EXPECT_EQ(-1, tower.getNbrOfBuffPerTower()[1]);

	tower.balanceTowers({ 2, 1 });

	EXPECT_FALSE(isBuffed[0]);
	EXPECT_FALSE(isNerfed[0]);
	EXPECT_FALSE(isBuffed[1]);
	EXPECT_FALSE(isNerfed[1]);
	EXPECT_EQ(1, tower.getNbrOfBuffPerTower()[0]);
	EXPECT_EQ(-1, tower.getNbrOfBuffPerTower()[1]);

}