#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Color.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Direction.h"
#include <process.h>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include "Screen.h"

using namespace std;

void setTextColor(Color);
void ShowConsoleCursor(bool showFlag);
int getNumOfDigits(int num);
void playStartMusic();
void playTriumphMusic();

#endif