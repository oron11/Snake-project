#include "MenuManager.h"
#include "SnakesGame.h"

void SnakesGame::run()
{
	//playStartMusic();
	printFrame();

	while (true)
	{
		char keyPressed = 0;
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == ESC)
			{
				choice = getSubMenuChoice(TRUE);
				executeSubMenuChoice();
				if (choice == '1' || choice == '2')
					break;
			}
		}
		Sleep(120);
		countForEnterNum++;
		if (checkIfGameEnded())
		{
			choice = '2';
			break;
		}
		checkIfMissionEnded();
		endMission = FALSE;
		bullets.shootBullets(*this, keyPressed);
		for (size_t i = 0; i < SIZE; ++i)
		{
			handleUtilities(i);
			handleSnake(keyPressed,i);
			handleIfThereAre60NumbersOnScreen();
			checkIfMissionEnded();
		}
		enterNumberEach5steps();
		endMission = FALSE;
	}
}

void SnakesGame::handleSnake(char keyPressed,size_t snakeNum)
{
	if (!endMission && snakes[snakeNum].isSnakeAlive())
	{
		Point pos = snakes[snakeNum].move(*this, keyPressed, snakes[(snakeNum- 1) % 2]); // move and check if the snake ate a number
		int num = getNumber(pos, TRUE);
		endMission = checkIfSnakeGotNumber(snakeNum, num);
	}
	printStats(snakeNum);
}

void SnakesGame::handleUtilities(int time)
{
	replay.addStepToMission();
	bullets.handleBullets(*this,0,SIZE);

	int handleAll=SIZE_CREATURES;
	if (time == 1) //if time==0 then flyingCols also moving
		handleAll = 3;

	for (int i = 0; i < handleAll; i++)
		creatures[i]->handleCreature(*this);
}

SnakesGame::SnakesGame()
{
	snakes[0].setKeys('a', 'd', 'w', 'x');
	snakes[1].setKeys('j', 'l', 'i', ',');
	makeArrayCreatures();
	initiateScreen();
	countForEnterNum = 0;
	countNumbersOnScreen = 0;
	endMission = TRUE;
}

void SnakesGame::makeArrayCreatures()
{
    creatures[0] = &eatingNumber;
    for (int i = 0; i < SIZE; i++)
     {
		 creatures[i + 1] = &flyingRows[i];
         creatures[i + 3] = &flyingCols[i];
     }
}

void SnakesGame::checkIfMissionEnded()
{
	if (endMission)
	{
		replay.handlePreviewIfNeeded(this);
		checkIfSnakesIsTrapped();
		gotoxy(0, 0);
		cout << "                                                         ";
		gotoxy(0, 0);
		if (choice != '4')
			cout << missions.getQuestion();
		else
		{
			cout << missions.getCurrentQuestion();
			choice = '0';
		}
		initiateUtilities();
		countForEnterNum = 0;
		for(int i=0;i<SIZE;i++)
		   addkeyToReplayArr(i, snakes[i].getBody());
	}
}

void SnakesGame::initiateUtilities()
{
	bullets.initiateBullets(*this);
	eatingNumber.initiateEatingNumber(*this);
	flyingRows[0].initiateFlyingRows({ 30,23 },RIGHT);
	flyingRows[1].initiateFlyingRows({ 50,15 },LEFT);
	flyingCols[0].initiateFlyingCols({ 55,15 },DOWN);
	flyingCols[1].initiateFlyingCols({ 45,23 },UP);
	checkForAnExceptionalEvent();
}

void SnakesGame::checkForAnExceptionalEvent()
{
	for (int i = 0; i < SIZE_CREATURES; i++)
		creatures[i]->handleNextCreaturePosition(*this, TRUE);
}

void SnakesGame::checkIfSnakesIsTrapped()
{
	for (int i = 0; i < SIZE; i++)
	{
	  if(snakes[i].checkIfSnakeIsTrapped())
	  {
			placeSnakesInStartPosition();
			printFrame();
		}
	}
}

