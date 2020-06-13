#pragma once
#include <vector>

#include "../GameEngine2D/Color.h"

class gv {//gv as game values
public:
	//Player related values
	static constexpr long speedDividingFactor{ 1000 };

	//Map related values
	static constexpr int tileSize{ 50 };
	static constexpr int maxPathSize{ 1000 };//Value used to limit the A star search for a path

	//-----GAME RELATED VALUES-----

	//Value common to all wave
	//static constexpr long long timeBetweenWaves{ 2 * 1000 * 1000 };//In micro second
	static constexpr long long timeBetweenSpawn{ 1000 * 1000 };//In micro second

	struct WaveValues {
		int nbrOfEnemy;
		int enemyHealth;
		float enemySpeed;
		int goldPerEnemy;
		const ge::Color color;
		WaveValues(int nbrOfEnemy, int enemyHealth, float enemySpeed, int goldPerEnemy, ge::Color color)
			: nbrOfEnemy{ nbrOfEnemy }, enemyHealth{ enemyHealth }, enemySpeed{ enemySpeed }, goldPerEnemy{ goldPerEnemy }, color{ color } {}
	};

	//Wave values
	static std::vector<WaveValues> wavesValues;
	static constexpr int nbrOfEnemyForLoss{ 0 };

	//Other game values
	static constexpr int startingGold{ 150 };

	struct TowerValues {
		int cost;
		int damage;
		int range;
		int reloadingTime;
		ge::Color color;
		TowerValues(int cost, int damage, int range, int reloadingTime, ge::Color color)
			: cost{ cost }, damage{ damage }, range{ range }, reloadingTime{ reloadingTime }, color{ color } {}
	};

	static std::vector<TowerValues> towersValues;
};
