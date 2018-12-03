#include "MenuManager.h"
#include "SnakesGame.h"

void MenuManager::printMainMenu()
{
	clrscr();
	gotoxy(0, 7);
	cout << "--------------------TheSnakesGame By Or&Oron--------------------" << endl;
	cout << "---------------------------MainMenu-----------------------------" << endl;
	cout << "Please enter your choice by entering a number between 1 to 3" << endl << endl;
	cout << "(1) Show the instructions" << endl;
	cout << "(2) Start game" << endl;
	cout << "(3) Exit" << endl;
}

void MenuManager::startGame()
{
	ShowConsoleCursor(false);
	do {
		printMainMenu();
		game.setChoice(_getch());
		executeMenuChoice();
	} while (game.getChoice() != '3');
	finishGame();
}

void MenuManager::printInstructions()
{
	clrscr();
	gotoxy(0, 4);
	cout << "--------------------TheSnakesGame By Or&Oron--------------------" << endl;
	cout << "---------------------------Instructions-----------------------------" << endl;
	cout << "This is a game for 2 players." << endl << endl;
	cout << "Each player controls a different snake (@,#)." << endl;
	cout << "The aim of the game is to collect as fast as possible and as much as possible " << endl;
	cout << "right numbers from the screen according to the missions that appear." << endl;
	cout << "The numbers appear randomly at the screen." << endl;
	cout << "Each player has 5 bullets in start of every mission." << endl;
	cout << "The player can use the bullets to destroy numbers,the other player and himself!" << endl;
	cout << "Each right eating of a number equals 1 point for the player who's collected it." << endl;
	cout << "If a player collected wrong number the point goes to the other player." << endl;
	cout << "The first player that reached 12 points wins the game" << endl;
	cout << "GOOD LUCK !" << endl;
	cout << "Press any key to continue" << endl;
	while (!_kbhit()) {}
	_getch();
}

void MenuManager::executeMenuChoice()
{
	switch (game.getChoice())
	{
	case '1':
	{
		printInstructions();
		break;
	}
	case '2':
	{
		clrscr();
		game.run();
		evaluateChoice();
		break;
	}
	}
}

void MenuManager::finishGame()
{
	setTextColor(LIGHTMAGENTA);
	clrscr();
	printf("Good Bye!\n");
	Sleep(800);
}

void MenuManager::evaluateChoice()
{
	if (game.getChoice() == '1')
		game.setChoice('3');
	else if (game.getChoice() == '2')
	{
		game.initiateGame();
		game.setChoice('0');
	}
}


