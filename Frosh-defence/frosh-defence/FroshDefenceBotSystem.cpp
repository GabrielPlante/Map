#include "FroshDefenceBotSystem.h"

FroshDefenceBotSystem::FroshDefenceBotSystem(GameState& gsInstance) {
	this->gsInstance = &gsInstance;
}

void FroshDefenceBotSystem::update() {}

//Every function the bot manager need
bool hasWaveEnded() { return false; }
void startNextWave() { ; }
bool hasGameEnded() { return false; }
void startNewGame() { ; }

int getMoney() { return FroshDefenceBotSystem::getGameState()->getTams(); }

/*
//This function find the best place to build a tower
void placeTower(int towerType, int nbrOfTowerAlreadyPlaced) {
	//While there is still tower that can be build, and while we fail to build a tower
	while (bestTowerPositionVector[towerType].size() > nbrOfTowerAlreadyPlaced && !GameCore::getInstance()->getTowerManager()
		->buildTower(F_FACTORY->map.relativeToAbsolute({ bestTowerPositionVector[towerType][nbrOfTowerAlreadyPlaced][1], bestTowerPositionVector[towerType][nbrOfTowerAlreadyPlaced][2] }), towerType)) {
		nbrOfTowerAlreadyPlaced++;
	}
}

void buffDamage(int tower) { gv::towersValues[tower].damage += 4; }
void nerfDamage(int tower) { tower == 0 ? gv::towersValues[tower].damage -= 1 : gv::towersValues[tower].damage -= 5; }

void buffWave(int waveNbr) { gv::wavesValues[waveNbr].enemyHealth += 10; }
void nerfWave(int waveNbr) { gv::wavesValues[waveNbr].enemyHealth -= 20; } */