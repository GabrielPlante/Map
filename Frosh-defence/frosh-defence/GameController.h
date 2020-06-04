/*
 * GameController.h
 *
 *  Created on: Nov 6, 2018
 *      Author: Connor
 */
#pragma once
#include "GameState.h"
#include "Frec.h"
#include "FrecController.h"

#include "../../pns-innov/BotManager.h"

 // Game Controller keeps all Game State Variables Running and Updated
class GameController {
private:

public:

	GameController();

	void process();
	void update();
	void render();
};

// Game Board generates the map, and handles interactions
// for any entities sitting on the map
class GameBoard {
private:
	//For the bot implementation
	static GameBoard* instance;

	GameState* gameState;
	FrecController* frecController;
	int width;

	// Helper functions
	bool gridSpaceAvailable(int gridX, int gridY);
	bool frecIsPurchasable(FrecType type);

public:
	GameBoard(GameState* gameState, FrecController* frecController,
		int widthInPixels);

	//Function for the bot
	static GameBoard* getInstance() { return instance; }
	int getMoney() { return gameState->getTams(); }
	GameState* getGameState() { return gameState; }

	void placeFrec(FrecType type, int gridX, int gridY);

	bool validatePos(int mouseX, int mouseY, int range);
	void process(sf::Event event, sf::Vector2i mousePos);
	void update();
	void render();		// Render board
	void renderLabels();
	void renderRange(int mouseX, int mouseY, int range);
	void renderShadow(int mouseX, int mouseY, int range);
	int gridStatus[32][18] = { 0 };
};

