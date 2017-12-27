/*Based on PSO*/

#include "iostream"
#include "stdlib.h"
using namespace std;

//unsigned int RANDOMSEED = 0;

int PointNumber = 50;	//Changable. Number of Points. Max is 63.
int IterationTimes = 50000;	//Changable. Iteration Times.

int Job = 0;	//Max is 63.
int Machine = 0;	//Max is 63.
int Time[64][64];
int Operate[64][64];

//This part is for Hyper-Heuristic.
int Sign[64] = { 0 };
int MachineTime[64] = { 0 };
int JobTime[64] = { 0 };

int Points[64][4096];
double StartOmega = 0.7;	//Changable. Usually start from 0.9, and end at 0.4.
double Omega = 0;
double C1 = 0.3, C2 = 0.6;	//Changable. Usually set 0.5.
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

void SPT(int X);
void WSPT(int X);
void TIS(int X);
void SRPT(int X);
void EDD(int X);
void WEDD(int X);
void ChangeTime(int X, int Job);

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
		Sign[X] = 1;
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
	int X = 0;
	int Y = 0;
	for (X = 1;X <= PointNumber;X++)
	{
		for (Y = 1;Y <= Job*Machine;Y++)
		{
			int Temp = 1 + (Random() % 6);	//6 is the number of LLH.

			Points[X][Y] = Temp;
		}
	}

	StartOmega = 0.9;
	C1 = 0.5;
	C2 = 0.5;

	return;
}

int Random()	//Return random number.
{
	//srand(RANDOMSEED);

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

	return;
}

