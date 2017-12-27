//#include "stdio.h"
//
//void BFS(int x, int y, int f);
//
//int step = 0;//步数
//int stepmin = 99999;//最小步数
//int Queue[1000][2];//队列
//int Qin;//进队列
//int Qout;//出队列
//int MAP[21][21];//图
//
//int main()
//{
//	int M, N;//行列
//	int K;//加速器个数
//	int X, Y, Z;//加速器的位置以及可加速的格子数
//	int MX, NX;//重置用 不用于其他
//	int SX, SY;//开始的坐标
//	int EX, EY;//结束的坐标
//
//	int Kc;//K计数器
//
//	scanf("%d%d", &M, &N);
//
//	for (MX = 0; MX < 21; MX++)
//	{
//		for (NX = 0; NX < 21; NX++)
//		{
//			if (MX >= 1 && MX <= M&&NX >= 1 && NX <= N)//可用区域标记为0
//			{
//				MAP[MX][NX] = 0;
//			}
//			else//不可行区域标记为-9
//			{
//				MAP[MX][NX] = -9;
//			}
//		}
//	}
//
//	scanf("%d", &K);
//
//	for (Kc = 1; Kc <= K; Kc++)
//	{
//		scanf("%d%d%d", &X, &Y, &Z);
//		MAP[X][Y] = Z;
//	}
//
//	scanf("%d%d", &SX, &SY);
//	MAP[SX][SY] = -1;//令起点为-1  注意 在判断加速点的时候  需要判断位置为严格>0
//
//	scanf("%d%d", &EX, &EY);
//	MAP[EX][EY] = -2;//终点为-2
//
//	/*--------------输入完成---------------*/
//
//	Queue[0][0] = SX;
//	Queue[0][1] = SY;//起始点入队列
//	MAP[SX][SY] = 0;//将起点置为普通点
//
//	for (Qin = 1, Qout = 0; Qout <= Qin;)//Qin在前，Qout在后
//	{
//		BFS(Queue[Qout][0], Queue[Qout][1], 0);
//	}
//}
//
//void BFS(int x, int y, int f)//f为从哪里来 1 2 3 4对应上下左右 0在起点或者撞墙或者到终点时使用
//{
//	if (MAP[x][y] == -2)//到达终点
//	{
//		if (step < stepmin)
//		{
//			stepmin = step;
//		}
//		return;
//	}
//	
//	if (MAP[x][y] == -9)//撞墙
//	{
//		return;
//	}
//
//	if (MAP[x][y] > 0)//加速点
//	{
//		if (f == 0)
//		{
//
//		}
//	}
//}

#include<stdio.h>
#include<iostream>
using namespace std;
#define maxn 10000
int dis[21][21];
int map[21][21];
int n, m;
int ans = maxn;
int startx, starty, endx, endy, nextx, nexty;

int isvalid(int x, int y)
{
	if (x >= 1 && x <= n&&y >= 1 && y <= m)
		return 1;
	else
		return 0;
}
void dfs(int startx, int starty, int step)
{
	dis[startx][starty] = step;
	if (startx == endx&&starty == endy)
	{
		if (step < ans)
		{
			ans = step;
			return;
		}
	}

	nextx = startx;
	nexty = starty - 1;
	if (isvalid(nextx, nexty))
	{
		while (map[nextx][nexty] > 0)
		{
			nexty -= map[nextx][nexty];
			if (nexty <= 1)
			{
				nexty = 1;
				break;
			}
		}
		if (dis[nextx][nexty] > step + 1)
		{
			dfs(nextx, nexty, step + 1);
		}
	}

	nextx = startx;
	nexty = starty + 1;
	if (isvalid(nextx, nexty))
	{
		while (map[nextx][nexty] > 0)
		{
			nexty += map[nextx][nexty];
			if (nexty >= m)
			{
				nexty = m;
				break;
			}
		}
		if (dis[nextx][nexty] > step + 1)
		{
			dfs(nextx, nexty, step + 1);
		}
	}

	nextx = startx - 1;
	nexty = starty;
	if (isvalid(nextx, nexty))
	{
		while (map[nextx][nexty] > 0)
		{
			nextx -= map[nextx][nexty];
			if (nextx <= 1)
			{
				nextx = 1;
				break;
			}
		}
		if (dis[nextx][nexty] > step + 1)
		{
			dfs(nextx, nexty, step + 1);
		}
	}
	nextx = startx + 1;
	nexty = starty;
	if (isvalid(nextx, nexty))
	{
		while (map[nextx][nexty] > 0)
		{
			nextx += map[nextx][nexty];
			if (nextx >= n)
			{
				nextx = n;
				break;
			}
		}
		if (dis[nextx][nexty] > step + 1)
		{
			dfs(nextx, nexty, step + 1);
		}
	}
}

int main()
{
	int i, j, k, x, y, z;
	while (~scanf("%d%d", &n, &m))
	{
		ans = maxn;
		for (i = 0; i < 21; i++)
		{
			for (j = 0; j < 21; j++)
			{
				dis[i][j] = maxn;
				map[i][j] = 0;
			}
		}
		scanf("%d", &k);
		for (i = 0; i < k; i++)
		{
			scanf("%d%d%d", &x, &y, &z);
			map[x][y] = z;
		}
		scanf("%d%d", &startx, &starty);
		scanf("%d%d", &endx, &endy);
		dfs(startx, starty, 0);
		if (ans != maxn)
		{
			printf("%d\n", ans);
		}
		else
		{
			printf("Oh my Hubro QVQ\n");
		}
	}

	return 0;
}