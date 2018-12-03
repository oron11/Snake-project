#include "EatingNumber.h"
#include "SnakesGame.h"

void EatingNumber::initiateEatingNumber(SnakesGame& game)
{
	initiateCreature({ 10,19 },UP);
	destination = { -1,-1 };
	distanceFromDestination = Questions::MAX_VALUE_NUMBER;
	arr.resize(0);
	isAlive = TRUE;
	game.checkForAvailableSolution(2);
}

BOOL EatingNumber::checkIfEatingNumberHasDestination()const
{
	Point p= { -1,-1 };
	return !(destination == p);
}

void EatingNumber::handleCreature(SnakesGame& game)
{
	if (isAlive)
	{
		drawShape();
		if (checkIfEatingNumberHasDestination())
		{
			Creature::removeCreatureFromScreen();
			moveTowardsDestination(game);
		}	
	}
}

void EatingNumber::changeDestinationIfNecessary()
{
	for (size_t i = 0; i < arr.back().distance.size(); i++)
		if (arr.back().distance[i] < distanceFromDestination)
		{
			distanceFromDestination = arr.back().distance[i];
			destination = arr.back().location[i];
		}
}

void EatingNumber::moveTowardsDestination(SnakesGame& game)
{
	getNextDir();
	move();
	distanceFromDestination--;
	game.replay.addkeyToEatingNumberArr(getDirection());
	handleNextCreaturePosition(game,FALSE);
	if(isAlive)
	   drawShape();
}

void EatingNumber::removeCreatureFromScreen()
{
	isAlive = FALSE;
	Creature::removeCreatureFromScreen();
}

void EatingNumber::getNextDir()
{
	int countColsFromRight, countColsFromLeft, countRowsFromTop, countRowsFromDown;
	int x = getLocation().getX(), y = getLocation().getY();

	countColsFromRight = getCountColsFromRight(x,destination);
	countColsFromLeft = getCountColsFromLeft(x, destination);
	countRowsFromTop = getCountRowsFromTop(y, destination);
	countRowsFromDown = getCountRowsFromDown(y, destination);

	if (countColsFromRight < countColsFromLeft)
			setDirection(RIGHT);
	else if (countColsFromRight > countColsFromLeft)
		    setDirection(LEFT);
	else if (countRowsFromTop < countRowsFromDown)
		    setDirection(UP);
	else
		    setDirection(DOWN);
}

int EatingNumber::getCountRowsFromTop(int y, const Point& pos)const
{
	int countRowsFromTop = 0;
	while (y != pos.getY())
	{
		y--;
		if (y == Point::min_y - 1)
			y = Point::max_y;
		countRowsFromTop++;
	}
	return countRowsFromTop;
}

int EatingNumber::getCountRowsFromDown(int y, const Point& pos)const
{
	int countRowsFromDown = 0;
	while (y != pos.getY())
	{
		y++;
		if (y == Point::max_y + 1)
			y = Point::min_y;
		countRowsFromDown++;
	}
	return countRowsFromDown;
}

int EatingNumber::getCountColsFromRight(int x, const Point& pos)const
{
	int countColsFromRight = 0;
	while (x != pos.getX())
	{
		x++;
		if (x == Point::max_x + 1)
			x = Point::min_x;
		countColsFromRight++;
	}
	return countColsFromRight;
}

int EatingNumber::getCountColsFromLeft(int x, const Point& pos)const
{
	int countColsFromLeft = 0;
	while (x != pos.getX())
	{
		x--;
		if (x == Point::min_x - 1)
			x = Point::max_x;
		countColsFromLeft++;
	}
	return countColsFromLeft;
}

void EatingNumber::handleNextCreaturePosition(SnakesGame & game, BOOL exceptionalEvent)
{
	for (int i = 0; i < game.SIZE; i++)
		if (game.snakes[i].checkIfNextStepIsTheSnakeItself(getLocation(), 0))
		{
			game.vanishSnake(game.snakes[i]);
			game.snakes[i].setLifeOfTheSnake(FALSE);
			if (!exceptionalEvent)
			{
				int otherSnake = (i == 0) ? 1 : 0;
				game.snakes[otherSnake].increaseSnake();
				gotoxy(0, 1);
				cout << "snake " << game.snakes[i].getChar() << " Has Got Eaten by eating numbers!";
				Sleep(4000);
				gotoxy(0, 1);
				cout << "                                                      ";
				game.endMission = TRUE;
				game.cleanHalfOfScreen();
			}
			game.reviveSnake(game.snakes[i]);
		}
	game.getNumber(getLocation(), TRUE);
	if (game.checkIfPosIsBullet(getLocation(), TRUE))
	{
		game.enterDeadCounterCreature(0);
		isAlive = FALSE;
	}
}

void EatingNumber::enterNumberToArr(int x, int y, int countDigit,int num,bool endLine)
{
	vector<Point> points;
	for (int i = 1; i <= countDigit; i++)
		points.push_back({ y - i + endLine,x });
	
	arr.push_back({ num,points });
	for (size_t i = 0; i < arr.back().location.size(); i++)
		arr.back().distance.push_back(getTheDistanceOfDigit(arr.back().location[i]));

	changeDestinationIfNecessary();
}

void EatingNumber::findClosestNumber()
{
	if (arr.size() == 0)
		return;

	size_t i, j;
	getIndexOfMinimumInArr(i,j);
	destination = arr[i].location[j];
	distanceFromDestination = arr[i].distance[j];
}

void EatingNumber::getIndexOfMinimumInArr(size_t &i, size_t& j)const
{
	i=0,j=0;
	for (size_t k = 0; k < arr.size(); k++)
		for(size_t t = 0; t < arr[k].distance.size(); t++)
			if (arr[k].distance[t] < arr[i].distance[j])
				i = k, j = t;
}

int EatingNumber::getTheDistanceOfDigit(const Point& pos)
{
	int res=0;
	int countColsFromRight = getCountColsFromRight(pos.getX(), getLocation());
	int countColsFromLeft = getCountColsFromLeft(pos.getX(), getLocation());
	int countRowsFromTop = getCountRowsFromTop(pos.getY(), getLocation());
	int countRowsFromDown = getCountRowsFromDown(pos.getY(), getLocation());

	if (countColsFromRight < countColsFromLeft)
		res = countColsFromRight;
	else
		res = countColsFromLeft;
	if (countRowsFromTop < countRowsFromDown)
		res += countRowsFromTop;
	else
		res += countRowsFromDown;

	return res;
}

BOOL EatingNumber::checkIfPosIsACreature(const Point& pos)const
{
	if (isAlive)
		return Creature::checkIfPosIsACreature(pos);
	return FALSE;
}

void EatingNumber::deleteNumber(const Point& pos)
{
	for(size_t i=0;i<arr.size();i++)
		for(size_t j=0;j<arr[i].location.size();j++)
			if (arr[i].location[j]== pos)
			{
				handleIfDestinationIsTheDeletedNumber(i);
				arr.erase(arr.begin() + i);
				if (!checkIfEatingNumberHasDestination())
					findClosestNumber();
				return;
			}

}

void EatingNumber::handleIfDestinationIsTheDeletedNumber(size_t i)
{
	for (size_t j = 0; j < arr[i].location.size(); j++)
		if (arr[i].location[j]== destination)
		{
			destination = { -1,-1 };
			distanceFromDestination = Questions::MAX_VALUE_NUMBER;
		}
}


