#ifndef _FLYING_COLS_H_
#define _FLYING_COLS_H_

#include "io_utils.h"
#include "Creature.h"

class SnakesGame;

class FlyingCols : public Creature
{
	bool isAlive;
public:
	
	FlyingCols(char _shape,Color _color, Direction _direction, Point _location) : Creature(_shape, _color, _direction, _location), isAlive(TRUE) {}
	virtual void handleCreature(SnakesGame& game)override;
	const BOOL isFlyingColAlive()const { return isAlive; }
	virtual BOOL isCreatureAlive()const override { return isAlive; }
	void initiateFlyingCols(const Point& _location,const Direction& _direction);
	void getNextDir();
	virtual void handleNextCreaturePosition(SnakesGame & game, BOOL exceptionalEvent)override;
	virtual void removeCreatureFromScreen()override;
	virtual BOOL checkIfPosIsACreature(const Point& pos)const override;
};



#endif 
