#include "pch.h"

#include "../pns-innov/Container2D.h"

TEST(Container2DTest, All) {
	pns::Container2D<int> container;
	EXPECT_FALSE(container.exist(0, 0));
	container.insert(1, 2, 5, -1);
	EXPECT_EQ(-1, container.get(1, 0));
	EXPECT_EQ(-1, container.get(1, 1));
	EXPECT_EQ(5, container.get(1, 2));
	EXPECT_FALSE(container.exist(0, 0));
}
