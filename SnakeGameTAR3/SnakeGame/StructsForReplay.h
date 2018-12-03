#ifndef _STRUCTS_FOR_REPLAY_H_
#define _STRUCTS_FOR_REPLAY_H_

#include <list>

struct Number {
	int num;
	Point location;
	size_t count;
};
struct Ammu
{
	size_t ammu, count;
};
struct KeyAmmu
{
	vector<Ammu> key;
};
struct Vanish
{
   size_t countVanish;
   int countToRevive;
};
struct Location {
	vector<Point> body;
	size_t count;
	BOOL reviveLocation;
};
struct SnakeReplay {
	vector<Location> locations;
	vector<Vanish> vanish;
	BOOL alive;
	Color headColor, bodyColor;
	char c;
	size_t score;
};
struct KeyPressed {
	Direction dir;
	size_t count;
};
struct KeysPressed {
	vector<KeyPressed> key;
};
struct DeleteNumber {
	Point location;
	size_t count;
	size_t numOfDigits;
};
struct BulletReplay {
	size_t countLive, countDead,id;
};
struct BulletsReplay {
	vector<BulletReplay> bullets;
};
struct BulletsAliveSnake {
	Bullet bullet;
	size_t countDead;
};
struct BulletsOfSnake {
	list<BulletsAliveSnake> bullets;
};


#endif