void SnakesGame::placeSnakesInStartPosition()
{
	initiateScreen();
	for (int i = 0; i < SIZE; i++)
	{
		snakes[i].placeSnakeInStartPosition();
		snakes[i].printSnake();
	}
}

void SnakesGame::handleIfThereAre60NumbersOnScreen()
{
	if (!endMission && countNumbersOnScreen >= 60)
	{
		gotoxy(0, 1);
		cout << "There is 60 numbers on the screen, please wait until next mission.";
		if (!checkForAvailableSolution(1))
		{
			gotoxy(0, 2);
			cout << "Unfortunately there is not possible solution although thank you for the effort! ";
			Sleep(3500);
			printFrame();
		}
		else
			Sleep(900);
		gotoxy(0, 1);
		cout << "                                                                      ";
		cleanHalfOfScreen();
		endMission = TRUE;
		for (int i = 0; i<SIZE; i++)
			if (snakes[i].isSnakeAlive() == FALSE)
				reviveSnake(snakes[i]);
	}
}

void SnakesGame::handleSnakesHitted()
{
	for (int i = 0; i < SIZE; i++)
	{
		if (!snakes[i].isSnakeAlive())
		{
			snakes[i].setCountToReviveSnake(snakes[i].getCountToReviveSnake() + 1);
			if (snakes[i].getCountToReviveSnake() >= 50)
				    reviveSnake(snakes[i]);
		}
	}
}

void SnakesGame::reviveSnake(Snake& snake)
{
	bool otherSnake = (snake.getChar() == '@') ? 1 : 0;
	Point potentialLocation;
	BOOL fromTop = FALSE, fromRight = FALSE, fromLeft = FALSE, fromBottom = FALSE;
	do {
		potentialLocation = getRandomLocation();
		fromLeft = checkIfPosLegalFromLeft(potentialLocation, otherSnake, snake);
		if (!fromLeft)
			fromRight = checkIfPosLegalFromRight(potentialLocation, otherSnake, snake);
		else if (!fromRight)
			fromTop = checkIfPosLegalFromTop(potentialLocation, otherSnake, snake);
		else if (!fromTop)
			fromBottom = checkIfPosLegalFromBottom(potentialLocation, otherSnake, snake);

	} while (!fromLeft && !fromRight && !fromTop && !fromBottom);

	if (fromLeft)
		placeSnakeFromLeft(potentialLocation, snake);
	else if (fromRight)
		placeSnakeFromRight(potentialLocation, snake);
	else if (fromTop)
		placeSnakeFromTop(potentialLocation, snake);
	else
		placeSnakeFromBottom(potentialLocation, snake);

	snake.setCountToReviveSnake(0);
	snake.setLifeOfTheSnake(TRUE);
	replay.addLocation(!otherSnake, snakes[!otherSnake].getBody(),TRUE);
	printSnakes();
}

BOOL SnakesGame::checkIfPosLegalFromRight(const Point& location, int otherSnake,const Snake& snake)
{
	Point nextStep = location;
	for (size_t i = 0; i < snake.getSize(); i++)
	{
		if (snake.checkIfnextStepIsOtherSnake(nextStep, snakes[otherSnake]) || checkIfPosIsOtherObjects(nextStep))
			return FALSE;
		nextStep.setPoint(nextStep.getX() + 1, nextStep.getY());
		if (nextStep.getX() == Point::max_x + 1)
			nextStep.setPoint(Point::min_x, nextStep.getY());
	}
	return TRUE;
}

BOOL SnakesGame::checkIfPosLegalFromTop(const Point& location, int otherSnake,const Snake& snake)
{
	Point nextStep = location;
	for (size_t i = 0; i < snake.getSize(); i++)
	{
		if (snake.checkIfnextStepIsOtherSnake(nextStep, snakes[otherSnake]) || checkIfPosIsOtherObjects(nextStep))
			return FALSE;
		nextStep.setPoint(nextStep.getX(), nextStep.getY() - 1);
		if (nextStep.getY() == Point::min_y - 1)
			nextStep.setPoint(nextStep.getX(), Point::max_y);
	}
	return TRUE;
}

