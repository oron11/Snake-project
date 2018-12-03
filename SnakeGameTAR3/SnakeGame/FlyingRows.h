#ifndef _FLYING_ROWS_H_
#define _FLYING_ROWS_H_

#include "io_utils.h"
#include "Creature.h"

class SnakesGame;

class FlyingRows : public Creature
{

public:
	FlyingRows(char _shape, Color _color, Direction _direction, Point _location):  Creature(_shape, _color, _direction, _location) {}
	virtual void handleCreature(SnakesGame& game)override;
	void initiateFlyingRows(const Point& _location, const Direction& _direction);
	void getNextDir();
	virtual void handleNextCreaturePosition(SnakesGame & game, BOOL exceptionalEvent)override;
	virtual BOOL isCreatureAlive()const override {return TRUE;}
};



#endif 
