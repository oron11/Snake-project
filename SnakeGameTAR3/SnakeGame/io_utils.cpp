#include "io_utils.h"
#include "gotoxy.h"

using namespace std;

void setTextColor(Color colorToSet) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}
int getNumOfDigits(int num)
{
	int numOfDigits = 0;

	if (num != 0)
	{
		while (num > 0)
		{
			num /= 10;
			numOfDigits++;
		}
	}
	else
		numOfDigits = 1;
	return numOfDigits;
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void playStartMusic()
{
	Beep(330, 100); Sleep(125);
	Beep(330, 100); Sleep(125);
	Beep(330, 100); Sleep(125);
	Beep(262, 100); Sleep(125);
	Beep(330, 100); Sleep(100);
	Beep(392, 100); Sleep(100);
	Beep(196, 100); Sleep(100);
	Beep(262, 300); Sleep(125);
	Beep(196, 300); Sleep(125);
	Beep(164, 300); Sleep(125);
	Beep(220, 300); Sleep(125);
	Beep(246, 200); Sleep(125);
}

void playTriumphMusic()
{
	Beep(698, 100); Sleep(125);
	Beep(932, 100); Sleep(575);
	Beep(932, 100); Sleep(125);
	Beep(932, 100); Sleep(125);
	Beep(932, 100); Sleep(125);
	Beep(698, 100); Sleep(125);
	Beep(932, 100); Sleep(575);
	Beep(932, 100); Sleep(125);
	Beep(932, 100); Sleep(125);
	Beep(932, 100); Sleep(125);
}


