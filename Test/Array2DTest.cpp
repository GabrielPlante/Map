#include "pch.h"

#include "../Map/Array2D.h"

TEST(Array2DTest, All) {
	map::Array2D a;
	EXPECT_EQ(0, a.size());
	EXPECT_FALSE(a.positionExist({ 0, 1 }));
	a.addPosition({ 0, 1 });
	EXPECT_TRUE(a.positionExist({ 0, 1 }));
	EXPECT_FALSE(a.positionExist({ 0, 0 }));

	EXPECT_EQ(1, a.size());

	map::Array2D::Iterator it{ a.begin() };
	EXPECT_FALSE(it.end());
	ge::Vector2<int> position{ 0, 1 };
	EXPECT_EQ(position, it.get());
	it++;
	EXPECT_TRUE(it.end());
}