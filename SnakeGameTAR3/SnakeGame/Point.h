#ifndef _POINT_H_
#define _POINT_H_

#include "gotoxy.h"

using namespace std;

class Point
{
	int x;
	int y;
	int dir_x = 1;
	int dir_y = 0;

public:
	enum { min_x = 1, max_x = 78, min_y = 3, max_y = 23 };
	Point(int x1 = 1, int y1 = 1) {
		x = x1;
		y = y1;
	}
	void setPoint(int x1, int y1) { x = x1; y = y1; }
	int getX() const { return x; }
    int getY() const { return y; }
	void draw(char c = '*')
	{
		gotoxy(x, y);
		cout << c << endl;
	}
	void changeDir(Direction dir);
	void move(Direction dir);
	friend bool operator==(const Point& pointA, const Point& pointB);

};


#endif
