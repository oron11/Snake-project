#include "Bullet.h"
#include "SnakesGame.h"

size_t Bullet::counter;

void Bullet::shootBullets(SnakesGame& game, char keyPressed)
{
	if (keyPressed == 'z')
		shootSnakeBullet(game, 0);
	else if (keyPressed == 'n')
		shootSnakeBullet(game, 1);
}

void Bullet::shootSnakeBullet(SnakesGame& game, int snakeNumber)
{
	Snake &snake = game.snakes[snakeNumber];
	if (game.snakes[snakeNumber].isSnakeAlive() && !snakeHitHimself(game, snakeNumber) && game.snakes[snakeNumber].getAmmunition() >0)
	{
		snake.bullets.push_back({ snake.getDirection(),snake.body[0],snake.getSnakeHeadColor(),counter});
		snake.decreaseAmmunition(snakeNumber,game.replay);
		game.replay.addkeyToBullet(snakeNumber,counter++);
		game.replay.addStepToMission(); //check this
		if (snakeNumber == 0)
			handleBullets(game, 0, 1);
		else
			handleBullets(game, 1, 2);
	}
}

bool Bullet::snakeHitHimself(SnakesGame& game, int snakeNumber)
{
	Snake& snake = game.snakes[snakeNumber];
	bool res = FALSE;
	int xBody, yBody;
	if (snake.getDirection() == LEFT)
	{
		if (snake.body[0].getX() == Point::min_x)
			xBody = Point::max_x;
		else
			xBody = snake.body[0].getX() - 1;
		if (snake.body[1].getX() == xBody && snake.body[1].getY() == snake.body[0].getY())
			res = TRUE;
	}
	else if (snake.getDirection() == RIGHT)
	{
		if (snake.body[0].getX() == Point::max_x)
			xBody = Point::min_x;
		else
			xBody = snake.body[0].getX() + 1;
		if (snake.body[1].getX() == xBody && snake.body[1].getY() == snake.body[0].getY())
			res = TRUE;
	}
	else if (snake.getDirection() == UP)
	{
		if (snake.body[0].getY() == Point::min_y)
			yBody = Point::max_y;
		else
			yBody = snake.body[0].getY() - 1;
		if (snake.body[1].getY() == yBody && snake.body[1].getX() == snake.body[0].getX())
			res = TRUE;
	}
	else if (snake.getDirection() == DOWN)
	{
		if (snake.body[0].getY() == Point::max_y)
			yBody = Point::min_y;
		else
			yBody = snake.body[0].getY() + 1;
		if (snake.body[1].getY() == yBody && snake.body[1].getX() == snake.body[0].getX())
			res = TRUE;
	}
	return res;
}

void Bullet::handleBullets(SnakesGame & game,int indexStart,int indexEnd)
{
	Point nextPosition;
	for (int i = indexStart; i < indexEnd; i++)
	{
		bool meetBulletFromTheSameSnake = FALSE;
		setTextColor(game.snakes[i].getSnakeHeadColor());
		for (size_t j = 0; j < game.snakes[i].bullets.size(); j++)
		{
			game.snakes[i].bullets[j].removeBulletFromScreen();
			nextPosition = game.snakes[i].bullets[j].location;
			nextPosition.move(game.snakes[i].bullets[j].direction);
			Bullet bullet = game.snakes[i].bullets[j]; //copy of the bullet for new index if needed

			if (checkAndHandleNextPositionIsFreeToPass(game, i, nextPosition, meetBulletFromTheSameSnake))
			{
				game.snakes[i].bullets[j].location = nextPosition;
				game.snakes[i].bullets[j].location.draw();
			}
			else
			{
				int findNewIndex = getNewIndex(j, meetBulletFromTheSameSnake, game, i, bullet);
				game.snakes[i].bullets.erase(game.snakes[i].bullets.begin() + findNewIndex);
				j = findNewIndex - 1;
				game.replay.addKeyToDeleteBullet(i, bullet.id);
			}
		}
	}
	setTextColor(WHITE);
}

int Bullet::getNewIndex(int j, bool meetBulletFromTheSameSnake, SnakesGame& game, int snakeNum, const Bullet& bullet)const
{
	int newIndex = j;
	if (meetBulletFromTheSameSnake)
	{
		for (size_t k = 0; k < game.snakes[snakeNum].bullets.size(); k++)
			if (game.snakes[snakeNum].bullets[k].location== bullet.location)
				newIndex = k;
	}
	return newIndex;
}