BOOL SnakesGame::checkIfPosLegalFromBottom(const Point& location, int otherSnake,const Snake& snake)
{
	Point nextStep = location;
	for (size_t i = 0; i < snake.getSize(); i++)
	{
		if (snake.checkIfnextStepIsOtherSnake(nextStep, snakes[otherSnake]) || checkIfPosIsOtherObjects(nextStep))
			return FALSE;
		nextStep.setPoint(nextStep.getX(), nextStep.getY() + 1);
		if (nextStep.getY() == Point::max_y + 1)
			nextStep.setPoint(nextStep.getX(), Point::min_y);
	}
	return TRUE;
}

BOOL SnakesGame::checkIfPosIsOtherObjects(const Point& nextStep)
{
	return (checkIfPosIsBullet(nextStep,FALSE) || checkIfPosIsOneOfCreature(nextStep));
}

void SnakesGame::placeSnakeFromLeft(Point location, Snake& snake)
{
	snake.setDirection(LEFT);
	for (size_t i = 0; i < snake.getSize(); i++)
	{
		getNumber(location,TRUE);
		snake.setBodyPoint(i, location.getX(), location.getY());
		location.setPoint(location.getX() - 1, location.getY());
		if (location.getX() == Point::min_x - 1)
			location.setPoint(Point::max_x, location.getY());
	}
}

void SnakesGame::placeSnakeFromRight(Point location, Snake& snake)
{
	snake.setDirection(RIGHT);
	for (size_t i = 0; i < snake.getSize(); i++)
	{
		getNumber(location,TRUE);
		snake.setBodyPoint(i,location.getX(), location.getY());
		location.setPoint(location.getX() + 1, location.getY());
		if (location.getX() == Point::max_x + 1)
			location.setPoint(Point::min_x, location.getY());
	}
}

void SnakesGame::placeSnakeFromTop(Point location, Snake& snake)
{
	snake.setDirection(UP);
	for (size_t i = 0; i < snake.getSize(); i++)
	{
		getNumber(location,TRUE);
		snake.setBodyPoint(i, location.getX(), location.getY());
		location.setPoint(location.getX(), location.getY() - 1);
		if (location.getY() == Point::min_y - 1)
			location.setPoint(location.getX(), Point::max_y);
	}
}

void SnakesGame::placeSnakeFromBottom(Point location, Snake& snake)
{
	snake.setDirection(DOWN);
	for (size_t i = 0; i < snake.getSize(); i++)
	{
		getNumber(location, TRUE);
		snake.setBodyPoint(i, location.getX(), location.getY());
		location.setPoint(location.getX(), location.getY() + 1);
		if (location.getY() == Point::max_y + 1)
			location.setPoint(location.getX(), Point::min_y);
	}
}

BOOL SnakesGame::checkIfPosLegalFromLeft(const Point& location, int otherSnake,const Snake& snake)
{
	Point nextStep = location;
	for (size_t i = 0; i < snake.getSize(); i++)
	{
		if (snake.checkIfnextStepIsOtherSnake(nextStep, snakes[otherSnake]) || checkIfPosIsOtherObjects(nextStep))
			return FALSE;
		nextStep.setPoint(nextStep.getX() - 1, nextStep.getY());
		if (nextStep.getX() == Point::min_x - 1)
			nextStep.setPoint(Point::max_x, nextStep.getY());
	}
	return TRUE;
}

BOOL SnakesGame::checkIfPosIsOneOfCreature(const Point& location)const
{
	for (int i = 0; i < SIZE_CREATURES; i++)
		if (creatures[i]->checkIfPosIsACreature(location))
			return TRUE;
	return FALSE;
}

BOOL SnakesGame::checkIfPosIsFlyingRow(const Point& location)const
{
	return (flyingRows[0].checkIfPosIsACreature(location)|| flyingRows[1].checkIfPosIsACreature(location));
}

