#include "BotSystem.h"

#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/Console.h"

#include "../pns-innov/BotManager.h"

#include "FactoryFactory.h"
#include "GameValues.h"
#include "GameCore.h"

namespace ian {

	/*
	void generateBestTowerPositionVector() {
		constexpr ge::Vector2<int> mapSize{ 25, 25 };
		//For every tower
		for (int towerType = 0; towerType != gv::towersValues.size(); towerType++) {
			bestTowerPositionVector.push_back(std::vector<std::array<int, 3>>{});
			int towerRange{ gv::towersValues[towerType].range / gv::tileSize };
			//For every tile
			for (int i = towerRange; i < mapSize.x - towerRange; i++) {
				for (int j = towerRange; j < mapSize.y - towerRange; j++) {
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
						std::array<int, 3> towerArray{ towerFitness, i, j };
						//If it is the first tower to be added
						if (bestTowerPositionVector[towerType].empty()) {
							bestTowerPositionVector[towerType].push_back(towerArray);
						}
						else {
							for (int towerI = 0; towerI != bestTowerPositionVector[towerType].size(); towerI++) {
								//If we reached the correct place for this tower
								if (bestTowerPositionVector[towerType][towerI][0] < towerFitness) {
									bestTowerPositionVector[towerType].insert(bestTowerPositionVector[towerType].begin() + towerI, towerArray);
									break;
								}
								//Else if we reached the end of the list (ie this tower placement is the worst one yet)
								else if (towerI == bestTowerPositionVector[towerType].size() - 1) {
									bestTowerPositionVector[towerType].push_back(towerArray);
									break;
								}
							}
						}
					}
				}
			}
		}
	}*/

	//Every function the bot manager need
	bool hasWaveEnded() { return F_FACTORY->gameComponent.startNewWave == interWave; }
	void startNextWave() { EXEC("start_new_wave") }
	bool hasGameEnded() { return F_FACTORY->gameComponent.startNewWave == playerLost || F_FACTORY->gameComponent.startNewWave == playerWin; }
	void startNewGame() { EXEC("restart_game") }

	int getMoney() { return F_FACTORY->gameComponent.playerGold; }

	//Build the tower of type towerType at the position towerPosition
	void placeTower(int towerType, std::array<int, 2> towerPosition) {
		if (!GameCore::getInstance()->getTowerManager()->buildTower(F_FACTORY->map.relativeToAbsolute({ towerPosition[0], towerPosition[1] }), towerType))
			CONSOLE_LOG_ERROR("Cannot build tower of type: " + std::to_string(towerType) + " at position: " + std::to_string(towerPosition[0]) + ";" + std::to_string(towerPosition[1]))
	}

	void buffDamage(int tower) { gv::towersValues[tower].damage += 4; }
	void nerfDamage(int tower) { tower == 0 ? gv::towersValues[tower].damage -= 1 : gv::towersValues[tower].damage -= 5; }

	void buffWave(int waveNbr) { gv::wavesValues[waveNbr].enemyHealth += 10; }
	void nerfWave(int waveNbr) { gv::wavesValues[waveNbr].enemyHealth -= 20; }

	BotSystem::BotSystem() {
	}

	void BotSystem::update() {
		//If there isn't a bot yet create one
		if (F_FACTORY->botManager == nullptr) {

			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			//Create the tower manager
			std::vector<std::array<int, 2>> pathTiles;
			std::vector<std::array<int, 2>> buildableTiles;

			constexpr ge::Vector2<int> mapSize{ 25, 25 };
			//For every tile
			for (int i = 0; i < mapSize.x; i++) {
				for (int j = 0; j < mapSize.y; j++) {
					//If the tile exist
					if (F_FACTORY->map.tileExist({ i, j })) {
						//Add to the respective vector
						if (F_FACTORY->map.getTile({ i, j }).isWalkable)
							pathTiles.push_back({ i, j });
						else if (F_FACTORY->map.getTile({ i, j }).isBuildable)
							buildableTiles.push_back({ i, j });
					}
				}
			}

			//Make the towers cost and range vector
			std::vector<int> towersCost;
			std::vector<int> towersRange;
			for (int i = 0; i != gv::towersValues.size(); i++) {
				towersCost.push_back(gv::towersValues[i].cost);
				towersRange.push_back(gv::towersValues[i].range / gv::tileSize);
			}

			//Initialise the tower manager
			pns::TowerManager towerManager{ pathTiles, buildableTiles, towersRange };
			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------

			//Create the bot
			F_FACTORY->botManager = std::unique_ptr<pns::BotManager>{ new pns::BotManager{std::function<bool()>{hasWaveEnded}, std::function<void()>{startNextWave}, std::function<bool()>{hasGameEnded},
				std::function<void()>{startNewGame}, std::function<int()>{getMoney}, std::function<void(int, std::array<int, 2>)>{placeTower}, towersCost, towerManager, 50 ,
			50, 5, 15, 3} };

			//Setup a tower balancer
			//F_FACTORY->botManager->setupTowerBalancer(buffDamage, nerfDamage, { {20, 30}, {35, 45}, {35, 45} });

			//Setup a wave balancer
			F_FACTORY->botManager->setupWaveBalancer(buffWave, nerfWave, static_cast<int>(gv::wavesValues.size()));
		}
		F_FACTORY->botManager->update();
	}

}
