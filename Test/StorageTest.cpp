#include "pch.h"

//#include "MapTest.h" Commented to avoid error if ianagd is not set to library

#include <string>

#include "../GameEngine2D/Storage.h"

TEST(StorageTest, All) {
	ge::Storage<std::string> storage;
	unsigned int id1 = storage.addComponent("id1");
	EXPECT_EQ(*storage.getComponent(id1), "id1");

	unsigned int id2 = storage.addComponent("id2");
	unsigned int id3 = storage.addComponent("id3");
	EXPECT_EQ(*storage.getComponent(id2), "id2");
	EXPECT_EQ(*storage.getComponent(id3), "id3");

	storage.deleteComponent(id2);
	EXPECT_EQ(*storage.getComponent(id3), "id3");

	auto it = storage.getBeginningIterator();
	EXPECT_EQ(*it, "id1");
	it++;
	EXPECT_EQ(*it, "id3");
}