BOOL SnakesGame::checkIfPosIsEatingNumber(const Point& location)const
{
	return eatingNumber.checkIfPosIsACreature(location);
}

BOOL SnakesGame::checkIfPosIsFlyingCol(const Point& location)const
{
	return (flyingCols[0].checkIfPosIsACreature(location) || flyingCols[1].checkIfPosIsACreature(location));
}

BOOL SnakesGame::checkIfPosIsBullet(const Point& location,BOOL eraseBullet)
{
	return bullets.checkIfPosIsBullet(location, *this, eraseBullet);
}

BOOL SnakesGame::checkIfGameEnded()
{
	for (int i = 0; i < SIZE; i++)
	{
		if (snakes[i].getScore() == WIN_GAME)
		{

			clrscr();
			gotoxy(10, 5);
			cout << "Snake " << snakes[i].getChar() << " WON the Game !!!";
			time_t end = time(NULL) + 3;
			while (time(NULL) <= end)
			{
				gotoxy(10, 5); // move to where we want to output
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				setTextColor(snakes[i].getSnakeHeadColor());
				cout << "Snake " << snakes[i].getChar() << " WON the Game !!!"; // overwrite the current output
				Sleep(600);
				gotoxy(10, 5); // move back to the start of output							
				for (int i = 0; i < 26; i++)
					cout << " ";
				Sleep(300);
			}
			gotoxy(10, 5);
			cout << "Snake " << snakes[i].getChar() << " WON the Game !!!";
			Sleep(3000);
			setTextColor(WHITE);
			playTriumphMusic();
			return TRUE;
		}
	}
	return FALSE;
}

void SnakesGame::executeSubMenuChoice()
{
	if (choice == '7')
	{
		replay.setPreviewOfMission(TRUE);
		gotoxy(0, 18);
		cout << "Your choice has been received, Replay will be shown in the end of the mission." << endl;
		cout << "Enter your next choice please (1-6)";
		choice = getSubMenuChoice(FALSE);
		clrscr();
	}
	if (choice == '3')
	{
		printLastScreenNumbers();
		printSnakes();
		gotoxy(0, 0);
		cout << missions.getCurrentQuestion();
	}
	else
	{
		endMission = TRUE;
		replay.handlePreviewIfNeeded(this);
		if (choice == '4' || choice == '5')
		{
			placeSnakesInStartPosition();
			countForEnterNum = 0;
		}
		else if (choice == '6')
		{
			initiateGame();
			printSnakes();
		}
	}
	printFrame();
}

void SnakesGame::initiateGame()
{
	endMission = TRUE;
	initiateScreen();

	snakes[0].initiateSnake({ 10,9 }, RIGHT, INITIAL_SIZE);
	snakes[1].initiateSnake({ 70,9 }, LEFT, INITIAL_SIZE);
}

void SnakesGame::initiateScreen()
{
	clrscr();
	countNumbersOnScreen = 0;
	countForEnterNum = 0;
	for (int i = 0; i < MAX_ROWS; i++)
		for (int j = 0; j < MAX_COLS; j++)
			screen[i][j] = ' ';

}

void SnakesGame::printStats(int i)
{
	setTextColor(snakes[i].getSnakeHeadColor());
	gotoxy(62, i);
	cout << "|" << snakes[i].getChar();
	cout << " Score:" << snakes[i].getScore();
	if(snakes[i].getScore() / 10 == 0)  cout << " ";
	cout << ",Amo:" << snakes[i].getAmmunition();
	setTextColor(WHITE);
}

