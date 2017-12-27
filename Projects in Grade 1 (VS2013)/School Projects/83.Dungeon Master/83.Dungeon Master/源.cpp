#include "stdio.h"
#define N 40

int BFS(int x, int  y, int  z);

int A, B, H;//长 宽 高
char dungeon[N][N][N];//地牢  *********按照H B A来定义**********
int queue[100000][3];//队列
bool sign[N][N][N];//标记函数
int minute[N][N][N];//时间

int main()
{
	int minutes;
	int x, y, z;//长 宽 高的计数器
	while (1)
	{
		scanf("%d%d%d", &H, &B, &A);//输入

		if (A == 0 || B == 0 || H == 0)//退出
		{
			break;
		}

		for (z = 0; z < H; z++)//输入地牢
		{
			for (y = 0; y < B; y++)
			{
				scanf("%s", dungeon[z][y]);
			}
			getchar();
		}

		for (z = 0; z < H; z++)//将地牢的可移动的地方标记为可访问的
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

		for (z = 0; z < H; z++)//确定Start的位置
		{
			for (y = 0; y < B; y++)
			{
				for (x = 0; x < A; x++)
				{
					if (dungeon[z][y][x] == 'S')
					{
						minutes = BFS(z, y, x);//找到起始点 进入BFS函数  算出minutes  预定：返回非零整数  则printf(****)   返回为-1，则trapped。
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
	int in, out;//入队和出队计数器
	int stepx, stepy, stepz;//入队和出队的坐标 已初始化

	in = out = 0;//计数器清零

	queue[0][0] = z;
	queue[0][1] = y;
	queue[0][2] = x;//开始点入队

	sign[z][y][x] = 0;//起始点标记为不可访问
	minute[z][y][x] = 0;//时间初始化

	while (out <= in)
	{
		stepx = queue[out][2];
		stepy = queue[out][1];
		stepz = queue[out][0];//出队位置记录
		out++;

		/*移动后的点位置判断*/
		if (dungeon[stepz][stepy][stepx] == 'E')
		{
			return minute[stepz][stepy][stepx];//若可以逃脱 则返回时间
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