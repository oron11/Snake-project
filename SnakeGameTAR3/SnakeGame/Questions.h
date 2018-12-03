#ifndef _QUESTIONS_
#define _QUESTIONS_

#include "io_utils.h"

class Questions
{
public:
	enum { MAX_VALUE_NUMBER = 170 };

	virtual const string getNewQuestion()=0;
	virtual const string getCurrentQuestion()const = 0;
	virtual BOOL checkIfNumIsCorrect(int num)const = 0;

	virtual ~Questions(){}

};

class Q0 :public Questions
{
	string question;
	int x, y;
public:
	virtual const string getNewQuestion()override;
	virtual const string getCurrentQuestion()const override { return question; }
	void randNumber(int & x);
	void implantRandomNumbersInQuestion();
	void implantOneNumber(char c,int x);
	BOOL checkIfSolutionIsReachable()const;
	virtual BOOL checkIfNumIsCorrect(int num)const override;
};

class Q1 :public Questions {
	string question;
	int x, y;
public:
	virtual const string getNewQuestion()override;
	virtual const string getCurrentQuestion()const override { return question; }
	void randNumber(int & x);
	void implantRandomNumbersInQuestion();
	void implantOneNumber(char c, int x);
	BOOL checkIfSolutionIsReachable()const;
	virtual BOOL checkIfNumIsCorrect(int num)const override;
};

class Q2 :public Questions {
	string question;
	int x, y;
public:
	virtual const string getNewQuestion()override;
	virtual const string getCurrentQuestion()const override { return question; }
	void randNumber(int & x);
	void implantRandomNumbersInQuestion();
	void implantOneNumber(char c, int x);
	BOOL checkIfSolutionIsReachable()const;
	virtual BOOL checkIfNumIsCorrect(int num)const override;
};

class Q3 :public Questions {
	string question;
	int x;
public:
	virtual const string getNewQuestion()override;
	virtual const string getCurrentQuestion()const override { return question; }
	void randNumber();
	void implantRandomNumbersInQuestion();
	void implantOneNumber(char c);
	BOOL checkIfSolutionIsReachable()const;
	virtual BOOL checkIfNumIsCorrect(int num)const override;
};

class Q4 :public Questions {
	string question;
	int x, y;
public:
	virtual const string getNewQuestion()override;
	virtual const string getCurrentQuestion()const override { return question; }
	void randNumber(int &x);
	void implantRandomNumbersInQuestion();
	void implantOneNumber(char c,int x);
	BOOL checkIfSolutionIsReachable()const;
	virtual BOOL checkIfNumIsCorrect(int num)const override;
};

class Q5 :public Questions {
	string question;
	int x;
public:
	virtual const string getNewQuestion()override;
	virtual const string getCurrentQuestion()const override { return question; }
	void randNumber();
	void implantRandomNumbersInQuestion();
	void implantOneNumber(char c);
	BOOL checkIfSolutionIsReachable()const;
	virtual BOOL checkIfNumIsCorrect(int num)const override;
};

class Q6 :public Questions {
	string question;
	int x, y;
public:
	virtual const string getNewQuestion()override;
	virtual const string getCurrentQuestion()const override { return question; }
	void randNumber(int & x);
	void implantRandomNumbersInQuestion();
	void implantOneNumber(char c,int x);
	BOOL checkIfSolutionIsReachable()const;
	virtual BOOL checkIfNumIsCorrect(int num)const override;
};


#endif