BOOL SnakesGame::checkForAvailableSolution(int functionChoice)
{
	int x, y, digit, num = 0, digitsCounter = 0;
	BOOL startOfNumber = FALSE, res = FALSE;

	for (x = Point::min_y; x <= Point::max_y; x++)
	{
		for (y = Point::min_x; y <= Point::max_x; y++)
		{
			if (screen[x][y] != ' ')
			{
				startOfNumber = TRUE;
				digit = getDigit(y, x);
				digitsCounter++;
				num = num * 10 + digit;
			}
			else if (startOfNumber)
			{
				if (missions.checkIfNumIsCorrect(num))
				{
					res = TRUE;
					if (functionChoice == 1)
						flickeringNumber(y - digitsCounter, x, num, digitsCounter);
					else
						eatingNumber.enterNumberToArr(x, y, digitsCounter, num, FALSE);
				}
				startOfNumber = FALSE;
				num = 0;
				digitsCounter = 0;
			}
			if (y == Point::max_x && startOfNumber)
			{
				if (missions.checkIfNumIsCorrect(num))
				{
					res = TRUE;
					if(functionChoice == 1)
						flickeringNumber(y + 1 - digitsCounter, x, num, digitsCounter);
					else
						eatingNumber.enterNumberToArr(x, y, digitsCounter, num, TRUE);
				}
				startOfNumber = FALSE;
				num = 0;
				digitsCounter = 0;
			}
		}
	}
	return res;
}

void SnakesGame::flickeringNumber(int y, int x, int num, int digitsCounter)
{
	time_t end = time(NULL) + 1;
	while (time(NULL) <= end)
	{
		gotoxy(y, x); // move to where we want to output
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << num; // overwrite the current output
		Sleep(600);
		gotoxy(y, x); // move back to the start of output							
		for (int i = 0; i < digitsCounter; i++)
			cout << " ";
		Sleep(300);
	}
	setTextColor(WHITE);
	gotoxy(y, x);
	cout << num;
}

BOOL SnakesGame::checkIfSnakeGotNumber(int snakeNum, int num)
{
	BOOL AvailableSolutions = FALSE;
	if (num != -1)
	{
		Beep(530, 100);
		snakes[snakeNum].printSnakeHead();
		int otherSnake = (snakeNum == 1) ? 0 : 1;
		if (missions.checkIfNumIsCorrect(num))
		{
			gotoxy(0, 1);
			cout << "snake " << snakes[snakeNum].getChar() << " got number : " << num << " successfully!";
			snakes[snakeNum].increaseSnake();
		}
		else
		{
			Sleep(150);
			gotoxy(0, 1);
			cout << "snake " << snakes[snakeNum].getChar() << " collected wrong number";
			snakes[otherSnake].increaseSnake();
			if (!checkForAvailableSolution(1))
			{
				AvailableSolutions = TRUE;
				gotoxy(0, 2);
				cout << "Unfortunately there is not possible solution although thank you for the effort! ";
			}
		}
		Sleep(4000);
		gotoxy(0, 1);
		cout << "                                                      ";
		if (AvailableSolutions)
			printFrame();

		cleanHalfOfScreen();
		if (!snakes[otherSnake].isSnakeAlive())
			reviveSnake(snakes[otherSnake]);
		return TRUE;
	}
	return FALSE;
}

void SnakesGame::enterNumberEach5steps()
{
	int num;
	Point potentialLocation;

	handleSnakesHitted();
	if (countForEnterNum == 10)
	{
		countNumbersOnScreen++;
		num = randomizeNumber();
		do {
			potentialLocation = getRandomLocation();
		} while (!enterNumberToScreen(num, potentialLocation.getY(), potentialLocation.getX()));
		
		countForEnterNum = 0;
	}
}

Point SnakesGame::getRandomLocation()
{
	int x = rand() % 21 + 3;
	int y = rand() % Point::max_x + 1;
	return{ y,x };
}

