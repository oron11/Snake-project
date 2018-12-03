#ifndef _BULLET_H_
#define _BULLET_H_

#include "Point.h"
#include "Direction.h"
#include "Color.h"
#include <vector>

class SnakesGame;

class Bullet
{
	Direction direction;
	Point location;
	Color color;
	size_t id;
	friend class SnakesGame;
	static size_t counter;
public:
	Bullet(){}
	Bullet(Direction _direction,Point _location, Color _color,size_t _id) :
		  direction(_direction), color(_color), location(_location),id(_id) {}
	const Point getLocation()const { return location; }
	void shootBullets(SnakesGame& game,char keyPressed);
	void shootSnakeBullet(SnakesGame& game, int snakeNumber);
	bool snakeHitHimself(SnakesGame & game, int snakeNumber);
	void handleBullets(SnakesGame& game, int indexStart, int indexEnd);
	int getNewIndex(int j, bool meetBulletFromTheSameSnake, SnakesGame & game, int snakeNum,const Bullet& bullet)const;
	bool checkAndHandleNextPositionIsFreeToPass(SnakesGame& game,int snakeNumber,const Point& nextPosition, bool& meetBulletFromTheSameSnake);
	void removeBulletFromScreen();
	void moveBullet(Color color);
	void initiateBullets(SnakesGame & game);
	BOOL checkIfPosIsBullet(Point location, SnakesGame & game, BOOL eraseBullet);
	bool bulletsMeetEachOther(SnakesGame& game, const Point& nextPosition, int snakeNumber, bool& meetBulletFromTheSameSnake);
};

#endif 
