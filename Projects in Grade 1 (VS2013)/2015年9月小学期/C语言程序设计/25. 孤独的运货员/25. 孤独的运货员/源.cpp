#include "stdio.h"

struct St
{
	int Front;
	int Rear;
	int Goods[1000];/*Queue*/
}Station[102];
int StationC;

int Car[105];/*Stack*/
int CarTop;
int AllTime;

int SET;
int N, S, Q;/*N：环中站的个数 S：火车最大容量 Q：B平台能放置货物总数*/
int Nc;
int GoodsNum;

void POP();
void PUSH();

int main()
{
	scanf("%d", &SET);

	while (SET >= 1)
	{
		/*Reset*/
		for (StationC = 0; StationC < 102; StationC++)
		{
			Station[StationC].Front = 0;
			Station[StationC].Rear = 0;
			Station[StationC].Goods[0] = 0;
		}
		StationC = 0;

		for (CarTop = 0; CarTop < 105; CarTop++)
		{
			Car[CarTop] = 0;
		}
		CarTop = 0;
		AllTime = 0;
		/*Reset End*/

		scanf("%d%d%d", &N, &S, &Q);
		for (Nc = 1; Nc <= N; Nc++)
		{
			scanf("%d", &GoodsNum);
			while (GoodsNum >= 1)
			{
				scanf("%d", &Station[Nc].Goods[Station[Nc].Rear]);
				Station[Nc].Rear++;

				GoodsNum--;
			}
		}

		for (StationC = 1; StationC <= N + 1; StationC++)
		{
			if (StationC == N + 1)
			{
				StationC = 1;
			}

			POP();
			PUSH();

			if (CarTop == 0)/*跳出检查*/
			{
				int searchEND;
				int Flag = 1;
				for (searchEND = 1; searchEND <= N; searchEND++)
				{
					if (Station[searchEND].Rear - Station[searchEND].Front > 0)
					{
						Flag = 0;
					}
				}
				if (Flag == 1)
				{
					break;
				}
			}
			AllTime = AllTime + 2;
		}
		printf("%d\n", AllTime);
		SET--;
	}
}

void POP()
{
	if (CarTop == 0)/*如果卡车是空的*/
	{
		return;
	}
	else
	{
		CarTop--;
		for (; CarTop >= 0;)
		{
			if (Car[CarTop] == StationC)
			{
				Car[CarTop] = 0;
				CarTop--;
				AllTime++;
				continue;
			}
			else
			{
				if ((Station[StationC].Rear - Station[StationC].Front) == Q)
				{
					CarTop++;
					return;
				}
				else
				{
					Station[StationC].Goods[Station[StationC].Rear] = Car[CarTop];
					Station[StationC].Rear++;
					Car[CarTop] = 0;
					CarTop--;
					AllTime++;
					continue;
				}
			}
		}
		CarTop++;
	}
}

void PUSH()
{
	if (CarTop == S)
	{
		return;
	}
	else
	{
		for (; CarTop < S;)
		{
			if (Station[StationC].Front == Station[StationC].Rear)
			{
				return;
			}
			else
			{
				Car[CarTop] = Station[StationC].Goods[Station[StationC].Front];
				Station[StationC].Front++;
				CarTop++;
				AllTime++;
				continue;
			}
		}
	}
}