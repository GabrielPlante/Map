#include "pch.h"

#include "../pns-innov/Container2D.h"


TEST(Container2DSerializerTest, All) {
	pns::Container2D<int> container;

	int a[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 11}
	};
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			container.set(i, j, a[i][j]);

	try {
		container.writeToFile(
			"Container2DSerializerTest.txt");
	}
	catch (string e) {
		std::cerr << "error writing file: " << e;
	}

	EXPECT_FALSE(container.exist(0, 0));
	container.set(1, 2, 5, -1);
	EXPECT_EQ(-1, container.get(1, 0));
	EXPECT_EQ(-1, container.get(1, 1));
	EXPECT_EQ(5, container.get(1, 2));
	EXPECT_FALSE(container.exist(0, 0));
}