#include "stdio.h"
#define N 40

int BFS(int x, int  y, int  z);

int A, B, H;//�� �� ��
char dungeon[N][N][N];//����  *********����H B A������**********
int queue[100000][3];//����
bool sign[N][N][N];//��Ǻ���
int minute[N][N][N];//ʱ��

int main()
{
	int minutes;
	int x, y, z;//�� �� �ߵļ�����
	while (1)
	{
		scanf("%d%d%d", &H, &B, &A);//����

		if (A == 0 || B == 0 || H == 0)//�˳�
		{
			break;
		}

		for (z = 0; z < H; z++)//�������
		{
			for (y = 0; y < B; y++)
			{
				scanf("%s", dungeon[z][y]);
			}
			getchar();
		}

		for (z = 0; z < H; z++)//�����εĿ��ƶ��ĵط����Ϊ�ɷ��ʵ�
		{
			for (y = 0; y < B; y++)
			{
				for (x = 0; x < A; x++)
				{
					if (dungeon[z][y][x] == '#')
					{
						sign[z][y][x] = 0;
					}
					else
					{
						sign[z][y][x] = 1;
					}
				}
			}
		}

		for (z = 0; z < H; z++)//ȷ��Start��λ��
		{
			for (y = 0; y < B; y++)
			{
				for (x = 0; x < A; x++)
				{
					if (dungeon[z][y][x] == 'S')
					{
						minutes = BFS(z, y, x);//�ҵ���ʼ�� ����BFS����  ���minutes  Ԥ�������ط�������  ��printf(****)   ����Ϊ-1����trapped��
					}
				}
			}
		}
		if (minutes >= 0)
		{
			printf("Escaped in %d minute(s).\n", minutes);
		}
		else
		{
			printf("Trapped!\n");
		}
	}
}

int BFS(int z, int  y, int  x)
{
	int in, out;//��Ӻͳ��Ӽ�����
	int stepx, stepy, stepz;//��Ӻͳ��ӵ����� �ѳ�ʼ��

	in = out = 0;//����������

	queue[0][0] = z;
	queue[0][1] = y;
	queue[0][2] = x;//��ʼ�����

	sign[z][y][x] = 0;//��ʼ����Ϊ���ɷ���
	minute[z][y][x] = 0;//ʱ���ʼ��

	while (out <= in)
	{
		stepx = queue[out][2];
		stepy = queue[out][1];
		stepz = queue[out][0];//����λ�ü�¼
		out++;

		/*�ƶ���ĵ�λ���ж�*/
		if (dungeon[stepz][stepy][stepx] == 'E')
		{
			return minute[stepz][stepy][stepx];//���������� �򷵻�ʱ��
		}
		
		if ((stepx + 1) <= N && sign[stepz][stepy][stepx + 1])
		{
			in++;
			queue[in][0] = stepz;
			queue[in][1] = stepy;
			queue[in][2] = stepx + 1;
			minute[stepz][stepy][stepx + 1] = minute[stepz][stepy][stepx] + 1;
			sign[stepz][stepy][stepx + 1] = 0;
		}
		if ((stepx - 1) <= N && sign[stepz][stepy][stepx - 1])
		{
			in++;
			queue[in][0] = stepz;
			queue[in][1] = stepy;
			queue[in][2] = stepx - 1;
			minute[stepz][stepy][stepx - 1] = minute[stepz][stepy][stepx] + 1;
			sign[stepz][stepy][stepx - 1] = 0;
		}
		if ((stepy + 1) <= N && sign[stepz][stepy + 1][stepx])
		{
			in++;
			queue[in][0] = stepz;
			queue[in][1] = stepy + 1;
			queue[in][2] = stepx;
			minute[stepz][stepy + 1][stepx] = minute[stepz][stepy][stepx] + 1;
			sign[stepz][stepy + 1][stepx] = 0;
		}
		if ((stepy - 1) <= N && sign[stepz][stepy - 1][stepx])
		{
			in++;
			queue[in][0] = stepz;
			queue[in][1] = stepy - 1;
			queue[in][2] = stepx;
			minute[stepz][stepy - 1][stepx] = minute[stepz][stepy][stepx] + 1;
			sign[stepz][stepy - 1][stepx] = 0;
		}
		if ((stepz + 1) <= N && sign[stepz + 1][stepy][stepx])
		{
			in++;
			queue[in][0] = stepz + 1;
			queue[in][1] = stepy;
			queue[in][2] = stepx;
			minute[stepz + 1][stepy][stepx] = minute[stepz][stepy][stepx] + 1;
			sign[stepz + 1][stepy][stepx] = 0;
		}
		if ((stepz - 1) <= N && sign[stepz - 1][stepy][stepx])
		{
			in++;
			queue[in][0] = stepz - 1;
			queue[in][1] = stepy;
			queue[in][2] = stepx;
			minute[stepz - 1][stepy][stepx] = minute[stepz][stepy][stepx] + 1;
			sign[stepz - 1][stepy][stepx] = 0;
		}
	}
	return -1;
}