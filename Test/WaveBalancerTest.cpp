#include "pch.h"

#include "../pns-innov/WaveBalancer.h"

std::vector<bool> isBuffedWave{ false, false };
std::vector<bool> isNerfedWave{ false, false };
void buffWave(int id) { isBuffedWave[id] = true; }
void nerfWave(int id) { isNerfedWave[id] = true; }

TEST(TestWaveBalancer, TestAll) {
	constexpr int nbrOfWave{ 2 };
	pns::WaveBalancer waveBalancer{ buffWave, nerfWave, nbrOfWave };
	
	EXPECT_FALSE(waveBalancer.didFinishBalance());
	EXPECT_EQ(0, waveBalancer.getCurrentBalancingWave());

	waveBalancer.balanceWave(false);
	EXPECT_FALSE(isBuffedWave[0]);
	EXPECT_TRUE(isNerfedWave[0]);
	isNerfedWave[0] = false;

	waveBalancer.balanceWave(true);
	EXPECT_TRUE(isBuffedWave[0]);
	EXPECT_FALSE(isNerfedWave[0]);
	isBuffedWave[0] = false;

	waveBalancer.balanceWave(false);
	EXPECT_FALSE(isBuffedWave[0]);
	EXPECT_TRUE(isNerfedWave[0]);

	EXPECT_EQ(1, waveBalancer.getCurrentBalancingWave());

	waveBalancer.balanceWave(true);
	EXPECT_TRUE(isBuffedWave[1]);
	EXPECT_FALSE(isNerfedWave[1]);
	isBuffedWave[1] = false;

	waveBalancer.balanceWave(true);
	EXPECT_TRUE(isBuffedWave[1]);
	EXPECT_FALSE(isNerfedWave[1]);
	isBuffedWave[1] = false;

	waveBalancer.balanceWave(false);
	EXPECT_FALSE(isBuffedWave[1]);
	EXPECT_TRUE(isNerfedWave[1]);

	EXPECT_TRUE(waveBalancer.didFinishBalance());

	EXPECT_EQ(1, waveBalancer.getNbrOfBuffPerWave()[1]);
}
