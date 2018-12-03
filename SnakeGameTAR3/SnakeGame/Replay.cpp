#include "Replay.h"
#include "SnakesGame.h"

/*void Replay::addkeyToSnakesArr(const Direction & dir, char c)
{
	int i = (c == '@') ? 0 : 1;
	keyPressed[i].key.push_back({ dir,countSteps });
}*/

void Replay::addKeyToDeleteBullet(int snakeNum, size_t id)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < bulletsReplay[i].bullets.size(); j++)
			if (bulletsReplay[i].bullets[j].id == id)
			{
				bulletsReplay[snakeNum].bullets[j].countDead = countSteps;
				return;
			}
	}
}

void Replay::setColorOfSnakesAndShape()
{
	snakes[0].headColor = LIGHTRED;
	snakes[0].bodyColor = YELLOW;
	snakes[0].c = '@';
	snakes[1].headColor = LIGHTBLUE;
	snakes[1].bodyColor = LIGHTCYAN;
	snakes[1].c = '#';
}

/*void Replay::enterLocationOfSnakeAfterRevive(int snakeNum, SnakesGame* _game, Direction dir)
{
	game = _game;
	vector<Point> points;
	points.resize(game->snakes[snakeNum].getSize());
	for (size_t i = 0; i < points.size(); i++)
		points[i] = game->snakes[snakeNum].getBodyPoint(i);

	locationsReviveSnake[snakeNum].locations.back().location = points;
	locationsReviveSnake[snakeNum].locations.back().countToRevive = countSteps;
	locationsReviveSnake[snakeNum].locations.back().dirAfterRevive = dir;
}*/

void Replay::run()
{
	countReplay = 0;
	while (countReplay < countSteps)
	{
		moveAllOneStep();
		Sleep(75);
		countReplay++;
	}
}

void Replay::moveAllOneStep()
{
	moveBullets();
	updateAmmu();
	deleteNumbers();
	moveCreatures();
	moveSnakes();
	enterNumber();
}

void Replay::updateAmmu()
{
	for (int i = 0; i < SIZE; i++)
	{
		if (keyAmmu[i].key.size() != 0 && keyAmmu[i].key[0].count == countReplay)
		{
			gotoxy(78, i);
			setTextColor(snakes[i].headColor);
			cout << keyAmmu[i].key[0].ammu;
			keyAmmu[i].key.erase(keyAmmu[i].key.begin());
			setTextColor(WHITE);
		}
	}
}

void Replay::enterNumber()
{
	if (arr.size() != 0 && countReplay == arr[0].count)
	{
		gotoxy(arr[0].location.getX(), arr[0].location.getY());
		cout << arr[0].num;
		arr.erase(arr.begin());
	}
}

void Replay::deleteNumbers()
{
	auto i = deleteNumbersArr.begin();
	while (i != deleteNumbersArr.end())
	{
		if (countReplay == i->count)
		{
			gotoxy(i->location.getX(), i->location.getY());
			for (size_t j = 0; j < i->numOfDigits; j++)
				cout << " ";
			deleteNumbersArr.erase(i++);
		}
		else
			i++;
	}
}

void Replay::moveSnakes()
{
	vanishSnakes();
	reviveSnakes();
	for (int i = 0; i < SIZE; i++)
	{
		if (snakes[i].alive && snakes[i].locations.size()!=0 && snakes[i].locations[0].count == countReplay)
		{
			/*snakes[i].locations[0].body.back().draw(' ');
			snakes[i].locations[0].body[1].draw(' ');
			setTextColor(snakes[i].bodyColor);
			snakes[i].locations[0].body[1].draw(snakes[i].c);
			setTextColor(snakes[i].headColor);
			snakes[i].locations[0].body[0].draw(snakes[i].c);
			setTextColor(WHITE);*/
			vanishSnake(i);
			if(snakes[i].locations.size()!=0 && !snakes[i].locations[0].reviveLocation)
			   snakes[i].locations.erase(snakes[i].locations.begin());
			if (snakes[i].locations.size() !=0 && !snakes[i].locations[0].reviveLocation)
				printSnake(i);
			else
				snakes[i].alive = FALSE;
		}
		if (!snakes[i].alive && snakes[i].locations.size()!=0 && snakes[i].locations[0].count == countReplay)
		{
			snakes[i].alive = TRUE;
			printSnake(i);
		}
	}
}

void Replay::vanishSnakes()
{
	for (int i = 0; i < SIZE; i++)
		if (snakes[i].vanish.size() != 0 && snakes[i].vanish[0].countVanish == countReplay)
		{
			vanishSnake(i);
			snakes[i].alive = FALSE;
		}
}

void Replay::vanishSnake(int i)
{
	for (size_t j = 0; j < snakes[i].locations[0].body.size(); j++)
		snakes[i].locations[0].body[j].draw(' ');
}

void Replay::reviveSnakes()
{
	/*for (int i = 0; i < SIZE; i++)
	{
		if (snakes[i].vanish.size() != 0 && snakes[i].locations[0].count!=0 && snakes[i].locations[0].count != 0 == countReplay)
		{
			snakes[i].alive = TRUE;
			snakes[i].vanish.erase(snakes[i].vanish.begin());
		}
	}*/
}

void Replay::moveBullets()
{
	/*for (int i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < bulletsReplay[i].bullets.size(); j++)
			if (bulletsReplay[i].bullets[j].countLive == countReplay)
			{
				bulletsOfSnakes[i].bullets.push_back({ { snakes[i].getDirection(),snakes[i].getBodyPoint(0),snakes[i].getSnakeHeadColor(),0 },bulletsReplay[i].bullets[j].countDead });
				//bulletsOfSnakes[i].bullets.back().bullet.moveBullet(snakes[i].getSnakeHeadColor());
			}
	}*/
	for (int i = 0; i < SIZE; i++)
	{
		auto j = bulletsOfSnakes[i].bullets.begin();
		while (j != bulletsOfSnakes[i].bullets.end())
		{
			if (countReplay < j->countDead || j->countDead == 0)
			{
				j->bullet.moveBullet(snakes[i].headColor);
				j++;
			}
			else
			{
				j->bullet.removeBulletFromScreen();
				bulletsOfSnakes[i].bullets.erase(j++);
			}
		}
	}
}

