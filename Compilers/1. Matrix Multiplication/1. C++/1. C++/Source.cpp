#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

double startTime = 0;
double endTime = 0;
double useTime = 0;
int firstMatrixM = 0;
int firstMatrixN = 0;
int secondMatrixM = 0;
int secondMatrixN = 0;

vector<vector<int> > firstMatrix(firstMatrixM, vector<int>(firstMatrixN));
vector<vector<int> > secondMatrix(secondMatrixM, vector<int>(secondMatrixN));
vector<vector<int> > resultMatrix(firstMatrixM, vector<int>(secondMatrixN));

int LeagalCheck();
void Init();
void Calc();
void Output();

int main()
{
	cout << "Please input M and N of the first matrix." << endl;
	cin >> firstMatrixM >> firstMatrixN;
	cout << "Please input M and N of the second matrix." << endl;
	cin >> secondMatrixM >> secondMatrixN;

	if (LeagalCheck() == 1)
	{
		return 0;
	}
	else
	{
		Init();
	}

	startTime = clock();
	Calc();
	endTime = clock();
	useTime = endTime - startTime;

	Output();

	//cout << "Calculation used " << useTime << " ms." << endl;
}

int LeagalCheck()
{
	if (firstMatrixM == 0 || firstMatrixN == 0 || secondMatrixM == 0 || secondMatrixN == 0)
	{
		return 1;
	}
	else
	{
		if (firstMatrixN != secondMatrixM)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

void Init()
{
	int temp0 = 0;

	firstMatrix.resize(firstMatrixM);
	for (temp0 = 0;temp0 < firstMatrixM;temp0++)
	{
		firstMatrix.at(temp0).resize(firstMatrixN);
	}
	secondMatrix.resize(secondMatrixM);
	for (temp0 = 0;temp0 < secondMatrixM;temp0++)
	{
		secondMatrix.at(temp0).resize(secondMatrixN);
	}
	resultMatrix.resize(firstMatrixM);
	for (temp0 = 0;temp0 < firstMatrixM;temp0++)
	{
		resultMatrix.at(temp0).resize(secondMatrixN);
	}

	cout << "Please input the first matrix. End with a blank Line." << endl;
	int temp1 = 0;
	int temp2 = 0;
	for (temp0 = 0;temp0 < firstMatrixM;temp0++)
	{
		for (temp1 = 0;temp1 < firstMatrixN;temp1++)
		{
			cin >> temp2;
			firstMatrix[temp0][temp1] = temp2;
		}
	}

	cout << "Please input the second matrix. End with a blank Line." << endl;
	for (temp0 = 0;temp0 < secondMatrixM;temp0++)
	{
		for (temp1 = 0;temp1 < secondMatrixN;temp1++)
		{
			cin >> temp2;
			secondMatrix[temp0][temp1] = temp2;
		}
	}

	return;
}

void Calc()
{
	int temp0 = 0;
	int temp1 = 0;
	int temp2 = 0;
	int temp3 = 0;

	for (temp0 = 0;temp0 < firstMatrixM;temp0++)
	{
		for (temp1 = 0;temp1 < secondMatrixN;temp1++)
		{
			for (temp2 = 0;temp2 < firstMatrixN;temp2++)
			{
				temp3 += firstMatrix[temp0][temp2] * secondMatrix[temp2][temp1];
			}

			resultMatrix[temp0][temp1] = temp3;
			temp3 = 0;
		}
	}

	return;
}

void Output()
{
	int temp0 = 0;
	int temp1 = 0;

	cout << "The result matrix after multiplication is:" << endl;
	for (temp0 = 0;temp0 < firstMatrixM;temp0++)
	{
		for (temp1 = 0;temp1 < secondMatrixN;temp1++)
		{
			cout << resultMatrix[temp0][temp1];
			if (temp1 == secondMatrixN - 1)
			{
				cout << endl;
			}
			else
			{
				cout << " ";
			}
		}
	}

	cout << "Calculation used " << useTime << " ms." << endl;

	return;
}