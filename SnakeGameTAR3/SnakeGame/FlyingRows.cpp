#include "FlyingRows.h"
#include "SnakesGame.h"

void FlyingRows::handleCreature(SnakesGame& game)
{
	removeCreatureFromScreen();
	getNextDir();
	move();
	handleNextCreaturePosition(game,FALSE);
	drawShape();
}

void FlyingRows::initiateFlyingRows(const Point& _location,const Direction& _direction)
{
	initiateCreature(_location, _direction);
}

void FlyingRows::getNextDir()
{
	if (getColor() == Color::LIGHTMAGENTA)
		setDirection(RIGHT);
	else
	{
		if (getLocation().getX() == Point::max_x)
			setDirection(LEFT);
		else if(getLocation().getX() == Point::min_x)
			setDirection(RIGHT);
		else
			setDirection(getDirection());
	}
}

void FlyingRows::handleNextCreaturePosition(SnakesGame & game, BOOL exceptionalEvent)
{
	Creature::handleNextCreaturePosition(game,exceptionalEvent);
	game.checkIfPosIsBullet(getLocation(), TRUE);
}

