#ifndef _REPLAY_H_
#define _REPLAY_H_

#include "Bullet.h"
#include "Screen.h"
#include "Snake.h"
#include "FlyingCols.h"
#include "FlyingRows.h"
#include "EatingNumber.h"
#include "StructsForReplay.h"

class SnakesGame;
class Creature;

class Replay
{
	enum { SIZE = 2 };

	//Snake snakes[SIZE];
	Creature* creatures[5];
	EatingNumber eatingNumber = { Creature::EATING_NUMBER,BROWN,UP,{ 10,19 } };
	FlyingRows flyingRows[SIZE] = { { Creature::FLYING_ROWS,LIGHTMAGENTA,RIGHT,{ 30,23 } },{ Creature::FLYING_ROWS,MAGENTA,LEFT,{ 50,15 } } };
	FlyingCols flyingCols[SIZE] = { { Creature::FLYING_COLS,LIGHTGREY,DOWN,{ 55,15 } },{ Creature::FLYING_COLS,DARKGREY,UP,{ 45,23 } } };
	BOOL showLastMissionPreview;
	size_t countSteps,countReplay;
	char screen[MAX_ROWS][MAX_COLS];
	
	vector<Number> arr;
	//KeysPressed keyPressed[SIZE];
	SnakeReplay snakes[SIZE];
	KeyAmmu keyAmmu[SIZE];
	KeysPressed keyEatingNumber;
	list<DeleteNumber> deleteNumbersArr;
	BulletsReplay bulletsReplay[SIZE];
	BulletsOfSnake bulletsOfSnakes[SIZE];

	int counterDeadCreatures[3];
	SnakesGame* game;

public:
	Replay() { makeArrayCreatures(); setColorOfSnakesAndShape(); }
	void setPreviewOfMission(BOOL _status) { showLastMissionPreview = _status; }
	void addStepToMission() { countSteps++; }
	//void addkeyToSnakesArr(const Direction& dir, char c);
	void addkeyToEatingNumberArr(const Direction& dir) { keyEatingNumber.key.push_back({dir,countSteps}); }
	void addkeyToDeleteNumberArr(const Point& pos, size_t numOfDigits) { deleteNumbersArr.push_back({ pos,countSteps,numOfDigits }); }
	void addkeyToKillCreature(int place) { counterDeadCreatures[place] = countSteps; }
	void addkeyToBullet(int snakeNum,size_t id) { bulletsReplay[snakeNum].bullets.push_back({countSteps,0,id}); }
	void addKeyToDeleteBullet(int snakeNum, size_t id);
	//void enterLocationOfSnakeAfterRevive(int snakeNum, SnakesGame * _game, Direction dir);
	void enterNumToArr(int num, const Point& location) { arr.push_back({ num,location,countSteps }); }
	void addKeyToAmmu(size_t ammu, int snakeNum) { keyAmmu[snakeNum].key.push_back({ammu,countSteps});}
	void addKeyToVanishSnake(int snakeNum) {snakes[snakeNum].vanish.push_back({ countSteps,-1 });}

	void addLocation(int i, vector<Point> newBody,BOOL reviveLocation) { snakes[i].locations.push_back({ newBody,countSteps,reviveLocation }); }

	void run();
	void moveAllOneStep();
	void updateAmmu();
	void enterNumber();
	void deleteNumbers();
	void moveSnakes();
	void vanishSnakes();
	void vanishSnake(int i);
	void setColorOfSnakesAndShape();
	void reviveSnakes();
	void moveBullets();
	void moveCreatures();
	void printCreatures();
	void drawCreature(int i);
	void initiateReplay();
	void initiateArrays();
	void handlePreviewIfNeeded(SnakesGame* _game);
	void printCurrentScreen();

	void enterNumbersToReplayScreen();
	void showLastMission();
	void printStatus(const string& str);
	void printSnakes();
	void printSnake(int i);
	void printStats(int i);
	void makeArrayCreatures();
};



#endif