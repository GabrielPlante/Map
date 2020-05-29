#include "pch.h"
#include <sstream>

#include "../pns-innov/Container2D.h"

TEST(Container2DTest, Container) {
	pns::Container2D<int> container;
	EXPECT_FALSE(container.exist(0, 0));
	container.set(1, 2, 5, -1);
	EXPECT_EQ(-1, container.get(1, 0));
	EXPECT_EQ(-1, container.get(1, 1));
	EXPECT_EQ(5, container.get(1, 2));
	EXPECT_FALSE(container.exist(0, 0));
}

TEST(Conateiner2DTest, print) {
	pns::Container2D<int> container;
	container.set(0, 3, 4);
	container.set(1, 1, 3);
	container.print("testContainer.csv");
	std::ifstream infile{ "testContainer.csv" };
	std::string line;
	std::getline(infile, line);
	EXPECT_EQ("0 0 0 4 ;0 3 ;", line);
}
