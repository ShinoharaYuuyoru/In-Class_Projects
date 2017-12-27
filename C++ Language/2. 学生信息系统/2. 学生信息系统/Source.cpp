//Copyright © PiaoQuanyu. All Rights Reserved.

#include "iostream"
#include "string"
using namespace std;

typedef class STUDENT
{
public:
	void Input();
	void Output();

private:
	unsigned int Number;
	string Name;
	double Score;
}Student,*Stud;

void STUDENT::Input()
{
	int NumberTemp;
	string NameTemp;
	double ScoreTemp;

	while (1)
	{
		cin >> NumberTemp >> NameTemp >> ScoreTemp;

		if (NumberTemp < 0)
		{
			cout << "The student Number can't < 0! Please input the information again." << endl;
			continue;
		}
		if (ScoreTemp < 0)
		{
			cout << "The student Score can't < 0! Please input the information again." << endl;
			continue;
		}

		Number = NumberTemp;
		Name = NameTemp;
		Score = ScoreTemp;

		break;
	}

	return;
}
void STUDENT::Output()
{
	cout << Number << "\t" << Name << "\t" << Score << "." << endl;

	return;
}

int main()
{
	int NumberOfStudent = 0;

	cout << "Please input the nunber of Student." << endl;
	cin >> NumberOfStudent;

	Stud StudentList = new Student[NumberOfStudent];

	cout << "Please input Number Name Sore." << endl;

	int Counter = 0;
	for (Counter = 0;Counter < NumberOfStudent;Counter++)
	{
		StudentList[Counter].Input();
	}

	cout << "Now we will output all data. Please check." << endl;
	cout << "Number\tName\tScore" << endl;
	for (Counter = 0;Counter < NumberOfStudent;Counter++)
	{
		StudentList[Counter].Output();
	}

	return 0;
}