#include "iostream"
#include "cstring"
using namespace std;

double Alpha = 1.0;//This is the most important parameter.

int Machine = 0;
int Model = 0;
int Time[1024][1024];
int Step[1024][1024];
int Pointer[1024];
int MachineTime[1024];

void Input();
void Reset();
void Solve();
int EndCheck();
int GetMaxPri();
int CalH(int M);
int CalF(int M);
void ANS();

int main()
{
	Reset();

	Input();

	Solve();

	ANS();
}

void Reset()
{
	memset(Time, 0, sizeof(Time));
	memset(Step, 0, sizeof(Step));
	int R = 0;
	for (R = 0;R < 1024;R++)
	{
		Pointer[R] = 1;
		MachineTime[R] = 0;
	}

	return;
}

void Input()
{
	cout << "Please input the number of Machine:" << endl;
	cin >> Machine;
	cout << "Please input the number of Model:" << endl;
	cin >> Model;

	cout << "Please input the Time of working each Model:" << endl;
	int MachineC = 0;
	int ModelC = 0;
	for (ModelC = 1;ModelC <= Model;ModelC++)
	{
		for (MachineC = 1;MachineC <= Machine;MachineC++)
		{
			cin >> Time[ModelC][MachineC];
		}
	}
	cout << "Please input the Step of working each Model:" << endl;
	for (ModelC = 1;ModelC <= Model;ModelC++)
	{
		for (MachineC = 1;MachineC <= Machine;MachineC++)
		{
			cin >> Step[ModelC][MachineC];
		}
	}

	return;
}

void Solve()
{
	int WorkMod = 0;
	while (EndCheck())
	{
		WorkMod = GetMaxPri();

		if (MachineTime[Step[WorkMod][Pointer[WorkMod]]] > CalF(WorkMod))
		{
			MachineTime[Step[WorkMod][Pointer[WorkMod]]] += Time[WorkMod][Pointer[WorkMod]];
		}
		else
		{
			MachineTime[Step[WorkMod][Pointer[WorkMod]]] = CalF(WorkMod) + Time[WorkMod][Pointer[WorkMod]];
		}

		Pointer[WorkMod]++;
	}

	return;
}

int EndCheck()
{
	int X = 0;
	for (X = 1;X <= Model;X++)
	{
		if (Pointer[X] <= Machine)
		{
			return 1;
		}
	}

	return 0;
}

int GetMaxPri()
{
	int MaxPriMod = 0;
	int MaxPri = -999999999;
	double Temp;
	int Scan = 0;
	for (Scan = 1;Scan <= Model;Scan++)
	{
		if (Pointer[Scan] > Machine)
		{
			continue;
		}
		else
		{
			Temp = (double)CalH(Scan) - (double)Alpha*CalF(Scan);
			if (Temp > MaxPri)
			{
				MaxPri = Temp;
				MaxPriMod = Scan;
			}
		}
	}

	return MaxPriMod;
}

int CalH(int M)
{
	int T = 0;
	int ScanMac = 0;

	for (ScanMac = Pointer[M] + 1;ScanMac <= Machine;ScanMac++)
	{
		T = T + Time[M][ScanMac];
	}

	return T;
}

int CalF(int M)
{
	int Did = 0;
	int Check = 0;
	for (Check = Pointer[M] - 1;Check >= 1;Check--)
	{
		Did = Did + Time[M][Check];
	}

	return Did;
}

void ANS()
{
	int NeedTime = 0;

	int S = 0;
	for (S = 1;S <= Machine;S++)
	{
		if (MachineTime[S] > NeedTime)
		{
			NeedTime = MachineTime[S];
		}
	}

	cout << "Need " << NeedTime << " hour(s)." << endl;

	return;
}