#include "pch.h"

#include "../Ianagd/Map.h"

TEST(MapTest, absoluteToRelative) {
	ian::Map map;
	EXPECT_EQ(1, map.absoluteToRelative({ 55, 0 }).x);
	EXPECT_EQ(0, map.absoluteToRelative({ 15, 0 }).x);
	EXPECT_EQ(-1, map.absoluteToRelative({ -15, 0 }).x);
	EXPECT_EQ(-1, map.absoluteToRelative({ -50, 0 }).x);
	EXPECT_EQ(-2, map.absoluteToRelative({ -55, 0 }).x);
	EXPECT_EQ(0, map.absoluteToRelative({ 0, 0 }).x);

	EXPECT_EQ(1, map.absoluteToRelative({ 0, 55 }).y);
	EXPECT_EQ(0, map.absoluteToRelative({ 0, 15 }).y);
	EXPECT_EQ(-1, map.absoluteToRelative({ 0, -15 }).y);
	EXPECT_EQ(-2, map.absoluteToRelative({ 0, -55 }).y);
	EXPECT_EQ(0, map.absoluteToRelative({ 0, 0 }).y);
}

TEST(MapTest, relativeToAbsolute) {
	ian::Map map;
	EXPECT_EQ(50, map.relativeToAbsolute({ 1, 0 }).x);
	EXPECT_EQ(0, map.relativeToAbsolute({ 0, 0 }).x);
	EXPECT_EQ(-50, map.relativeToAbsolute({ -1, 0 }).x);
	EXPECT_EQ(-100, map.relativeToAbsolute({ -2, 0 }).x);
	EXPECT_EQ(100, map.relativeToAbsolute({ 2, 0 }).x);

	EXPECT_EQ(50, map.relativeToAbsolute({ 0, 1 }).y);
	EXPECT_EQ(0, map.relativeToAbsolute({ 0, 0 }).y);
	EXPECT_EQ(-50, map.relativeToAbsolute({ 0, -1 }).y);
	EXPECT_EQ(-100, map.relativeToAbsolute({ 0, -2 }).y);
	EXPECT_EQ(100, map.relativeToAbsolute({ 0, 2 }).y);
}

//Commented because the method is usually private
/*TEST(MapTest, coordinateToTile) {
	ian::Map map;
	EXPECT_EQ(0, map.coordinateToTile({ 0, 0 })[0]);
	EXPECT_EQ(1, map.coordinateToTile({ 0, -1 })[0]);
	EXPECT_EQ(2, map.coordinateToTile({ -1, 0 })[0]);
	EXPECT_EQ(3, map.coordinateToTile({ -1, -1 })[0]);

	EXPECT_EQ(0, map.coordinateToTile({ 0, 0 })[1]);
	EXPECT_EQ(1, map.coordinateToTile({ 1, 0 })[1]);
	EXPECT_EQ(1, map.coordinateToTile({ 0, 1 })[2]);

	EXPECT_EQ(0, map.coordinateToTile({ -1, 0 })[1]);
	EXPECT_EQ(1, map.coordinateToTile({ -2, 0 })[1]);
	EXPECT_EQ(1, map.coordinateToTile({ 0, -2 })[2]);
	EXPECT_EQ(2, map.coordinateToTile({ 0, 2 })[2]);
}*/

TEST(MapTest, tileExist) {
	ian::Map map;

	map.addTile({ 0, 0 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ 0, 0 }));

	map.addTile({ 1, 0 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ 1, 0 }));

	map.addTile({ -1, 0 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ -1, 0 }));
	map.addTile({ -2, 0 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ -2, 0 }));

	map.addTile({ 0, -1 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ 0, -1 }));

	map.addTile({ -1, -1 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ -1, -1 }));

	EXPECT_TRUE(!map.tileExist({ 1, 1 }));

}
