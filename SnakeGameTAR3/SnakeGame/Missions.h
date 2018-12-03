#ifndef _MISSION_H_
#define _MISSION_H_

#include "Questions.h"

class Mission
{
	vector <Questions*> q;
	size_t currQuestion;
	Q0 q0; Q1 q1; Q2 q2; Q3 q3; Q4 q4; Q5 q5; Q6 q6;
	vector<string> quests;
public:
	Mission();
	void readMissionsFromFile();
	void createQuestsContainer();
	size_t getRandomNumberForQuestion();
	BOOL checkIfNumIsCorrect(int num)const {return q[currQuestion]->checkIfNumIsCorrect(num);}
	const string getCurrentQuestion()const { return q[currQuestion]->getCurrentQuestion(); }
	const string getQuestion();
};


#endif