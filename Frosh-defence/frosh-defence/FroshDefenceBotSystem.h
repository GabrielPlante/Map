#pragma once
#include <memory>

#include "../../pns-innov/BotManager.h"
#include "GameState.h"

class FroshDefenceBotSystem
{
private:
	GameState* gsInstance = nullptr;
public:
	//Constructor
	FroshDefenceBotSystem() {}
	FroshDefenceBotSystem(GameState& gsInstance);
	//Update the system
	void update();

	static FroshDefenceBotSystem& getInstance()
	{
		static FroshDefenceBotSystem INSTANCE = FroshDefenceBotSystem();
		return INSTANCE;
	}
	static GameState *getGameState() { return getInstance().gsInstance; }
	static void setGameStateInstance(GameState& gs) {
		getInstance().gsInstance = &gs;
	}

};