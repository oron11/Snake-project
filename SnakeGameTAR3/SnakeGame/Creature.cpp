#include "Creature.h"
#include "SnakesGame.h"

void Creature::initiateCreature(const Point& _location,const Direction& _direction)
{
	Creature::removeCreatureFromScreen();
	location = _location;
	direction = _direction;
	drawShape();
}

void Creature::removeCreatureFromScreen()
{
	location.draw(' ');
}

void Creature::drawShape()
{
	setTextColor(color);
	location.draw(shape);
	setTextColor(WHITE);
}

BOOL Creature::checkIfPosIsACreature(const Point& pos)const
{
	return pos== location;
}

void Creature::handleNextCreaturePosition(SnakesGame& game,BOOL exceptionalEvent)
{
	game.getNumber(location, TRUE);

	for (int i = 0; i<game.SIZE; i++)
		if (game.snakes[i].checkIfNextStepIsTheSnakeItself(location, 0))
		{
			game.vanishSnake(game.snakes[i]);
			game.snakes[i].setLifeOfTheSnake(FALSE);
			if (exceptionalEvent) //The event that occurs when the snake is in the creature spot
				game.reviveSnake(game.snakes[i]);
		}
}
