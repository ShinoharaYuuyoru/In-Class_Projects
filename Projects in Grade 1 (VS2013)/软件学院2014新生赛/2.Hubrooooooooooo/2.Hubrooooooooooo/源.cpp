//#include "stdio.h"
//
//void BFS(int x, int y, int f);
//
//int step = 0;//����
//int stepmin = 99999;//��С����
//int Queue[1000][2];//����
//int Qin;//������
//int Qout;//������
//int MAP[21][21];//ͼ
//
//int main()
//{
//	int M, N;//����
//	int K;//����������
//	int X, Y, Z;//��������λ���Լ��ɼ��ٵĸ�����
//	int MX, NX;//������ ����������
//	int SX, SY;//��ʼ������
//	int EX, EY;//����������
//
//	int Kc;//K������
//
//	scanf("%d%d", &M, &N);
//
//	for (MX = 0; MX < 21; MX++)
//	{
//		for (NX = 0; NX < 21; NX++)
//		{
//			if (MX >= 1 && MX <= M&&NX >= 1 && NX <= N)//����������Ϊ0
//			{
//				MAP[MX][NX] = 0;
//			}
//			else//������������Ϊ-9
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
//	MAP[SX][SY] = -1;//�����Ϊ-1  ע�� ���жϼ��ٵ��ʱ��  ��Ҫ�ж�λ��Ϊ�ϸ�>0
//
//	scanf("%d%d", &EX, &EY);
//	MAP[EX][EY] = -2;//�յ�Ϊ-2
//
//	/*--------------�������---------------*/
//
//	Queue[0][0] = SX;
//	Queue[0][1] = SY;//��ʼ�������
//	MAP[SX][SY] = 0;//�������Ϊ��ͨ��
//
//	for (Qin = 1, Qout = 0; Qout <= Qin;)//Qin��ǰ��Qout�ں�
//	{
//		BFS(Queue[Qout][0], Queue[Qout][1], 0);
//	}
//}
//
//void BFS(int x, int y, int f)//fΪ�������� 1 2 3 4��Ӧ�������� 0��������ײǽ���ߵ��յ�ʱʹ��
//{
//	if (MAP[x][y] == -2)//�����յ�
//	{
//		if (step < stepmin)
//		{
//			stepmin = step;
//		}
//		return;
//	}
//	
//	if (MAP[x][y] == -9)//ײǽ
//	{
//		return;
//	}
//
//	if (MAP[x][y] > 0)//���ٵ�
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