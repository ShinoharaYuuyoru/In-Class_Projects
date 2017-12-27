#include "iostream"
#include "stdlib.h"
using namespace std;

int PointNumber = 32;	//Changable. Number of Points. Max is 63.
int IterationTimes = 500000;	//Changable. Iteration Times.

int Job = 0;	//Max is 63.
int Machine = 0;	//Max is 63.
int Time[64][64];
int Operate[64][64];

int Points[64][4096];
double StartOmega = 0.9;	//Changable. Usually start from 0.9, and end at 0.4.
double Omega = 0;
double C1 = 0.5, C2 = 0.5;	//Changable. Usually set 0.5.
double Rau = 0;
int pBest[64][4096];
int gBest[4096];

void Reset();
void Input();
void Initialize();
int Random();
void Solve();
void CalPointTime(int X);
void NewPoint(int X);
void DoGinStep2(int X);
void DoGinStep3(int X);
void ANS();

int main()
{
	Reset();

	Input();

	Initialize();

	Solve();

	ANS();

	return 0;
}

void Reset()
{
	int Job = 0;
	int Machine = 0;

	int X = 0;
	int Y = 0;
	for (X = 0;X < 64;X++)
	{
		for (Y = 0;Y < 64;Y++)
		{
			Time[X][Y] = 0;
			Operate[X][Y] = 0;
		}
		gBest[X] = 0;
	}

	return;
}

void Input()
{
	cout << "Please input the number of Jobs." << endl;
	cin >> Job;
	cout << "Please input the nunber of Machines." << endl;
	cin >> Machine;

	cout << "Please input the time." << endl;
	int X = 0;
	int Y = 0;
	for (X = 1; X <= Job;X++)
	{
		for (Y = 1;Y <= Machine;Y++)
		{
			cin >> Time[X][Y];
		}
	}

	cout << "Please input the step." << endl;
	for (X = 1;X <= Job;X++)
	{
		for (Y = 1;Y <= Machine;Y++)
		{
			cin >> Operate[X][Y];
		}
	}

	return;
}

void Initialize()
{
	int Sign[64] = { 0 };
	int X = 0;
	int Y = 0;
	for (X = 1;X <= PointNumber;X++)
	{
		for (Y = 1;Y <= Job*Machine;)
		{
			int Temp = 1 + (Random() % Job);
			if (Sign[Temp] < Machine)
			{
				Points[X][Y] = Temp;
				Sign[Temp]++;
				Y++;
			}
		}

		int R = 0;
		for (R = 0;R <= Job;R++)
		{
			Sign[R] = 0;
		}
	}

	StartOmega = 0.9;
	C1 = 0.5;
	C2 = 0.5;

	return;
}

int Random()	//Return random number.
{
	return rand();
}

void Solve()
{
	Omega = StartOmega;

	int Counter = 0;
	for (Counter = 1;Counter <= IterationTimes;Counter++)
	{
		if (Counter == 1)
		{
			int X = 0;
			int Y = 0;
			for (X = 1;X <= PointNumber;X++)
			{
				for (Y = 1;Y <= Job*Machine;Y++)
				{
					pBest[X][Y] = Points[X][Y];
				}
				CalPointTime(X);
				pBest[X][0] = Points[X][0];
				if (gBest[0] == 0)
				{
					int R = 0;
					for (R = 0;R <= Job*Machine;R++)
					{
						gBest[R] = pBest[X][R];
					}
				}
				else
				{
					if (pBest[X][0] < gBest[0])
					{
						int Y = 0;
						for (Y = 0;Y <= Job*Machine;Y++)
						{
							gBest[Y] = pBest[X][Y];
						}
					}
				}
			}
		}
		else
		{
			int X = 0;
			for (X = 1;X <= PointNumber;X++)
			{
				NewPoint(X);
				CalPointTime(X);
				if (Points[X][0] < pBest[X][0])
				{
					int Y = 0;
					for (Y = 0;Y <= Job*Machine;Y++)
					{
						pBest[X][Y] = Points[X][Y];
					}
				}
				if (pBest[X][0] < gBest[0])
				{
					int Y = 0;
					for (Y = 0;Y <= Job*Machine;Y++)
					{
						gBest[Y] = pBest[X][Y];
					}
				}

				Omega = StartOmega - ((double)Counter / (double)IterationTimes)*0.5;
			}
		}
	}
}