void Replay::moveCreatures()
{
	if (counterDeadCreatures[0] == 0 || countReplay < counterDeadCreatures[0])
	{
		if (keyEatingNumber.key.size() != 0 && keyEatingNumber.key.front().count == countReplay)
		{
			creatures[0]->setDirection(keyEatingNumber.key.front().dir);
			keyEatingNumber.key.erase(keyEatingNumber.key.begin());
			drawCreature(0);
		}
		if (creatures[0]->isCreatureAlive())
			creatures[0]->drawShape();
	}
	else if (countReplay == counterDeadCreatures[0])
		creatures[0]->removeCreatureFromScreen();

	for (int i = 1; i<3; i++)
		if (countReplay == counterDeadCreatures[i])
			flyingCols[i - 1].removeCreatureFromScreen();

	int withFlyingCol = (countReplay % 2 == 0) ? 0 : 2;
	for (int i = 1; i < game->SIZE_CREATURES - withFlyingCol; i++)
	{
		if (creatures[i]->isCreatureAlive())
		{
			creatures[i]->getNextDir();
			drawCreature(i);
		}
	}
}

void Replay::printCreatures()
{
	for (int i = 0; i < SnakesGame::SIZE_CREATURES; i++)
		creatures[i]->drawShape();
}

void Replay::drawCreature(int i)
{
	creatures[i]->Creature::removeCreatureFromScreen();
	creatures[i]->move();
	creatures[i]->drawShape();
}

void Replay::initiateReplay()
{
	
	enterNumbersToReplayScreen();
	countSteps = 0;
	showLastMissionPreview = FALSE;

	eatingNumber.initiateCreature({ 10,19 }, UP);
	flyingRows[0].initiateFlyingRows({ 30,23 }, RIGHT);
	flyingRows[1].initiateFlyingRows({ 50,15 }, LEFT);
	flyingCols[0].initiateFlyingCols({ 55,15 }, DOWN);
	flyingCols[1].initiateFlyingCols({ 45,23 }, UP);

	initiateArrays();
}

void Replay::initiateArrays()
{
	arr.resize(0);
	keyEatingNumber.key.resize(0);
	deleteNumbersArr.resize(0);

	for (int i = 0; i < SIZE; i++)
	{
		snakes[i].alive = TRUE;
		snakes[i].locations.resize(0);
		snakes[i].vanish.resize(0);
		bulletsReplay[i].bullets.resize(0);
		bulletsOfSnakes[i].bullets.resize(0);
		keyAmmu[i].key.resize(0);
	}
	for (int i = 0; i < 3; i++)
		counterDeadCreatures[i] = -1;
}

void Replay::handlePreviewIfNeeded(SnakesGame* _game)
{
	game = _game;

	if (showLastMissionPreview)
	{
		printStatus("Replay");
		showLastMission();
		showLastMissionPreview = FALSE;
		printStatus("End Of Replay");
		game->printFrame();
		game->printSnakes();
		game->printLastScreenNumbers();
	}
	initiateReplay();
}

void Replay::printCurrentScreen()
{
	for (int i = Point::min_y; i < MAX_ROWS; i++)
		for (int j = 0; j < MAX_COLS; j++)
		{
			gotoxy(j, i);
			if (screen[i][j] != ' ')
				cout << screen[i][j];
		}
}

void Replay::enterNumbersToReplayScreen()
{
	for (int i = Point::min_y; i < Point::max_y; i++)
		for (int j = Point::min_x; j < Point::max_x; j++)
			screen[i][j] = game->screen[i][j];
}

void Replay::showLastMission()
{
	printCurrentScreen();
	game->printFrame();
	printCreatures();
	printSnakes();
	gotoxy(0, 0);
	cout << game->missions.getCurrentQuestion();
	for (int i = 0; i<SIZE; i++)
		printStats(i);

	run();
}

void Replay::printStatus(const string& str)
{
	clrscr();
	gotoxy(20, 10);
	setTextColor(YELLOW);
	cout << str;
	setTextColor(WHITE);
	Sleep(2000);
	clrscr();
}

void Replay::printSnakes()
{
	for (int i = 0; i < SIZE; i++)
		printSnake(i);
}

void Replay::printSnake(int i)
{
	if (snakes[i].locations.size() != 0)
	{
		setTextColor(snakes[i].headColor);
		snakes[i].locations[0].body[0].draw(snakes[i].c);
		setTextColor(snakes[i].bodyColor);
		for (size_t j = 1; j < snakes[i].locations[0].body.size(); j++)
			snakes[i].locations[0].body[j].draw(snakes[i].c);
	
	}
	setTextColor(WHITE);
}

void Replay::printStats(int i)
{
	setTextColor(snakes[i].headColor);
	gotoxy(62, i);
	cout << "|" << snakes[i].c;
	cout << " Score:" << snakes[i].score;
	if (snakes[i].score / 10 == 0)  cout << " ";
	cout << ",Amo:" << 5;
	setTextColor(WHITE);
}

void Replay::makeArrayCreatures()
{
	creatures[0] = &eatingNumber;
	for (int i = 0; i < game->SIZE; i++)
	{
		creatures[i + 1] = &flyingRows[i];
		creatures[i + 3] = &flyingCols[i];
	}
}