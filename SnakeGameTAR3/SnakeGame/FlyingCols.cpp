#include "FlyingCols.h"
#include "SnakesGame.h"

void FlyingCols::handleCreature(SnakesGame& game)
{
	if (isAlive)
	{
		Creature::removeCreatureFromScreen();
		getNextDir();
		move();
		handleNextCreaturePosition(game,FALSE);
		if(isAlive)
		   drawShape();
	}
}

void FlyingCols::initiateFlyingCols(const Point& _location,const Direction& _direction)
{
	isAlive = TRUE;
	initiateCreature(_location, _direction);
}

void FlyingCols::getNextDir()
{
	if (getColor() == Color::LIGHTGREY)
		setDirection(DOWN);
	else
	{
		if (getLocation().getY() == Point::min_y)
			setDirection(DOWN);
		else if (getLocation().getY() == Point::max_y)
			setDirection(UP);
		else
			setDirection(getDirection());
	}
}

void FlyingCols::handleNextCreaturePosition(SnakesGame & game, BOOL exceptionalEvent)
{
	if (game.checkIfPosIsBullet(getLocation(), TRUE))
	{
		isAlive = FALSE;
		int placeOfFlyingCol = (getColor() == LIGHTGREY) ? 1 : 2;
		game.enterDeadCounterCreature(placeOfFlyingCol);
	}
	Creature::handleNextCreaturePosition(game, exceptionalEvent);
}

void FlyingCols::removeCreatureFromScreen()
{
	Creature::removeCreatureFromScreen();
	isAlive = FALSE;
}

BOOL FlyingCols::checkIfPosIsACreature(const Point& pos)const
{
	if (isAlive)
		return Creature::checkIfPosIsACreature(pos);
	return FALSE;
}