void CalPointTime(int X)
{
	int ThisStep[64] = { 0 };
	int RTS = 0;	//Reset ThisStep.
	for (RTS = 0;RTS < 64;RTS++)
	{
		ThisStep[RTS] = 1;
	}
	int MachineTime[64] = { 0 };
	int JobTime[64] = { 0 };

	int Y = 0;
	for (Y = 1;Y <= Job*Machine;Y++)
	{
		int TempTime = 0;
		int NowJob = Points[X][Y];
		int NowStep = ThisStep[NowJob];
		int NowMachine = Operate[NowJob][NowStep];

		TempTime = JobTime[NowJob];

		if (TempTime > MachineTime[NowMachine])
		{
			MachineTime[NowMachine] = TempTime + Time[NowJob][NowStep];
		}
		else
		{
			MachineTime[NowMachine] = MachineTime[NowMachine] + Time[NowJob][NowStep];
		}

		JobTime[NowJob] = MachineTime[NowMachine];
		ThisStep[NowJob]++;
	}

	int MaxTime = MachineTime[1];
	for (Y = 2;Y <= Machine;Y++)
	{
		if (MachineTime[Y] > MaxTime)
		{
			MaxTime = MachineTime[Y];
		}
	}

	Points[X][0] = MaxTime;

	return;
}

void NewPoint(int X)
{
	//Step 1
	Rau = Random() / double(RAND_MAX);
	if (Rau < Omega)
	{
		int a = 1 + Random() % (Job*Machine);
		int b = 1 + Random() % (Job*Machine);

		int T = 0;
		T = Points[X][a];
		Points[X][a] = Points[X][b];
		Points[X][b] = T;
	}

	//Step 2
	Rau = Random() / double(RAND_MAX);
	if (Rau < C1)
	{
		DoGinStep2(X);	//Do function g() for Step 2.
	}

	//Step 3
	Rau = Random() / double(RAND_MAX);
	if (Rau < C2)
	{
		DoGinStep3(X);	//Do function g() for Step 3.
	}
}

void DoGinStep2(int X)
{
	int S1[64] = { 0 };
	int S1Num = 1;
	int S2[64] = { 0 };
	int S2Num = 1;
	int Counter = 0;
	for (Counter = 1;Counter <= Job;Counter++)
	{
		int Div = Random() % 2;
		if (Div == 0)
		{
			if (S1Num < Job)
			{
				S1[S1Num] = Counter;
				S1Num++;
			}
			else
			{
				S2[S2Num] = Counter;
				S2Num++;
			}
		}
		else
		{
			S2[S2Num] = Counter;
			S2Num++;
		}
	}
	S1Num--;
	S2Num--;

	int Y[4096] = { 0 };
	int RY = 0;
	for (RY = 1;RY <= Job*Machine;RY++)
	{
		Y[RY] = Points[X][RY];
	}
	int l = 1;
	int j = 1;
	int SCounter = 0;
	for (;;)
	{
		for (SCounter = 1;SCounter <= S1Num;SCounter++)
		{
			if (Points[X][j] == S1[SCounter])
			{
				Y[l] = Points[X][j];
				l++;

				break;
			}
		}
		for (SCounter = 1;SCounter <= S2Num;SCounter++)
		{
			if (pBest[X][j] == S2[SCounter])
			{
				Y[l] = pBest[X][j];
				l++;

				break;
			}
		}

		if (l <= Job*Machine)
		{
			j++;
			continue;
		}
		else
		{
			break;
		}
	}

	int Copy = 0;
	for (Copy = 1;Copy <= Job*Machine;Copy++)
	{
		Points[X][Copy] = Y[Copy];
	}

	return;
}

void DoGinStep3(int X)
{
	int S1[64] = { 0 };
	int S1Num = 1;
	int S2[64] = { 0 };
	int S2Num = 1;
	int Counter = 0;
	for (Counter = 1;Counter <= Job;Counter++)
	{
		int Div = Random() % 2;
		if (Div == 0)
		{
			if (S1Num < Job)
			{
				S1[S1Num] = Counter;
				S1Num++;
			}
			else
			{
				S2[S2Num] = Counter;
				S2Num++;
			}
		}
		else
		{
			S2[S2Num] = Counter;
			S2Num++;
		}
	}
	S1Num--;
	S2Num--;

	int Y[4096] = { 0 };
	int RY = 0;
	for (RY = 1;RY <= Job*Machine;RY++)
	{
		Y[RY] = Points[X][RY];
	}
	int l = 1;
	int j = 1;
	int SCounter = 0;
	for (;;)
	{
		for (SCounter = 1;SCounter <= S1Num;SCounter++)
		{
			if (Points[X][j] == S1[SCounter])
			{
				Y[l] = Points[X][j];
				l++;

				break;
			}
		}
		for (SCounter = 1;SCounter <= S2Num;SCounter++)
		{
			if (gBest[j] == S2[SCounter])
			{
				Y[l] = gBest[j];
				l++;

				break;
			}
		}
		
		if (l <= Job*Machine)
		{
			j++;
			continue;
		}
		else
		{
			break;
		}
	}

	int Copy = 0;
	for (Copy = 1;Copy <= Job*Machine;Copy++)
	{
		Points[X][Copy] = Y[Copy];
	}

	return;
}

void ANS()
{
	cout << "Need " << gBest[0] << " hour(s)." << endl;

	return;
}