bool Bullet::checkAndHandleNextPositionIsFreeToPass(SnakesGame& game, int snakeNumber, const Point& nextPosition, bool& meetBulletFromTheSameSnake)
{
	int other = (snakeNumber == 0) ? 1 : 0;
	Snake &otherSnake = game.snakes[other];

	if (game.snakes[snakeNumber].checkIfNextStepIsTheSnakeItself(nextPosition, 0))
	{
		game.vanishSnake(game.snakes[snakeNumber]);
		game.snakes[snakeNumber].setLifeOfTheSnake(FALSE);
		return FALSE;
	}
	else if (game.snakes[snakeNumber].checkIfnextStepIsOtherSnake(nextPosition, otherSnake))
	{
		game.snakes[snakeNumber].increaseAmmunition(snakeNumber, game.replay);
		game.vanishSnake(otherSnake);
		otherSnake.setLifeOfTheSnake(FALSE);
		return FALSE;
	}
	else if (game.checkIfPosIsFlyingRow(nextPosition))
		return FALSE;
	else 
	{
		for (int i = 0; i < game.SIZE_CREATURES;)
		{
			if (game.creatures[i]->checkIfPosIsACreature(nextPosition))
			{
				game.snakes[snakeNumber].increaseAmmunition(snakeNumber, game.replay);
				game.creatures[i]->removeCreatureFromScreen();
				int j = (i == 0) ? 0 : i - 2; //key for deadCreature 0 for eating number 1,2 for flyingcols
				game.enterDeadCounterCreature(j);
				return FALSE;
			}
			i = (i == 0) ? 3 : i + 1;
		}
	}

	if (game.getNumber(nextPosition, TRUE) != -1 || bulletsMeetEachOther(game, nextPosition, snakeNumber, meetBulletFromTheSameSnake))
		return FALSE;

	return TRUE;

}

bool Bullet::bulletsMeetEachOther(SnakesGame& game, const Point& nextPosition, int snakeNumber, bool& meetBulletFromTheSameSnake)
{
	for (int i = 0; i<game.SIZE; i++)
		for (size_t j = 0; j < game.snakes[i].bullets.size(); j++)
			if (game.snakes[i].bullets[j].location==nextPosition)
			{
				game.snakes[i].bullets[j].removeBulletFromScreen();
				game.replay.addKeyToDeleteBullet(i, game.snakes[i].bullets[j].id);
				game.snakes[i].bullets.erase(game.snakes[i].bullets.begin() + j);
				if (i == snakeNumber)
					meetBulletFromTheSameSnake = TRUE;
				else
				{
					game.snakes[0].increaseAmmunition(0, game.replay);
					game.snakes[1].increaseAmmunition(1, game.replay);
				}
				return TRUE;
			}
	return FALSE;
}

void Bullet::removeBulletFromScreen()
{
	location.draw(' ');
}

void Bullet::moveBullet(Color color)
{
	removeBulletFromScreen();
	location.move(direction);
	setTextColor(color);
	location.draw();
	setTextColor(WHITE);
}

void Bullet::initiateBullets(SnakesGame & game)
{
	for (int i = 0; i < game.SIZE; i++)
	{
		for (size_t j = 0; j < game.snakes[i].bullets.size(); j++)
			game.snakes[i].bullets[j].removeBulletFromScreen();

		game.snakes[i].setLifeOfTheSnake(TRUE);
		game.snakes[i].setCountToReviveSnake(0);
		game.snakes[i].bullets.resize(0);
		game.snakes[i].initiateAmmunition();
	}
}

BOOL Bullet::checkIfPosIsBullet(Point location, SnakesGame& game,BOOL eraseBullet)
{
	for (int i = 0; i<game.SIZE; i++)
		for (size_t j = 0; j < game.snakes[i].bullets.size(); j++)
			if (game.snakes[i].bullets[j].location==location)
			{
				if (eraseBullet)
				{
					if (game.checkIfPosIsFlyingCol(location))
						game.snakes[i].increaseAmmunition(i, game.replay);
					game.snakes[i].bullets[j].removeBulletFromScreen();
					game.replay.addKeyToDeleteBullet(i, game.snakes[i].bullets[j].id);
					game.snakes[i].bullets.erase(game.snakes[i].bullets.begin() + j);
				}
				return TRUE;
			}
	return FALSE;
}




