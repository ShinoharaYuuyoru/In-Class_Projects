#include "stdio.h" 
#include "stdlib.h" 

struct Q
{
	short y;
	short x;
	int step;
}Queue[6000000];
int QueueFront = 0;
int QueueRear = 0;
int ALLStep = 0;

char MAP[2005][2005];
int n, m;

void BFS();

int main()
{
	char InputTemp;

	int nc, mc;

	scanf("%d%d", &n, &m);
	InputTemp = getchar();

	for (nc = 0; nc < n; nc++)
	{
		for (mc = 0; mc <= m; mc++)
		{
			InputTemp = getchar();
			MAP[nc][mc] = InputTemp;
			if (InputTemp == 'N')/*起点标记并入队*/
			{
				Queue[0].x = mc;
				Queue[0].y = nc;
				Queue[0].step = 0;
				QueueRear++;
			}
			if (InputTemp == '\n')
			{
				MAP[nc][mc] = '\0';
				continue;
			}
		}
	}

	for (QueueFront = 0; QueueFront < QueueRear; QueueFront++)
	{
		BFS();
	}
	printf("Bad Eureka\n");
}

void BFS()/*直接进行临近四个点的判断 符合条件的入队*/
{
	int Ex, Ey;

	MAP[Queue[QueueFront].y][Queue[QueueFront].x] = '*';/*标记不可访问*/

	if (Queue[QueueFront].x + 1 < m)
	{
		if (MAP[Queue[QueueFront].y][Queue[QueueFront].x + 1] == 'C')
		{
			ALLStep = Queue[QueueFront].step + 1;
			printf("%d\n", ALLStep);
			exit(0);
		}
		if (MAP[Queue[QueueFront].y][Queue[QueueFront].x + 1] == 'E')/*传送门*/
		{
			/*先入队*/
			MAP[Queue[QueueFront].y][Queue[QueueFront].x + 1] = '*';
			Queue[QueueRear].x = Queue[QueueFront].x + 1;
			Queue[QueueRear].y = Queue[QueueFront].y;
			Queue[QueueRear].step = Queue[QueueFront].step + 1;
			QueueRear++;

			/*把所有的E全部入队*/

			for (Ey = 0; Ey < n; Ey++)
			{
				for (Ex = 0; Ex < m; Ex++)
				{
					if (MAP[Ey][Ex] == 'E')
					{
						Queue[QueueRear].x = Ex;
						Queue[QueueRear].y = Ey;
						Queue[QueueRear].step = Queue[QueueFront].step + 1;
						MAP[Ey][Ex] = '*';
						QueueRear++;
					}
				}
			}
		}
		if (MAP[Queue[QueueFront].y][Queue[QueueFront].x + 1] == '.')
		{
			MAP[Queue[QueueFront].y][Queue[QueueFront].x + 1] = '*';
			Queue[QueueRear].x = Queue[QueueFront].x + 1;
			Queue[QueueRear].y = Queue[QueueFront].y;
			Queue[QueueRear].step = Queue[QueueFront].step + 1;
			QueueRear++;
		}
		/*如果是M 则直接跳过不进队*/
	}
	if (Queue[QueueFront].x - 1 >= 0)
	{
		if (MAP[Queue[QueueFront].y][Queue[QueueFront].x - 1] == 'C')
		{
			ALLStep = Queue[QueueFront].step + 1;
			printf("%d\n", ALLStep);
			exit(0);
		}
		if (MAP[Queue[QueueFront].y][Queue[QueueFront].x - 1] == 'E')/*传送门*/
		{
			/*先入队*/
			MAP[Queue[QueueFront].y][Queue[QueueFront].x - 1] = '*';
			Queue[QueueRear].x = Queue[QueueFront].x - 1;
			Queue[QueueRear].y = Queue[QueueFront].y;
			Queue[QueueRear].step = Queue[QueueFront].step + 1;
			QueueRear++;

			/*把所有的E全部入队*/
			for (Ey = 0; Ey < n; Ey++)
			{
				for (Ex = 0; Ex < m; Ex++)
				{
					if (MAP[Ey][Ex] == 'E')
					{
						Queue[QueueRear].x = Ex;
						Queue[QueueRear].y = Ey;
						Queue[QueueRear].step = Queue[QueueFront].step + 1;
						MAP[Ey][Ex] = '*';
						QueueRear++;
					}
				}
			}
		}
		if (MAP[Queue[QueueFront].y][Queue[QueueFront].x - 1] == '.')
		{
			MAP[Queue[QueueFront].y][Queue[QueueFront].x - 1] = '*';
			Queue[QueueRear].x = Queue[QueueFront].x - 1;
			Queue[QueueRear].y = Queue[QueueFront].y;
			Queue[QueueRear].step = Queue[QueueFront].step + 1;
			QueueRear++;
		}
	}
	if (Queue[QueueFront].y + 1 < n)
	{
		if (MAP[Queue[QueueFront].y + 1][Queue[QueueFront].x] == 'C')
		{
			ALLStep = Queue[QueueFront].step + 1;
			printf("%d\n", ALLStep);
			exit(0);
		}
		if (MAP[Queue[QueueFront].y + 1][Queue[QueueFront].x] == 'E')/*传送门*/
		{
			/*先入队*/
			MAP[Queue[QueueFront].y + 1][Queue[QueueFront].x] = '*';
			Queue[QueueRear].x = Queue[QueueFront].x;
			Queue[QueueRear].y = Queue[QueueFront].y + 1;
			Queue[QueueRear].step = Queue[QueueFront].step + 1;
			QueueRear++;

			/*把所有的E全部入队*/
			for (Ey = 0; Ey < n; Ey++)
			{
				for (Ex = 0; Ex < m; Ex++)
				{
					if (MAP[Ey][Ex] == 'E')
					{
						Queue[QueueRear].x = Ex;
						Queue[QueueRear].y = Ey;
						Queue[QueueRear].step = Queue[QueueFront].step + 1;
						MAP[Ey][Ex] = '*';
						QueueRear++;
					}
				}
			}
		}
		if (MAP[Queue[QueueFront].y + 1][Queue[QueueFront].x] == '.')
		{
			MAP[Queue[QueueFront].y + 1][Queue[QueueFront].x] = '*';
			Queue[QueueRear].x = Queue[QueueFront].x;
			Queue[QueueRear].y = Queue[QueueFront].y + 1;
			Queue[QueueRear].step = Queue[QueueFront].step + 1;
			QueueRear++;
		}
	}
	if (Queue[QueueFront].y - 1 >= 0)
	{
		if (MAP[Queue[QueueFront].y - 1][Queue[QueueFront].x] == 'C')
		{
			ALLStep = Queue[QueueFront].step + 1;
			printf("%d\n", ALLStep);
			exit(0);
		}
		if (MAP[Queue[QueueFront].y - 1][Queue[QueueFront].x] == 'E')/*传送门*/
		{
			/*先入队*/
			MAP[Queue[QueueFront].y - 1][Queue[QueueFront].x] = '*';
			Queue[QueueRear].x = Queue[QueueFront].x;
			Queue[QueueRear].y = Queue[QueueFront].y - 1;
			Queue[QueueRear].step = Queue[QueueFront].step + 1;
			QueueRear++;

			/*把所有的E全部入队*/
			for (Ey = 0; Ey < n; Ey++)
			{
				for (Ex = 0; Ex < m; Ex++)
				{
					if (MAP[Ey][Ex] == 'E')
					{
						Queue[QueueRear].x = Ex;
						Queue[QueueRear].y = Ey;
						Queue[QueueRear].step = Queue[QueueFront].step + 1;
						MAP[Ey][Ex] = '*';
						QueueRear++;
					}
				}
			}
		}
		if (MAP[Queue[QueueFront].y - 1][Queue[QueueFront].x] == '.')
		{
			MAP[Queue[QueueFront].y - 1][Queue[QueueFront].x] = '*';
			Queue[QueueRear].x = Queue[QueueFront].x;
			Queue[QueueRear].y = Queue[QueueFront].y - 1;
			Queue[QueueRear].step = Queue[QueueFront].step + 1;
			QueueRear++;
		}
	}
}