void SnakesGame::cleanHalfOfScreen()
{
	int currcountNumbersOnScreen=countNumbersOnScreen / 2;
	int x = 3, y = 0, i = 0;

	while (i < currcountNumbersOnScreen)
	{
		if (screen[x][y] != ' ')
		{
			if (rand() % 2 == 0)
			{
				i++;
				while (y <= Point::max_x && screen[x][y] != ' ')
				{
					gotoxy(y, x);
					cout << " ";
					screen[x][y++] = ' ';
				}
			}
			else
				while (y <= Point::max_x && screen[x][y] != ' ')
					y++;
		}
		else
			y++;

		if (y == Point::max_x + 1)
		{
			x++;
			if (x == MAX_ROWS)
				x = Point::min_y;
			y = 0;
		}
	}
	countNumbersOnScreen = (countNumbersOnScreen % 2 == 0) ? countNumbersOnScreen / 2 : countNumbersOnScreen / 2 + 1;
}

int SnakesGame::getNumber(const Point& pos, BOOL eraseNumber)
{
	int x = pos.getX();
	int y = pos.getY();
	if (screen[y][x] == ' ')
		return -1;
	int num = 0;
	while (x >= Point::min_x && getDigit(x, y) != -1) //go left
		--x;
	++x;
	int colLeftDigit = x; //for replay key
	int digit;
	while (x <= Point::max_x && (digit = getDigit(x, y)) != -1) //go right
	{
		if (eraseNumber)
		{
			screen[y][x] = ' ';
			gotoxy(x, y);
			cout << " ";
		}
		++x;
		num = num * 10 + digit;
	}
	if (eraseNumber)
	{
		countNumbersOnScreen--;
		eatingNumber.deleteNumber(pos);
		replay.addkeyToDeleteNumberArr({ colLeftDigit,y }, getNumOfDigits(num));
	}
	return num;
}

void SnakesGame::printFrame()
{
	setTextColor(LIGHTGREEN);
	for (int i = 2; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			if (i == Point::min_y-1 || i == Point::max_y+1)
			{
				gotoxy(j, i);
				cout << "-";
			}
			else if (j == Point::min_x - 1 || j == Point::max_x+1)
			{
				gotoxy(j, i);
				cout << "|";
			}
		}
	}
	gotoxy(0, 0);
	setTextColor(WHITE);
}

BOOL SnakesGame::enterNumberToScreen(int num, int x, int y)
{
	int numOfDigits, cpyNum = num, cpyY = y, cpyNumOfDigits;
	BOOL posLegalFromL = TRUE, posLegalFromR = TRUE,res=FALSE;
	numOfDigits = getNumOfDigits(num);
	cpyNumOfDigits = numOfDigits;

	while (cpyNumOfDigits > 0 && posLegalFromL) //put from left to right
	{
		if (cpyY <= Point::max_x)
		{
			if (!checkIfPosIsLegal(x, cpyY++))
				posLegalFromL = FALSE;
		}
		else
			posLegalFromL = FALSE;
		cpyNumOfDigits--;
	}
	cpyNumOfDigits = numOfDigits;
	cpyY = y;
	if (!posLegalFromL) // put from right to left
	{
		while (cpyNumOfDigits > 0 && posLegalFromR)
		{
			if (cpyY >= Point::min_x)
			{
				if (!checkIfPosIsLegal(x, cpyY--))
					posLegalFromR = FALSE;
			}
			else
				posLegalFromR = FALSE;
			cpyNumOfDigits--;
		}
	}
	else // enter from left to right
	{
		if (numOfDigits == 3)
		{
			screen[x][y] = num / 100 + '0';
			screen[x][y + 1] = (num % 100) / 10 + '0';
			screen[x][y + 2] = num % 10 + '0';
		}
		else if (numOfDigits == 2)
		{
			screen[x][y] = num / 10 + '0';
			screen[x][y + 1] = num % 10 + '0';
		}
		else
			screen[x][y] = num + '0';
		replay.enterNumToArr(num, { y,x });
		gotoxy(y--, x);
		cout << num;
		res= TRUE;
	}
	if (res == FALSE)
	{
		if (posLegalFromR)
		{
			cpyNum = num;
			while (cpyNum > 0)
			{
				screen[x][y--] = cpyNum % 10 + '0';
				cpyNum /= 10;
			}
			gotoxy(y + 1, x);
			replay.enterNumToArr(num, { y + 1,x });
			cout << num;
			res = TRUE;
		}
	}
	if (missions.checkIfNumIsCorrect(num))
	{
		if (posLegalFromL || posLegalFromR)
			eatingNumber.enterNumberToArr(x, y + numOfDigits, numOfDigits,num, TRUE);
	}
	return res;
}

