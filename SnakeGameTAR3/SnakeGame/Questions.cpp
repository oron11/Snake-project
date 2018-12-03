#include "Questions.h"

//Q0 Collect the right missing number: _+x-y=1

const string Q0::getNewQuestion()
{
	question = "Collect the right missing number: _+x-y=1";
	do {
		randNumber(x);
		randNumber(y);
	} while (!checkIfSolutionIsReachable());
    implantRandomNumbersInQuestion();
	return question;
}

void Q0::randNumber(int& x)
{
	x= rand() % (MAX_VALUE_NUMBER - 1) + 1;
}

void Q0::implantRandomNumbersInQuestion()
{
	implantOneNumber('x',x);
	implantOneNumber('y',y);
}


void Q0::implantOneNumber(char c,int x)
{
	size_t i = question.find(c);
	string str = to_string(x);
	question.replace(i, 1, str);
}

BOOL Q0::checkIfSolutionIsReachable()const
{
	for (int i = 0; i < MAX_VALUE_NUMBER; i++)
		if (checkIfNumIsCorrect(i))
			return TRUE;
	return FALSE;
}

BOOL Q0::checkIfNumIsCorrect(int num)const
{
	return (num + x - y == 1);
}

//Q1 Collect prime number that is between [x,y]

const string Q1::getNewQuestion()
{
	question = "Collect prime number that is between [x,y]";
	do {
		randNumber(x);
		randNumber(y);
	} while (!checkIfSolutionIsReachable());

	implantRandomNumbersInQuestion();
	return question;
}

void Q1::randNumber(int& x)
{
	x = rand() % (MAX_VALUE_NUMBER - 1) + 1;
}

void Q1::implantRandomNumbersInQuestion()
{
	implantOneNumber('x',x);
	implantOneNumber('y',y);
}


void Q1::implantOneNumber(char c,int x)
{
	size_t i = question.find(c);
	string str = to_string(x);
	question.replace(i, 1, str);
}

BOOL Q1::checkIfSolutionIsReachable()const
{
	for (int i = 0; i < MAX_VALUE_NUMBER; i++)
		if (checkIfNumIsCorrect(i))
			return TRUE;
	return FALSE;
}

BOOL Q1::checkIfNumIsCorrect(int num)const
{
	if (num == 1 || num == 0 || num < x || num > y)
		return FALSE;
	for (int i = num - 1; i > 1; i--)
			if (num%i == 0)
				return FALSE;
	return TRUE;
}

//Q2 Collect number that is multiple of x and not of y

const string Q2::getNewQuestion()
{
	question = "Collect number that is multiple of x and not of y";
	do {
		randNumber(x);
		randNumber(y);
	} while (!checkIfSolutionIsReachable());

	implantRandomNumbersInQuestion();
	return question;
}

void Q2::randNumber(int& x)
{
	x = rand() % 20 + 1;
}

void Q2::implantRandomNumbersInQuestion()
{
	implantOneNumber('x',x);
	implantOneNumber('y',y);
}

void Q2::implantOneNumber(char c,int x)
{
	size_t i = question.find(c);
	string str = to_string(x);
	question.replace(i, 1, str);
}

BOOL Q2::checkIfSolutionIsReachable()const
{
	for (int i = 0; i < MAX_VALUE_NUMBER; i++)
		if (checkIfNumIsCorrect(i))
			return TRUE;
	return FALSE;
}

BOOL Q2::checkIfNumIsCorrect(int num)const
{
	return (num %x == 0 && num%y != 0);
}

//Q3 Collect number that his unit digit is x

const string Q3::getNewQuestion()
{
	question = "Collect number that his unit digit is x";
	do {
		randNumber();
	} while (!checkIfSolutionIsReachable());

	implantRandomNumbersInQuestion();
	return question;
}

void Q3::randNumber()
{
	x = rand() % 10;
}

