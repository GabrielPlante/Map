#include "pch.h"

#include "../pns-innov/BotManager.h"
#include "../pns-innov/GeneticBot.h"
using pns::BotManager;
using pns::GeneticBot;

TEST(GeneticBotTest, GetValuesUnder) {
	std::vector<int> array1{ 1, 8, 7, 16, 9, 4, 7, 3, 2};
	std::vector<int> expected1{ 0, 5, 7, 8},
		expected2{0, 1, 2, 4, 5, 6, 7, 8},
		res;
	GeneticBot gb = GeneticBot();
	res = gb.getValuesUnder(array1, 5);
	for (int i = 0; i < expected1.size(); i++)
		EXPECT_EQ(expected1.at(i), res.at(i));
	res = gb.getValuesUnder(array1, 9);
	for (int i = 0; i < expected2.size(); i++)
		EXPECT_EQ(expected2.at(i), res.at(i));
	res = gb.getValuesUnder(array1, 0);
	EXPECT_EQ(0, res.size());
}
int getMoney() {
	return 7;
}
TEST(GeneticBotTest, Play) {
	std::vector<int> towersCost{ 3, 4, 5 };

}