#ifndef _SNAKES_GAME_H_
#define _SNAKES_GAME_H_

//#include "io_utils.h"
#include "Snake.h"
#include "Missions.h"
#include "EatingNumber.h"
#include "FlyingRows.h"
#include "FlyingCols.h"
#include "Replay.h"

class SnakesGame {
	enum { SIZE = 2,ESC = 27, INITIAL_SIZE = 3, WIN_GAME = 12,SIZE_CREATURES = 5};

	Snake snakes[SIZE] = {
		{ { 10, 9 }, '@',Direction::RIGHT,INITIAL_SIZE, LIGHTRED,YELLOW }, // snake 1
		{ { 70, 9 }, '#',Direction::LEFT,INITIAL_SIZE, LIGHTBLUE,LIGHTCYAN }, // snake 2
	};
	Mission missions;
	EatingNumber eatingNumber = { Creature::EATING_NUMBER,BROWN,UP,{10,19} };
	FlyingRows flyingRows[SIZE] = { {Creature::FLYING_ROWS,LIGHTMAGENTA,RIGHT,{30,23}},{Creature::FLYING_ROWS,MAGENTA,LEFT,{ 50,15 } } };
	FlyingCols flyingCols[SIZE] = { {Creature::FLYING_COLS,LIGHTGREY,DOWN,{ 55,15 } },{ Creature::FLYING_COLS,DARKGREY,UP,{ 45,23 } } };
	Bullet bullets;
	Creature* creatures[SIZE_CREATURES];
	size_t countForEnterNum;
	size_t countNumbersOnScreen;
	char screen[MAX_ROWS][MAX_COLS];
	Replay replay;
	BOOL endMission;
	int choice;

	int getNumber(const Point& pos, BOOL eraseNumber);
	void makeArrayCreatures();
	int getDigit(int x, int y) {
		char c = screen[y][x];
		if (c == ' ') {
			return -1;
		}
		return c - '0';
	}
	
	friend class Bullet;
	friend class Creature;
	friend class EatingNumber;
	friend class Replay;

public:
	SnakesGame();
	void run();
	void handleSnake(char keyPressed,size_t snakeNum);
	void handleUtilities(int time);
	void initiateGame();

	SnakesGame(const SnakesGame& s) = delete;
	int getChoice() const{ return choice; }
	void setChoice(int _choice) { choice = _choice; }
	BOOL checkIfPosIsASnake(int x, int y)const;
	BOOL checkIfPosNearOtherNumber(int x, int y)const;
	int getSubMenuChoice(BOOL clearScreen);
	BOOL checkIfPosNearHeadOfSnakes(int x, int y)const;
	BOOL checkIfPosIsLegal(int x, int y);
	BOOL enterNumberToScreen(int num, int x, int y);
	void enterNumberEach5steps();
	Point getRandomLocation();
	void cleanHalfOfScreen();
	BOOL checkIfSnakeGotNumber(int snakeNum, int num);
	BOOL checkForAvailableSolution(int functionChoice);
	void flickeringNumber(int y, int x, int num, int digitsCounter);
	void printStats(int i);
	void initiateScreen();
	void printFrame();
	void printSubMenu();
	void executeSubMenuChoice();
	void printLastScreenNumbers();
	void printSnakes();
	void checkIfMissionEnded();
	void initiateUtilities();
	void checkForAnExceptionalEvent();
	BOOL checkIfGameEnded();
	void checkIfSnakesIsTrapped();
	void placeSnakesInStartPosition();
	void handleIfThereAre60NumbersOnScreen();
	void handleSnakesHitted();

	void reviveSnake(Snake& snake);
	BOOL checkIfPosIsOneOfCreature(const Point& location)const;
	BOOL checkIfPosIsFlyingRow(const Point& location)const;
	BOOL checkIfPosIsEatingNumber(const Point& location)const;
	BOOL checkIfPosIsFlyingCol(const Point& location)const;
	BOOL checkIfPosIsBullet(const Point& location, BOOL eraseBullet);
	BOOL checkIfPosLegalFromLeft(const Point& location, int otherSnake, const Snake& snake);
	BOOL checkIfPosLegalFromRight(const Point& location, int otherSnake,const Snake& snake);
	BOOL checkIfPosLegalFromTop(const Point& location, int otherSnake, const Snake& snake);
	BOOL checkIfPosLegalFromBottom(const Point& location, int otherSnake,const Snake& snake);
	BOOL checkIfPosIsOtherObjects(const Point& nextStep);
	void placeSnakeFromLeft(Point location, Snake& snake);
	void placeSnakeFromRight(Point location, Snake& snake);
	void placeSnakeFromTop(Point location, Snake& snake);
	void placeSnakeFromBottom(Point location, Snake& snake);

	void addkeyToReplayArr(int i, vector<Point> location) { replay.addLocation(i, location,FALSE); }
	void enterDeadCounterCreature(int place) { replay.addkeyToKillCreature(place); }
	void AddKeyToVanishSnake(int i) { replay.addKeyToVanishSnake(i); }

	int randomizeNumber();
	void vanishSnake(Snake & snake);
	~SnakesGame() { }
};

#endif