BOOL SnakesGame::checkIfPosNearHeadOfSnakes(int x, int y)const
{
	return snakes[0].checkIfPosNearHeadOfSnake(x, y) || snakes[1].checkIfPosNearHeadOfSnake(x, y);
}

BOOL SnakesGame::checkIfPosIsLegal(int x, int y)
{
	return (!checkIfPosIsASnake(x, y) && !checkIfPosNearOtherNumber(x, y) &&
		!checkIfPosNearHeadOfSnakes(x, y) && !checkIfPosIsOtherObjects({ y,x }));
}


BOOL SnakesGame::checkIfPosIsASnake(int x, int y)const
{
	Point pos = { y,x };
	return snakes[0].checkIfNextStepIsTheSnakeItself(pos, 0) || snakes[1].checkIfNextStepIsTheSnakeItself(pos, 0);
}

BOOL SnakesGame::checkIfPosNearOtherNumber(int x, int y)const
{
	char ch;
	if (screen[x][y] != ' ')
		return TRUE;
	if (x > 3)
	{
		ch = screen[x - 1][y];
		if (ch >= '0' && ch <= '9')
			return TRUE;
	}
	if (x < 24)
	{
		ch = screen[x + 1][y];
		if (ch >= '0' && ch <= '9')
			return TRUE;
	}
	if (y > 0)
	{
		ch = screen[x][y - 1];
		if (ch >= '0' && ch <= '9')
			return TRUE;
	}
	if (y < Point::max_x)
	{
		ch = screen[x][y + 1];
		if (ch >= '0' && ch <= '9')
			return TRUE;
	}
	return FALSE;
}

int SnakesGame::getSubMenuChoice(BOOL clearScreen)
{
	int choice;
	if (clearScreen)
	    clrscr();
    printSubMenu();
	
	choice = _getch();
	while (choice <'1' || choice > '7')
	{
		cout << "Enter valid number ";
		choice = _getch();
	}
	if(clearScreen)
	    clrscr();
	return choice;
}

void SnakesGame::printSubMenu()
{
	gotoxy(0, 7);
	cout << "--------------------TheSnakesGame By Or&Oron--------------------" << endl;
	cout << "---------------------------SubMenu-----------------------------" << endl;
	cout << "Please enter your choice by entering a number between 1 to 7 " << endl << endl;
	cout << "(1) Exit the game" << endl;
	cout << "(2) Return to MainMenu" << endl;
	cout << "(3) Continue playing from the last point" << endl;
	cout << "(4) Start current mission all over again" << endl;
	cout << "(5) Start new mission" << endl;
	cout << "(6) Start new game" << endl;
	cout << "(7) Replay mission in end mission" << endl;

}

void SnakesGame::printLastScreenNumbers()
{
	for (int i = Point::min_y; i < MAX_ROWS; i++)
		for (int j = 0; j < MAX_COLS; j++)
		{
			gotoxy(j, i);
			if (screen[i][j] != ' ')
				cout << screen[i][j];
		}
}

void SnakesGame::printSnakes()
{
	for (int i = 0; i < SIZE; i++)
		snakes[i].printSnake();
}

int SnakesGame::randomizeNumber()
{
	int num, range;
	range = rand() % 3;
	switch (range)
	{
	case 0: num = rand() % 26;
		break;
	case 1: num = rand() % 56 + 26;
		break;
	case 2: num = rand() % 88 + 82;
		break;
	}
	return num;
}

void SnakesGame::vanishSnake(Snake& snake)
{
	snake.vanishSnake(*this);
	snake.setLifeOfTheSnake(FALSE);
}


