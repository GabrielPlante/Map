#include "pch.h"
#include <sstream>
#include <iostream>

#include "../pns-innov/BotManager.h"
#include "../pns-innov/GeneticBot.h"
using pns::BotManager;
using pns::GeneticBot;

bool un() { return true; }
pns::GameState ended() { return pns::GameState::Running; }
void deux() {}
int trois() { return 1; }
void quatre(int, std::array<int, 2>) {}

void print_vector(std::vector<int> vect) {
	for (int i = 0; i < vect.size(); i++)
		std::cout << vect.at(i) << std::endl;
}

TEST(BotManagerTest, Container) {
	int i;
	std::vector<int> line1{ 3,4,6,7,9 },
		line2{ 4,5,1 },
		line3{ 8,8,100,19,12,16 },
		line4{ 1 },
		line5{ 1, 4, 5 };
	BotManager botMng = BotManager{un, deux, ended, deux, trois, quatre, std::vector<int>(), pns::TowerManager{ std::vector<std::array<int, 2>>{}, std::vector<std::array<int, 2>>{}, std::vector<int>{} }};
	botMng.loadBots("Input_Files/input_botmanager.txt");
	std::vector<GeneticBot> botList = botMng.getBots();
	EXPECT_EQ(5, botList.at(0).getDecisionMap().size());
	for (i = 0; i < 5; i++) {
		EXPECT_EQ(line1.at(i), botList.at(0).getDecisionMap().at(i));
	}
	
	EXPECT_EQ(3, botList.at(1).getDecisionMap().size());
	
	print_vector(botList.at(1).getDecisionMap());
	for (i = 0; i < 3; i++) {
		EXPECT_EQ(line2.at(i), botList.at(1).getDecisionMap().at(i));
	}
	
	EXPECT_EQ(6, botList.at(2).getDecisionMap().size());
	for (i = 0; i < 6; i++) {
		EXPECT_EQ(line3.at(i), botList.at(2).getDecisionMap().at(i));
	}

	EXPECT_EQ(1, botList.at(3).getDecisionMap().size());
	for (i = 0; i < 1; i++) {
		EXPECT_EQ(line4.at(i), botList.at(3).getDecisionMap().at(i));
	}

	
	EXPECT_EQ(3, botList.at(4).getDecisionMap().size());
	for (i = 0; i < 3; i++) {
		EXPECT_EQ(line5.at(i), botList.at(4).getDecisionMap().at(i));
	}
}