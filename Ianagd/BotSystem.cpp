#include "BotSystem.h"

#include "../GameEngine2D/CommandList.h"
#include "../GameEngine2D/Console.h"

#include "../pns-innov/BotManager.h"
#include "../pns-innov/BalancerAttribute.h"

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

	//Build the tower of type towerType at the position towerPosition
	void placeTower(int towerType, std::array<int, 2> towerPosition) {
		if (!GameCore::getInstance()->getTowerManager()->buildTower(F_FACTORY->map.relativeToAbsolute({ towerPosition[0], towerPosition[1] }), towerType))
			CONSOLE_LOG_ERROR("Cannot build tower of type: " + std::to_string(towerType) + " at position: " + std::to_string(towerPosition[0]) + ";" + std::to_string(towerPosition[1]))
	}

	void buffDamage(int tower) { gv::towersValues[tower].damage += 4; }
	void nerfDamage(int tower) { tower == 0 ? gv::towersValues[tower].damage -= 1 : gv::towersValues[tower].damage -= 5; }

	void buffRange(int tower) { gv::towersValues[tower].range += 10; }
	void nerfRange(int tower) { gv::towersValues[tower].range -= 10; }

	void buffAttackSpeed(int tower) { gv::towersValues[tower].reloadingTime -= 50; }
	void nerfAttackSpeed(int tower) { gv::towersValues[tower].reloadingTime += 50; }

	void buffCost(int tower) { gv::towersValues[tower].cost -= 20; }
	void nerfCost(int tower) { gv::towersValues[tower].cost += 20; }


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
			std::vector<pns::BalancerAttribute> towerAttributes{
				pns::BalancerAttribute{ buffDamage, nerfDamage, 2 },
				pns::BalancerAttribute{ buffRange, nerfRange, 1 },
				pns::BalancerAttribute{ buffAttackSpeed, nerfAttackSpeed, 1 },
				pns::BalancerAttribute{ buffCost, nerfCost, 1 } };
			F_FACTORY->botManager->setupTowerBalancer(towerAttributes, { {20, 30}, {35, 45}, {35, 45} });

			//Setup a wave balancer
			//F_FACTORY->botManager->setupWaveBalancer(buffWave, nerfWave, static_cast<int>(gv::wavesValues.size()));
		}
		F_FACTORY->botManager->update();
	}

}
