#define MAX 1000
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

int firstMatrixM = 0;
int firstMatrixN = 0;
int secondMatrixM = 0;
int secondMatrixN = 0;

vector<vector<int> > firstMatrix(firstMatrixM, vector<int>(firstMatrixN));
vector<vector<int> > secondMatrix(secondMatrixM, vector<int>(secondMatrixN));

void buildMatrix();
void Output();

int main()
{
	cout << "Please input the first matrix's M and N." << endl;
	cin >> firstMatrixM >> firstMatrixN;
	cout << "Please input the second matrix's M and N." << endl;
	cin >> secondMatrixM >> secondMatrixN;

	buildMatrix();

	Output();
}

void buildMatrix()
{
	int temp0 = 0;
	srand((unsigned)time(NULL));

	firstMatrix.resize(firstMatrixM);
	for (temp0 = 0;temp0 < firstMatrixM;temp0++)
	{
		firstMatrix[temp0].resize(firstMatrixN);
	}
	secondMatrix.resize(secondMatrixM);
	for (temp0 = 0;temp0 < secondMatrixM;temp0++)
	{
		secondMatrix[temp0].resize(secondMatrixN);
	}

	int temp1 = 0;
	for (temp0 = 0;temp0 < firstMatrixM;temp0++)
	{
		for (temp1 = 0;temp1 < firstMatrixN;temp1++)
		{
			firstMatrix[temp0][temp1] = rand() % MAX;
		}
	}

	for (temp0 = 0;temp0 < secondMatrixM;temp0++)
	{
		for (temp1 = 0;temp1 < secondMatrixN;temp1++)
		{
			secondMatrix[temp0][temp1] = rand() % MAX;
		}
	}

	return;
}

void Output()
{
	ofstream matrixOut("matrixOut.txt");
	int temp0 = 0;
	int temp1 = 0;

	matrixOut << firstMatrixM << " " << firstMatrixN << endl;
	matrixOut << secondMatrixM << " " << secondMatrixN << endl;

	//cout << "The first matrix is:" << endl;

	//for (temp0 = 0;temp0 < firstMatrixM;temp0++)
	//{
	//	for (temp1 = 0;temp1 < firstMatrixN;temp1++)
	//	{
	//		cout << firstMatrix[temp0][temp1];
	//		if (temp1 == firstMatrixN - 1)
	//		{
	//			cout << endl;
	//		}
	//		else
	//		{
	//			cout << " ";
	//		}
	//	}
	//}

	for (temp0 = 0;temp0 < firstMatrixM;temp0++)
	{
		for (temp1 = 0;temp1 < firstMatrixN;temp1++)
		{
			matrixOut << firstMatrix[temp0][temp1];
			if (temp1 == firstMatrixN - 1)
			{
				matrixOut << endl;
			}
			else
			{
				matrixOut << " ";
			}
		}
	}
	matrixOut << endl;

	//cout << "The second matrix is:" << endl;

	//for (temp0 = 0;temp0 < secondMatrixM;temp0++)
	//{
	//	for (temp1 = 0;temp1 < secondMatrixN;temp1++)
	//	{
	//		cout << secondMatrix[temp0][temp1];
	//		if (temp1 == secondMatrixN - 1)
	//		{
	//			cout << endl;
	//		}
	//		else
	//		{
	//			cout << " ";
	//		}
	//	}
	//}

	for (temp0 = 0;temp0 < secondMatrixM;temp0++)
	{
		for (temp1 = 0;temp1 < secondMatrixN;temp1++)
		{
			matrixOut << secondMatrix[temp0][temp1];
			if (temp1 == secondMatrixN - 1)
			{
				matrixOut << endl;
			}
			else
			{
				matrixOut << " ";
			}
		}
	}
	matrixOut << endl;
}