#ifndef _EATING_NUMBER_H_
#define _EATING_NUMBER_H_

#include "io_utils.h"
#include "Creature.h"

class SnakesGame;

class EatingNumber : public Creature
{
	Point destination;
	class Numbers {
	public:
		int num;
		vector<Point> location;
		vector<int> distance;
	};
	vector<Numbers> arr;
	bool isAlive;
	int distanceFromDestination;
	friend class SnakesGame;

public:

	EatingNumber(char _shape, Color _color, Direction _direction, Point _location): Creature(_shape, _color, _direction, _location),isAlive(TRUE){}
	void initiateEatingNumber(SnakesGame& game);
	BOOL checkIfEatingNumberHasDestination()const;
	virtual void handleCreature(SnakesGame& game)override;
	virtual BOOL isCreatureAlive()const override { return isAlive; }

	void changeDestinationIfNecessary();
	const BOOL isEatingNumberAlive()const { return isAlive; }
	void moveTowardsDestination(SnakesGame & game);
	virtual void removeCreatureFromScreen()override;
	void getNextDir();
	int getCountRowsFromTop(int y, const Point& pos)const;
	int getCountRowsFromDown(int y, const Point& pos)const;
	int getCountColsFromRight(int x, const Point& pos)const;
	int getCountColsFromLeft(int x, const Point& pos)const;
	virtual void handleNextCreaturePosition(SnakesGame & game, BOOL exceptionalEvent)override;
	void enterNumberToArr(int x, int y, int countDigit, int num, bool endLine);
	void findClosestNumber();
	void getIndexOfMinimumInArr(size_t & i, size_t & j)const;
	int getTheDistanceOfDigit(const Point& pos);
	virtual BOOL checkIfPosIsACreature(const Point& pos)const override;
	void deleteNumber(const Point & pos);
	void handleIfDestinationIsTheDeletedNumber(size_t i);
};


#endif 
