#include "BotSystem.h"

#include "../GameEngine2D/CommandList.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameCore.h"

namespace ian {
	//Every function the bot manager need
	bool hasWaveEnded() { return F_FACTORY->gameComponent.startNewWave == interWave; }
	void startNextWave() { EXEC("start_new_wave") }
	bool hasGameEnded() { return F_FACTORY->gameComponent.startNewWave == playerLost || F_FACTORY->gameComponent.startNewWave == playerWin; }
	void startNewGame() { EXEC("restart_game") }

	int getMoney() { return F_FACTORY->gameComponent.playerGold; }

	//This function find the best place to build a tower
	void placeTower(int towerType) {
		//The fitness of the best tower, ie: how many path tile the best tower see
		int bestTowerFitness{ 0 };
		ge::Vector2<int> bestTowerPosition;
		//For every tile
		for (int i = 6; F_FACTORY->map.tileExist({ i, 0 }); i++) {
			for (int j = 6; F_FACTORY->map.tileExist({ i, j }); j++) {
				//If we can build on this tile
				if (GameCore::getInstance()->getTowerManager()->isBuildable(F_FACTORY->map.relativeToAbsolute({ i, j }))) {
					ge::Vector2<> tilePos{ F_FACTORY->map.relativeToAbsolute({i, j}) };

					//This tile fitness
					int towerFitness{ 0 };
					//For every tile in the square of size 2 x tower range centered on the tile
					for (long k = -gv::towersValues[towerType].range + tilePos.x; k < gv::towersValues[towerType].range + tilePos.x; k += gv::tileSize) {
						for (long l = -gv::towersValues[towerType].range + tilePos.y; l < gv::towersValues[towerType].range + tilePos.y; l += gv::tileSize) {
							//If the tile [k, l] is still in the circle (this could be improved with the mid-point circle algorithm for performance)
							//And this tile is part of the path the enemies take
							if (tilePos.rectIntersectCircle(ge::Vector2<>{ k, l }, 1, 1, gv::towersValues[towerType].range)
								&& F_FACTORY->map.tileExist(F_FACTORY->map.absoluteToRelative({ k, l }))
								&& F_FACTORY->map.getTile(F_FACTORY->map.absoluteToRelative({ k, l })).isWalkable) {
								towerFitness++;
							}
						}
					}
					//If this tile is the best for this tower type
					if (towerFitness > bestTowerFitness) {
						bestTowerFitness = towerFitness;
						bestTowerPosition = { i, j };
					}
				}
			}
		}
		//If we found a place to build the tower
		if (bestTowerFitness != 0) {
			GameCore::getInstance()->getTowerManager()->buildTower(F_FACTORY->map.relativeToAbsolute(bestTowerPosition), towerType);
		}
	}

	BotSystem::BotSystem() {
	}

	void BotSystem::update() {
		if (F_FACTORY->botManager == nullptr) {
			std::vector<int> towersCost;
			for (int i = 0; i != gv::towersValues.size(); i++) {
				towersCost.push_back(gv::towersValues[i].cost);
			}
			F_FACTORY->botManager = std::unique_ptr<pns::BotManager>{ new pns::BotManager{std::function<bool()>{hasWaveEnded}, std::function<void()>{startNextWave},
				std::function<bool()>{hasGameEnded}, std::function<void()>{startNewGame}, std::function<int()>{getMoney}, std::function<void(int)>{placeTower}, towersCost, 50 } };
		}
		F_FACTORY->botManager->update();
	}

}
