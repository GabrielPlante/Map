#include "pch.h"

#include "../GameEngine2D/VectorOfVector.h"

bool func1() { return false; }
bool func2(bool b) { return b; }

TEST(VectorOfVectorTest, All) {
	ge::VectorOfVector<bool> a{ func1, func2 };
	//EXPECT_EQ(0, a.size());
	EXPECT_FALSE(a.elementExist({ 0, 1 }));
	a.addElement({ 0, 1 }, true);
	EXPECT_TRUE(a.elementExist({ 0, 1 }));
	EXPECT_FALSE(a.elementExist({ 0, 0 }));

	//EXPECT_EQ(1, a.size());

	ge::VectorOfVector<bool>::Iterator it{ a.begin() };
	EXPECT_FALSE(it.endReached());
	ge::Vector2<unsigned> position{ 0, 1 };
	EXPECT_EQ(position, it.getPosition());
	it++;
	EXPECT_TRUE(it.endReached());


}