void Q3::implantRandomNumbersInQuestion()
{
	implantOneNumber('x');
}


void Q3::implantOneNumber(char c)
{
	size_t i = question.find(c);
	string str = to_string(x);
	question.replace(i, 1, str);
}

BOOL Q3::checkIfSolutionIsReachable()const
{
	for (int i = 0; i < MAX_VALUE_NUMBER; i++)
		if (checkIfNumIsCorrect(i))
			return TRUE;
	return FALSE;
}

BOOL Q3::checkIfNumIsCorrect(int num)const
{
	return (num % 10 == x);
}

//Q4 Collect the result of x+y

const string Q4::getNewQuestion()
{
	question = "Collect the result of x+y";
	do {
		randNumber(x);
		randNumber(y);
	} while (!checkIfSolutionIsReachable());

	implantRandomNumbersInQuestion();
	return question;
}

void Q4::randNumber(int& x)
{
	x = rand() % 80 + 1;
}

void Q4::implantRandomNumbersInQuestion()
{
	implantOneNumber('x',x);
	implantOneNumber('y',y);
}

void Q4::implantOneNumber(char c,int x)
{
	size_t i = question.find(c);
	string str = to_string(x);
	question.replace(i, 1, str);
}

BOOL Q4::checkIfSolutionIsReachable()const
{
	for (int i = 0; i < MAX_VALUE_NUMBER; i++)
		if (checkIfNumIsCorrect(i))
			return TRUE;
	return FALSE;
}

BOOL Q4::checkIfNumIsCorrect(int num)const
{
	return (x+y==num);
}

//Q5 Collect number that the result x/number is the number 

const string Q5::getNewQuestion()
{
	question = "Collect number that the result x/number is the number";
	do {
		randNumber();
	} while (!checkIfSolutionIsReachable());

	implantRandomNumbersInQuestion();
	return question;
}

void Q5::randNumber()
{
	x = rand() % 20 + 1;
}

void Q5::implantRandomNumbersInQuestion()
{
	implantOneNumber('x');
}


void Q5::implantOneNumber(char c)
{
	size_t i = question.find(c);
	string str = to_string(x);
	question.replace(i, 1, str);
}

BOOL Q5::checkIfSolutionIsReachable()const
{
	for (int i = 0; i < MAX_VALUE_NUMBER; i++)
		if (checkIfNumIsCorrect(i))
			return TRUE;
	return FALSE;
}

BOOL Q5::checkIfNumIsCorrect(int num)const
{
	if (num == 0)
		return FALSE;
	return(x / num == num);
}


//Q6 Collect number that has x odd digits and y even digits

const string Q6::getNewQuestion()
{
	question = "Collect number that has x odd digits and y even digits";
	do {
		randNumber(x);
		randNumber(y);
	} while (!checkIfSolutionIsReachable());

	implantRandomNumbersInQuestion();
	return question;
}

void Q6::randNumber(int& x)
{
	x = rand() % 3;
}

void Q6::implantRandomNumbersInQuestion()
{
	implantOneNumber('x',x);
	implantOneNumber('y',y);
}

void Q6::implantOneNumber(char c,int x)
{
	size_t i = question.find(c);
	string str = to_string(x);
	question.replace(i, 1, str);
}

BOOL Q6::checkIfSolutionIsReachable()const
{
	for (int i = 0; i < MAX_VALUE_NUMBER; i++)
		if (checkIfNumIsCorrect(i))
			return TRUE;
	return FALSE;
}

BOOL Q6::checkIfNumIsCorrect(int num)const
{
	int numOfDigits = getNumOfDigits(num);
	int countOddDigits = 0, countEvenDigits = 0, digit;
	while (numOfDigits > 0)
	{
		digit = num % 10;
		(digit % 2 == 0) ? countEvenDigits++ : countOddDigits++;
		num /= 10;
		numOfDigits--;
	}
	return (countOddDigits == x && countEvenDigits == y);
}