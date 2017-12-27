#include "stdio.h"
#define X 1005

int Caneat(int start);

int N;//N行
int Ncount;
int M;//M列
int Mcount;
int MAP[X][X];//地图
int MAX;//能吃到的最大可能

int main()
{
	for (Ncount = 0; Ncount < X; Ncount++)//初始化
	{
		for (Mcount = 0; Mcount < X; Mcount++)
		{
			MAP[Ncount][Mcount] = 9;
		}
	}

	scanf("%d%d", &N, &M);

	for (Ncount = 0; Ncount < N; Ncount++)//输入
	{
		for (Mcount = 0; Mcount < N; Mcount++)
		{
			scanf("%d", &MAP[Mcount][Ncount]);
		}
	}

	for (Ncount = 0; Ncount < N; Ncount++)
	{
		for (Mcount = 0; Mcount < M; Mcount++)
		{
			Caneat(MAP[Ncount][Mcount]);
		}
	}
}

int Caneat(int start)//从每一个点开始计数
{
	int row;//行
	int colum;//列

	for (row = Ncount; row < N; row++)
	{
		for (colum = Mcount; Mcount < M; colum++)
		{
			if ()
		}
	}
}