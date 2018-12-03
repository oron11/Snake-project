#include "SnakesGame.h"
#include "Snake.h"
#include "Replay.h"

Snake::Snake(const Point& head, char c1, Direction dir, size_t _snakeSize,Color _headColor,Color _bodyColor)
{
	headColor = _headColor;
	bodyColor= _bodyColor;
	c = c1;
	initiateSnake(head, dir, _snakeSize);
}

/*Snake & Snake::operator=(const Snake & _snake)
{
	headColor = _snake.headColor;
	bodyColor = _snake.bodyColor;
	c = _snake.c;
	for (int j = 0; j < 4; j++)
		dirKeys[j] = _snake.dirKeys[j];

	snakeSize = _snake.snakeSize;
	countForReviveSnake = 0;
	direction = _snake.direction;
	snakeAlive = TRUE;
	score = _snake.score;
	bullets.resize(0);
	ammunition = MAX_BULLETS;
	body = new Point[sizeof(Point)*_snake.getSize()];
	for (size_t j = 0; j < snakeSize; j++)
		body[j] = _snake.body[j];
	return *this;
}*/

void Snake::initiateSnake(const Point& head, Direction dir, size_t _snakeSize)
{
	body.resize(_snakeSize);
	snakeSize = _snakeSize;
	countForReviveSnake = 0;
	direction = dir;
	createNewBody(head);
	snakeAlive = TRUE;
	score = 0;
	ammunition =MAX_BULLETS;
}

void Snake::createNewBody(const Point& head)
{
	body[0] = head;
	body[0].draw(c);
	int addition = (c == '@') ? -1 : 1;
	for (size_t i = 1; i < snakeSize; ++i)
	{
		body[i].setPoint(body[0].getX() + addition*i, body[0].getY());
		body[i].draw(c);
	}
}

void Snake::setKeys(char keyLeft, char keyRight, char keyUp, char keyDown)
{
	dirKeys[Direction::LEFT] = keyLeft;
	dirKeys[Direction::RIGHT] = keyRight;
	dirKeys[Direction::UP] = keyUp;
	dirKeys[Direction::DOWN] = keyDown;
}
BOOL Snake::changeDir(char keyPressed)
{
	for (const auto& key : dirKeys) {
		if (key == keyPressed) {
			direction = (Direction)(&key - dirKeys);
			return TRUE;
		}
	}
	return FALSE;
}
void Snake::increaseAmmunition(int snakeNum, Replay & replay)
{
	 ammunition++;
	 replay.addKeyToAmmu(ammunition, snakeNum);
}

void Snake::decreaseAmmunition(int snakeNum, Replay & replay)
{
	ammunition--;
	replay.addKeyToAmmu(ammunition, snakeNum);
}

Point Snake::move(SnakesGame& game,char keyPressed,const Snake& otherSnake)
{
	Point nextStep = body[0];
	BOOL dirHasChanged = FALSE;
	if (changeDir(keyPressed))
		dirHasChanged = TRUE;
	nextStep.move(direction);
	if (snakeAlive)
	{
		if (game.checkIfPosIsFlyingCol(nextStep) || game.checkIfPosIsFlyingRow(nextStep) || game.checkIfPosIsBullet(nextStep,TRUE))
		{
			game.vanishSnake(*this);
			snakeAlive = FALSE;
		}
		else if (checkIfNextStepIsLegal(nextStep, otherSnake, game))
		{
			int snakeNum = (c == '@') ? 0 : 1;
			moveBody(nextStep);
			game.addkeyToReplayArr(snakeNum, body);
			printSnake();
		}
	}
	return body[0];
}

/*void Snake::moveSnakeReplay(const EatingNumber & eatingNumber,const Snake& otherSnake)
{
	Point nextStep = body[0];
	nextStep.move(direction);
	if (snakeAlive && !checkIfNextStepIsTheSnakeItself(nextStep, 1) && !eatingNumber.checkIfPosIsACreature(nextStep) && !checkIfnextStepIsOtherSnake(nextStep, otherSnake))
	{
		moveBody(nextStep);
		printSnake();
	}
}*/

