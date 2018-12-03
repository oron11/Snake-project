#include "Missions.h"

Mission::Mission()
{
	readMissionsFromFile();
	createQuestsContainer();
	currQuestion = 0;
}

void Mission::readMissionsFromFile()
{
	string str;
	ifstream fileQuests;
	fileQuests.open("Questions.txt", ios_base::in);

	while (!fileQuests.eof())
	{
		getline(fileQuests, str);
		if(str!="")
		  quests.push_back(str);
	}

	fileQuests.close();
}

void Mission::createQuestsContainer()
{
	q.resize(quests.size());
	int j = 0;
	for (int i = 0; i<quests.size(); i++)
	{
		if (quests[i].find("missing") != string::npos)
			q[j++] = &q0;
		else if (quests[i].find("between") != string::npos)
			q[j++] = &q1;
		else if(quests[i].find("multiple") != string::npos)
			q[j++] = &q2;
		else if (quests[i].find("unit") != string::npos)
			q[j++] = &q3;
		else if (quests[i].find("x+y") != string::npos)
			q[j++] = &q4;
		else if (quests[i].find("x/number") != string::npos)
			q[j++] = &q5;
		else if (quests[i].find("odd") != string::npos)
			q[j++] = &q6;
	}
}

const string Mission::getQuestion()
{
	int num = getRandomNumberForQuestion();
	return q[num]->getNewQuestion();
}

size_t Mission::getRandomNumberForQuestion()
{
	return currQuestion=rand() % (quests.size());
}