void CalPointTime(int X)
{
	int Counter = 0;
	for (Counter = 1;Counter <= Job*Machine;Counter++)
	{
		if (Points[X][Counter] == 1)
		{
			SPT(X);
		}
		if (Points[X][Counter] == 2)
		{
			WSPT(X);
		}
		if (Points[X][Counter] == 3)
		{
			TIS(X);
		}
		if (Points[X][Counter] == 4)
		{
			SRPT(X);
		}
		if (Points[X][Counter] == 5)
		{
			EDD(X);
		}
		if (Points[X][Counter] == 6)
		{
			WEDD(X);
		}
	}

	//Reset
	int R = 0;
	for (R = 0;R < 64;R++)
	{
		Sign[R] = 1;
		MachineTime[R] = 0;
		JobTime[R] = 0;
	}

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
	for (Counter = 1;Counter <= 6;Counter++)	//6 is the number of LLH.
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
			if (j <= Job*Machine)
			{
				j++;
			}
			else
			{
				break;
			}
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
	for (Counter = 1;Counter <= 6;Counter++)	//6 is the number of LLH.
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
			if (j <= Job*Machine)
			{
				j++;
			}
			else
			{
				break;
			}
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

void SPT(int X)		//LLH 1
{
	int MinTime = 999999999;
	int DoJob = 0;
	int Counter = 1;
	for (Counter = 1;Counter <= Job;Counter++)
	{
		int NowStep = Sign[Counter];

		if (NowStep <= Machine)
		{
			if (Time[Counter][NowStep] < MinTime)
			{
				MinTime = Time[Counter][NowStep];
				DoJob = Counter;
			}
		}
	}

	ChangeTime(X, DoJob);

	Sign[DoJob]++;

	return;
}

void WSPT(int X)	//LLH 2
{
	double MaxWP = -999999999;
	int DoJob = 0;
	int Counter = 1;
	for (Counter = 1;Counter <= Job;Counter++)
	{
		int NowStep = Sign[Counter];

		int Solved = 0;
		int C = 0;
		for (C = 1;C < NowStep;C++)
		{
			Solved = Solved + Time[Counter][C];
		}
		int StartTime = 0;
		if (Solved > MachineTime[Operate[Counter][NowStep]])
		{
			StartTime = Solved;
		}
		else
		{
			StartTime = MachineTime[Operate[Counter][NowStep]];
		}

		int Unsolved = 0;
		for (C = NowStep + 1;C <= Machine;C++)
		{
			Unsolved = Unsolved + Time[Counter][C];
		}

		double WP = ((double)Unsolved - (double)StartTime) / (double)Time[Counter][NowStep];

		if (NowStep <= Machine)
		{
			if (WP > MaxWP)
			{
				MaxWP = WP;
				DoJob = Counter;
			}
		}
	}

	ChangeTime(X, DoJob);

	Sign[DoJob]++;

	return;
}

void TIS(int X)		//LLH 3
{
	int MaxTime = -1;
	int DoJob = 0;
	int Counter = 1;
	for (Counter = 1;Counter <= Job;Counter++)
	{
		int NowStep = Sign[Counter];

		int SolvedTime = 0;
		int C = 0;
		for (C = 1;C < NowStep;C++)
		{
			SolvedTime = SolvedTime + Time[Counter][C];
		}

		if (NowStep <= Machine)
		{
			if (SolvedTime > MaxTime)
			{
				MaxTime = SolvedTime;
				DoJob = Counter;
			}
		}
	}

	ChangeTime(X, DoJob);

	Sign[DoJob]++;

	return;
}

void SRPT(int X)	//LLH 4
{
	int MinTime = 999999999;
	int DoJob = 0;
	int Counter = 1;
	for (Counter = 1;Counter <= Job;Counter++)
	{
		int NowStep = Sign[Counter];

		int SolvedTime = 0;
		int C = 0;
		for (C = NowStep;C <= Machine;C++)
		{
			SolvedTime = SolvedTime + Time[Counter][C];
		}

		if (NowStep <= Machine)
		{
			if (SolvedTime < MinTime)
			{
				MinTime = SolvedTime;
				DoJob = Counter;
			}
		}
	}

	ChangeTime(X, DoJob);

	Sign[DoJob]++;

	return;
}

void EDD(int X)		//LLH 5
{
	int MinTime = 999999999;
	int DoJob = 0;
	int Counter = 1;
	for (Counter = 1;Counter <= Job;Counter++)
	{
		int NowStep = Sign[Counter];

		if (NowStep <= Machine)
		{
			if (JobTime[Counter] < MinTime)
			{
				MinTime = JobTime[Counter];
				DoJob = Counter;
			}
		}
	}

	ChangeTime(X, DoJob);

	Sign[DoJob]++;

	return;
}

void WEDD(int X)	//LLH 6
{
	double MinWD = 999999999;
	int DoJob = 0;
	int Counter = 1;
	for (Counter = 1;Counter <= Job;Counter++)
	{
		int NowStep = Sign[Counter];

		int Solved = 0;
		int C = 0;
		for (C = 1;C < NowStep;C++)
		{
			Solved = Solved + Time[Counter][C];
		}
		int StartTime = 0;
		if (Solved > MachineTime[Operate[Counter][NowStep]])
		{
			StartTime = Solved;
		}
		else
		{
			StartTime = MachineTime[Operate[Counter][NowStep]];
		}

		int Unsolved = 0;
		for (C = NowStep + 1;C <= Machine;C++)
		{
			Unsolved = Unsolved + Time[Counter][C];
		}

		double WD = 0;
		if (JobTime[Counter] == 0)
		{
			WD = (double)Unsolved - (double)StartTime;
		}
		else
		{
			WD = ((double)Unsolved - (double)StartTime) / (double)JobTime[Counter];
		}

		if (NowStep <= Machine)
		{
			if (WD < MinWD)
			{
				MinWD = WD;
				DoJob = Counter;
			}
		}
	}

	ChangeTime(X, DoJob);

	Sign[DoJob]++;

	return;
}

void ChangeTime(int X, int Job)
{
	int TempTime = 0;
	int NowJob = Job;
	int NowStep = Sign[Job];
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

	int MaxTime = MachineTime[1];
	int Y = 0;
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