void Snake::moveBody(const Point& nextStep)
{
	body[snakeSize - 1].draw(' ');
	for (int i = snakeSize - 1; i > 0; --i)
		body[i] = body[i - 1];

	body[0] = nextStep;
}

BOOL Snake::checkIfNextStepIsLegal(const Point& nextStep,const Snake& otherSnake,SnakesGame& game)const
{
	return(!checkIfnextStepIsOtherSnake(nextStep, otherSnake) && !checkIfNextStepIsTheSnakeItself(nextStep,1) && !game.checkIfPosIsEatingNumber(nextStep));
}

BOOL Snake::checkIfnextStepIsOtherSnake(const Point& nextStep,const Snake& otherSnake)const
{
	if (otherSnake.snakeAlive)
	{
		for (size_t i = 0; i < otherSnake.snakeSize; i++)
			if (otherSnake.body[i]== nextStep)
				return TRUE;
	}
	return FALSE;
}

BOOL Snake::checkIfNextStepIsTheSnakeItself(const Point& nextStep,int locationToStart)const
{
	if (snakeAlive)
	{
		for (size_t i = locationToStart; i < snakeSize; i++)
			if (body[i]==nextStep)
				return TRUE;
	}
	return FALSE;
}

void Snake::increaseSnake()
{
	score++;
	body.push_back(body.back());
	snakeSize++;
}

BOOL Snake::checkIfSnakeIsTrapped()
{
	int x, y;
	BOOL fromBottom = FALSE, fromLeft = FALSE, fromTop = FALSE, fromRight = FALSE;
	x = body[0].getX();
	y = body[0].getY();
	for (size_t j = 1; j < snakeSize; j++)
	{
		if (body[j].getX() == x + 1 && body[j].getY() == y)
			fromBottom = TRUE;
	    else if (body[j].getX() == x - 1 && body[j].getY() == y)
			fromTop = TRUE;
		else if (body[j].getX() == x  && body[j].getY() == y + 1)
			fromRight = TRUE;
		else if (body[j].getX() == x  && body[j].getY() == y - 1)
			fromLeft = TRUE;
	}
	return (fromBottom && fromRight && fromLeft && fromTop);
}

void Snake::printSnake()
{
	if (snakeAlive)
	{
		setTextColor(headColor);

		for (size_t i = 0; i < snakeSize; i++)
		{
			body[i].draw(c);
			setTextColor(bodyColor);
		}
		setTextColor(WHITE);
	}
}

BOOL Snake::checkIfPosNearHeadOfSnake(int x, int y)const
{
	if (snakeAlive)
	{
		if (body[0].getY() == x - 1 && body[0].getX() == y)
			return TRUE;
		if (body[0].getY() == x + 1 && body[0].getX() == y)
			return TRUE;
		if (body[0].getY() == x     && body[0].getX() == y + 1)
			return TRUE;
		if (body[0].getY() == x     && body[0].getX() == y - 1)
			return TRUE;
	}
	return FALSE;
}

void Snake::placeSnakeInStartPosition()
{
	snakeAlive = TRUE;
	int overflow = 1;

	if (c == '@')
	{
		setDirection(RIGHT);
		for (size_t i = 0; i < snakeSize; i++)
		{
			if (i <= 9)
				body[i].setPoint(10 - i, 9);
			else
			{
				body[i].setPoint(1, 9 - overflow);
				overflow++;
			}
		}
	}
	else
	{
		setDirection(LEFT);
		for (size_t i = 0; i < snakeSize; i++)
		{
			if (i <= 8)
				body[i].setPoint(70 + i, 9);
			else
			{
				body[i].setPoint(78, 9 - overflow);
				overflow++;
			}
		}
	}
}

void Snake::printSnakeHead()
{
	setTextColor(headColor);
	body[0].draw(c);
	setTextColor(WHITE);
}

void Snake::vanishSnake(SnakesGame& game)
{
	int i = (c == '@') ? 0 : 1;
	game.AddKeyToVanishSnake(i);
	disappearSnake();
}

void Snake::disappearSnake()
{
	for (size_t i = 0; i < snakeSize; i++)
		body[i].draw(' ');
}

void Snake::setBodyPoint(int i,int x, int y)
{
	body[i].setPoint(x, y);
}
