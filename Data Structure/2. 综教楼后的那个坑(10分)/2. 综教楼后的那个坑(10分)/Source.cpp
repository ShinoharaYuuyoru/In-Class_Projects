#include "stdio.h"
#include "stdlib.h"

typedef struct NODE
{
	struct NODE *Left;

	int Width;
	int Height;
	int Position;

	struct NODE *Right;
}WALL;
WALL *First;
WALL *InputL;
WALL *InputR;
WALL *Start;
WALL *LeftWall;
WALL *RightWall;

int N;
int Nc;
int MIN = 99999999;
long long int TimeCounter;
long long int Time[100000];

void Flow();
void WallLow(int Flag);

int main()
{
	scanf("%d", &N);
	for (Nc = 0;Nc < N;Nc++)
	{
		if (Nc == 0)
		{
			InputR = (WALL*)malloc(sizeof(WALL));
			InputR->Left = NULL;
			scanf("%d%d", &InputR->Width, &InputR->Height);
			InputR->Position = Nc;
			InputR->Right = NULL;

			First = InputR;
			InputL = InputR;
		}
		else
		{
			InputR = (WALL*)malloc(sizeof(WALL));
			InputR->Left = InputL;
			scanf("%d%d", &InputR->Width, &InputR->Height);
			InputR->Position = Nc;
			InputR->Right = NULL;
			
			InputL->Right = InputR;
			InputL = InputR;
		}

		if (InputR->Height < MIN)
		{
			Start = InputR;
			MIN = InputR->Height;
		}
	}

	TimeCounter = 0;
	Flow();

	First = Start;

	for (Nc = 0;Nc < N;Nc++)
	{
		printf("%lld\n", Time[Nc]);
	}

	return 0;
}

void Flow()
{
	while (1)
	{
		LeftWall = Start->Left;
		RightWall = Start->Right;

		if (LeftWall == NULL&&RightWall == NULL)
		{
			TimeCounter = TimeCounter + Start->Width;
			Time[Start->Position] = TimeCounter;
			free(Start);

			return;
		}
		else
		{
			if (LeftWall == NULL)
			{
				if (Start->Height > RightWall->Height)
				{
					WallLow(1);
				}
				else
				{
					TimeCounter = TimeCounter + Start->Width;
					Time[Start->Position] = TimeCounter;

					TimeCounter = TimeCounter + (long long int)(Start->Width)*((RightWall->Height) - (Start->Height) - 1);

					RightWall->Width = RightWall->Width + Start->Width;
					RightWall->Left = NULL;
					free(Start);
					Start = RightWall;
				}

				continue;
			}
			if (RightWall == NULL)
			{
				if (Start->Height > LeftWall->Height)
				{
					WallLow(0);
				}
				else
				{
					TimeCounter = TimeCounter + Start->Width;
					Time[Start->Position] = TimeCounter;

					TimeCounter = TimeCounter + (long long int)(Start->Width)*((LeftWall->Height) - (Start->Height) - 1);

					LeftWall->Width = LeftWall->Width + Start->Width;
					LeftWall->Right = NULL;
					free(Start);
					Start = LeftWall;
				}

				continue;
			}

			if (LeftWall->Height > Start->Height&&RightWall->Height > Start->Height)
			{
				if (LeftWall->Height > RightWall->Height)
				{
					TimeCounter = TimeCounter + Start->Width;
					Time[Start->Position] = TimeCounter;

					TimeCounter = TimeCounter + (long long int)(Start->Width)*((RightWall->Height) - (Start->Height) - 1);

					RightWall->Width = RightWall->Width + Start->Width;
					RightWall->Left = LeftWall;
					LeftWall->Right = RightWall;
					free(Start);
					Start = RightWall;

					continue;
				}
				if (LeftWall->Height < RightWall->Height)
				{
					TimeCounter = TimeCounter + Start->Width;
					Time[Start->Position] = TimeCounter;

					TimeCounter = TimeCounter + (long long int)(Start->Width)*((LeftWall->Height) - (Start->Height) - 1);

					LeftWall->Width = LeftWall->Width + Start->Width;
					LeftWall->Right = RightWall;
					RightWall->Left = LeftWall;
					free(Start);
					Start = LeftWall;

					continue;
				}
			}
			else
			{
				if (LeftWall->Height < Start->Height)
				{
					WallLow(0);

					continue;
				}

				if (RightWall->Height < Start->Height)
				{
					WallLow(1);

					continue;
				}
			}
		}
	}
}

void WallLow(int Flag)
{
	if (Flag == 0)//LeftWall Low
	{
		WALL *Higher = LeftWall->Left;
		WALL *Front = LeftWall;
		while (1)
		{
			if (Higher == NULL)
			{
				break;
			}
			else
			{
				if (Higher->Height > Front->Height)
				{
					break;
				}
			}
			Higher = Higher->Left;
			Front = Front->Left;
		}
		Start = Front;
	}
	else
	{
		WALL *Higher = RightWall->Right;
		WALL *Front = RightWall;
		while (1)
		{
			if (Higher == NULL)
			{
				break;
			}
			else
			{
				if (Higher->Height > Front->Height)
				{
					break;
				}
			}
			Higher = Higher->Right;
			Front = Front->Right;
		}
		Start = Front;
	}

	return;
}