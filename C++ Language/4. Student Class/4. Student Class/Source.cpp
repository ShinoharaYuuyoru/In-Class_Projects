#include <iostream>
#include <string>
using namespace std;

class Student
{
	static int TotalNumber;
	static double TotalScore;

private:
	string Name;
	unsigned int Number;
	double Score;

public:
	static double Average();
	void Set();
	void Student::Show();
	Student()
	{
		Name[0] = '\0';
		Number = 0;
		Score = 0;
	}
	Student(const Student &Other);
	Student & operator = (const Student &Other);
};

int Student::TotalNumber=0;
double Student::TotalScore =0;

double Student::Average()
{
	return TotalScore / TotalNumber;
	
}

void Student::Set()
{
	cout << "Please input student's name." << endl;
	cin >> Name;
	cout << "Please input student's number." << endl;
	cin >> Number;
	cout << "Please input student's score." << endl;
	cin >> Score;

	TotalNumber++;
	TotalScore = TotalScore + Score;

	return;
}

void Student::Show()
{
	cout << "Name: " << Name << endl;
	cout << "Number: " << Number << endl;
	cout << "Score: " << Score << endl;

	return;
}

Student::Student(const Student &Other)
{
	Name = Other.Name;
	Number = Other.Number;
	Score = Other.Score;
}

Student & Student::operator = (const Student &Other)
{
	Name = Other.Name;
	Number = Other.Number;
	Score = Other.Score;

	return *this;
}

int main()
{
	Student S1;
	Student S2;
	Student S3;
	S1.Set();
	S2.Set();
	S3.Set();
	S1.Show();
	S2.Show();
	S3.Show();
	S3.Average();

	Student Copy1(S1);
	Student Copy2;
	Copy2 = S2;
	
	cout << "We will output the copy of S1 and S2" << endl;
	Copy1.Show();
	Copy2.Show();

	return 0;
}