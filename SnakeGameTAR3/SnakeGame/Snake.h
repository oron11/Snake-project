#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "Point.h"
#include "Direction.h"
#include "Bullet.h"

class Replay;
class EatingNumber;

class Snake
{
	Direction direction;
	char c;
	Color headColor;
	Color bodyColor;
	size_t score;
	char dirKeys[4];
	size_t snakeSize;
	BOOL snakeAlive;
	size_t countForReviveSnake;
	size_t ammunition;
	vector<Bullet> bullets;
	vector<Point> body;
	friend class Bullet; 
public:
	enum { MAX_BULLETS = 5 };
	Snake(){}
	Snake(const Point& head, char c1, Direction dir, size_t _snakeSize, Color _colorHead, Color _colorBody);
	//Snake& operator=(const Snake& _snake);
	void initiateSnake(const Point & head, Direction dir, size_t _snakeSize);

	int getScore()const { return score; }
	char getChar() const { return c; }
	Direction getDirection()const { return direction; }
	void setDirection(Direction _direction) { direction = _direction; }
	Color getSnakeHeadColor()const { return headColor; }
	Color getSnakeBodyColor()const { return bodyColor; }
	size_t getCountToReviveSnake()const {return countForReviveSnake;}
	void setCountToReviveSnake(size_t count) { countForReviveSnake = count; }
	BOOL isSnakeAlive()const { return snakeAlive; }
	void setLifeOfTheSnake(BOOL status) { snakeAlive = status; }
	size_t getAmmunition()const { return ammunition; }
	void increaseAmmunition(int snakeNum, Replay& replay);
	void decreaseAmmunition(int snakeNum, Replay& replay);
	void initiateAmmunition() { ammunition = MAX_BULLETS; }
	const size_t getSize()const { return snakeSize; }
	const Point getBodyPoint(int i)const { return body[i]; }
	const Point getBulletPoint(int i)const { return bullets[i].getLocation(); }
	const size_t sizeBullets()const { return bullets.size(); }
	const vector<Point> getBody()const { return body; };

	Point move(SnakesGame& game, char keyPressed, const Snake& otherSnake);
	//void moveSnakeReplay(const EatingNumber & eatingNumber, const Snake & otherSnake);
	void moveBody(const Point & nextStep);
	void setKeys(char keyLeft, char keyRight, char keyUp, char keyDown);
	BOOL changeDir(char keyPressed);
	void increaseSnake();
	BOOL checkIfSnakeIsTrapped();
	void printSnake();
	BOOL checkIfPosNearHeadOfSnake(int x, int y)const;
	void placeSnakeInStartPosition();
	void printSnakeHead();
	void vanishSnake(SnakesGame& game);
	void disappearSnake();
	void setBodyPoint(int i, int x, int y);
	BOOL checkIfNextStepIsLegal(const Point& nextStep,const Snake& otherSnake,SnakesGame& game)const;
	BOOL checkIfnextStepIsOtherSnake(const Point& nextStep,const Snake& otherSnake)const;
	BOOL checkIfNextStepIsTheSnakeItself(const Point& nextStep, int locationToStart)const;
	void createNewBody(const Point& head);
};


#endif
