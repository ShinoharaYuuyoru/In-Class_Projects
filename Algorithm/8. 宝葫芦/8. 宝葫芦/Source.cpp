#include "iostream"
#include "queue"

using namespace std;

int N, M;
int K;
int MyX, MyY;
int ProX, ProY;
int MinStep = -1;
char Map[128][128];
int KPoint[128][128];
int InQueue[10005][4];
int InQueueCounter;
queue<int*> Q;
int StopPoint[4];

void Reset();
void FourDimension(int X, int Y, int F, int S);
int LawCheck(int X, int Y, int F, int S);
void AddDimension(int X, int Y, int F, int S);
void PushInQueue(int X, int Y, int F, int S);
void BFS();
void Jump(int X, int Y, int F, int S);

int main()
{
	while (scanf("%d%d", &N, &M) != EOF)
	{
		Reset();
		InQueueCounter = 0;

		cin >> K;
		int KCounter = 1;
		int XTemp, YTemp, JTemp;
		for (KCounter = 1;KCounter <= K;KCounter++)
		{
			cin >> XTemp >> YTemp >> JTemp;
			Map[XTemp][YTemp] = '%';
			KPoint[XTemp][YTemp] = JTemp;
		}

		cin >> MyX >> MyY;
		PushInQueue(MyX, MyY, 0, 0);

		cin >> ProX >> ProY;
		Map[ProX][ProY] = '!';

		BFS();

		if (MinStep == -1)
		{
			cout << "impossible" << endl;
		}
		else
		{
			cout << MinStep << endl;
		}
	}
	
	return 0;
}

void Reset()
{
	int X, Y;
	for (X = 1;X <= N;X++)
	{
		for (Y = 1;Y <= M;Y++)
		{
			Map[X][Y] = '.';
			KPoint[X][Y] = 0;
		}
	}
	for (;Q.empty() != 1;Q.pop());
	MinStep = -1;
	InQueueCounter = 0;
}

void FourDimension(int X, int Y, int F, int S)	//F(For):1UP 2Down 3Left 4Right
{
	AddDimension(X - 1, Y, 1, S + 1);
	AddDimension(X + 1, Y, 2, S + 1);
	AddDimension(X, Y - 1, 3, S + 1);
	AddDimension(X, Y + 1, 4, S + 1);

	return;
}

int LawCheck(int X, int Y, int F, int S)
{
	if (X<1 || X>N || Y<1 || Y>M)
	{
		return 0;
	}
	else
	{
		if (Map[X][Y] == '%')	//Need Jump.
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
}

void AddDimension(int X, int Y, int F, int S)
{
	int LCSign = LawCheck(X, Y, F, S);

	if (LCSign == 0)
	{
		return;
	}
	else
	{
		if (LCSign == 1)
		{
			PushInQueue(X, Y, F, S);
		}
		else	//Need Jump.
		{
			Jump(X, Y, F, S);
			PushInQueue(StopPoint[0], StopPoint[1], StopPoint[2], StopPoint[3]);
		}
	}
}

void PushInQueue(int X, int Y, int F, int S)
{
	if (Map[X][Y] != '*')
	{
		InQueue[InQueueCounter][0] = X;
		InQueue[InQueueCounter][1] = Y;
		InQueue[InQueueCounter][2] = F;
		InQueue[InQueueCounter][3] = S;
		if (Map[X][Y] != '!'&&Map[X][Y] != '%')
		{
			Map[X][Y] = '*';
		}
		Q.push(InQueue[InQueueCounter]);
		InQueueCounter++;
	}

	return;
}

void BFS()
{
	int X, Y, F, S;

	for (;Q.empty() != 1;Q.pop())
	{
		X = Q.front()[0];
		Y = Q.front()[1];
		F = Q.front()[2];
		S = Q.front()[3];

		if (Map[X][Y] == '!')
		{
			MinStep = S;

			return;
		}
		FourDimension(X, Y, F, S);
	}
}

void Jump(int X, int Y, int F, int S)
{
	StopPoint[0] = X;
	StopPoint[1] = Y;
	StopPoint[2] = F;
	StopPoint[3] = S;

	if (F == 1)
	{
		for (;;)
		{
			if (X < 1)
			{
				StopPoint[0] = 1;

				break;
			}
			else
			{
				if (Map[X][Y] == '%')
				{
					X = X - KPoint[X][Y];
				}
				else
				{
					StopPoint[0] = X;

					break;
				}
			}
		}
	}
	if (F == 2)
	{
		for (;;)
		{
			if (X > N)
			{
				StopPoint[0] = N;

				break;
			}
			else
			{
				if (Map[X][Y] == '%')
				{
					X = X + KPoint[X][Y];
				}
				else
				{
					StopPoint[0] = X;

					break;
				}
			}
		}
	}
	if (F == 3)
	{
		for (;;)
		{
			if (Y < 1)
			{
				StopPoint[1] = 1;

				break;
			}
			else
			{
				if (Map[X][Y] == '%')
				{
					Y = Y - KPoint[X][Y];
				}
				else
				{
					StopPoint[1] = Y;

					break;
				}
			}
		}
	}
	if (F == 4)
	{
		for (;;)
		{
			if (Y > M)
			{
				StopPoint[1] = M;

				break;
			}
			else
			{
				if (Map[X][Y] == '%')
				{
					Y = Y + KPoint[X][Y];
				}
				else
				{
					StopPoint[1] = Y;

					break;
				}
			}
		}
	}


	return;
}