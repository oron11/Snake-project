#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "io_utils.h"
#include "Point.h"

class SnakesGame;

class Creature
{
	char shape;
	Color color;
	Direction direction;
    Point location;

public:
	enum Shapes { EATING_NUMBER = (int)'%', FLYING_ROWS = (int)'!', FLYING_COLS = (int)'$' };

	Creature(char _shape, Color _color, Direction _direction, Point _location) : shape(_shape), color(_color), direction(_direction), location(_location) { drawShape(); }
	virtual void handleCreature(SnakesGame& game) = 0;
	virtual void getNextDir() = 0;
	virtual BOOL isCreatureAlive()const = 0;

	Color getColor()const { return color; }
	Direction getDirection()const { return  direction; }
	Point getLocation()const { return location; }
	const char getShape()const { return shape; }

	void setDirection(Direction _direction) { direction = _direction; }
	void move(){location.move(direction);}

	void initiateCreature(const Point& _location,const Direction& _direction);
    virtual void removeCreatureFromScreen();
	void drawShape();
	virtual BOOL checkIfPosIsACreature(const Point& pos)const;
	virtual void handleNextCreaturePosition(SnakesGame & game, BOOL exceptionalEvent);
};


#endif 
