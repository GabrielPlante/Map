#include "pch.h"

#include "../GameEngine2D/TextureWrapper.h"
#include "../GameEngine2D/Drawer.h"
#include "../GameEngine2D/Window.h"

TEST(TextureWrapperTest, All) {
	//Setup the drawer
	ge::Window window{ 200, 200 };
	ge::Drawer::addRenderer(window.getRenderer());

	ge::Drawer drawer{};
	drawer.startDrawing({ 100, 100 }, { 100, 100, 100 });
	ge::TextureWrapper texture{ drawer.finishDrawing() };

	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().size());
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().find(texture.getId())->second);

	ge::TextureWrapper texture2{ texture };
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().size());
	EXPECT_EQ(2, ge::TextureWrapper::getInstanceCounter().find(texture.getId())->second);
	EXPECT_EQ(texture.get(), texture2.get());
	EXPECT_EQ(texture.getId(), texture2.getId());

	{
		ge::TextureWrapper texture3{ texture };
		EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().size());
		EXPECT_EQ(3, ge::TextureWrapper::getInstanceCounter().find(texture.getId())->second);
		EXPECT_EQ(texture.getId(), texture3.getId());
		EXPECT_TRUE(texture.get());
	}
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().size());
	EXPECT_EQ(2, ge::TextureWrapper::getInstanceCounter().find(texture.getId())->second);
	EXPECT_TRUE(texture.get());

	texture2 = nullptr;
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().size());
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().find(texture.getId())->second);
	EXPECT_TRUE(texture.get());

	texture2 = texture;
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().size());
	EXPECT_EQ(2, ge::TextureWrapper::getInstanceCounter().find(texture.getId())->second);
	EXPECT_EQ(texture.get(), texture2.get());
	EXPECT_TRUE(texture.get());

	texture2 = nullptr;
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().size());
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().find(texture.getId())->second);
	EXPECT_TRUE(texture.get());

	texture2 = texture.get();
	EXPECT_EQ(2, ge::TextureWrapper::getInstanceCounter().size());
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().find(texture.getId())->second);
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().find(texture2.getId())->second);
	EXPECT_EQ(texture.get(), texture2.get());
	EXPECT_TRUE(texture.get());

	drawer.startDrawing({ 100, 100 }, { 100, 100, 100 });
	texture2 = drawer.finishDrawing();
	EXPECT_EQ(2, ge::TextureWrapper::getInstanceCounter().size());
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().find(texture.getId())->second);
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().find(texture2.getId())->second);
	EXPECT_TRUE(texture.get());
	EXPECT_TRUE(texture2.get());

	texture2 = nullptr;
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().size());
	EXPECT_EQ(1, ge::TextureWrapper::getInstanceCounter().find(texture.getId())->second);
	EXPECT_TRUE(texture.get());

	texture = nullptr;
	EXPECT_EQ(0, ge::TextureWrapper::getInstanceCounter().size());
}
