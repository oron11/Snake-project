#include "Point.h"

void Point::changeDir(Direction dir) {
	switch (dir) {
	case Direction::LEFT:
		dir_x = -1;
		dir_y = 0;
		break;
	case Direction::RIGHT:
		dir_x = 1;
		dir_y = 0;
		break;
	case Direction::UP:
		dir_x = 0;
		dir_y = -1;
		break;
	case Direction::DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	}
}

void Point::move(Direction dir)
{
	changeDir(dir);
	switch (dir)
	{
	case 0: // left
		--x;
		if (x < min_x) {
			x = max_x;
		}
		break;
	case 1: // right
		++x;
		if (x > max_x) {
			x = min_x;
		}
		break;
	case 2: // up
		--y;
		if (y < min_y) {
			y = max_y;
		}
		break;
	case 3: // down
		++y;
		if (y > max_y) {
			y = min_y;
		}
	}
}

bool operator==(const Point & pointA, const Point & pointB)
{
	return (pointA.getX() == pointB.getX() && pointA.getY() == pointB.getY());
}
