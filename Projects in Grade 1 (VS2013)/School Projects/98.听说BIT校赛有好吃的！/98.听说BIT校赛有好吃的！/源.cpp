#include "stdio.h"
#define X 1005

int Caneat(int start);

int N;//N��
int Ncount;
int M;//M��
int Mcount;
int MAP[X][X];//��ͼ
int MAX;//�ܳԵ���������

int main()
{
	for (Ncount = 0; Ncount < X; Ncount++)//��ʼ��
	{
		for (Mcount = 0; Mcount < X; Mcount++)
		{
			MAP[Ncount][Mcount] = 9;
		}
	}

	scanf("%d%d", &N, &M);

	for (Ncount = 0; Ncount < N; Ncount++)//����
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

int Caneat(int start)//��ÿһ���㿪ʼ����
{
	int row;//��
	int colum;//��

	for (row = Ncount; row < N; row++)
	{
		for (colum = Mcount; Mcount < M; colum++)
		{
			if ()
		}
	}
}