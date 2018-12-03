#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "SnakesGame.h"

class MenuManager
{
	SnakesGame game;

public:
	void printMainMenu();
	void startGame();
	void printInstructions();
	void executeMenuChoice();
	void finishGame();
	void evaluateChoice();
};


#endif