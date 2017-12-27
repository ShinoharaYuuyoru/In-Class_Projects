#include "stdio.h"
#include "string.h"

int MAP[12][110];
int m, n;

int MIN(int a, int b);
int SearchPath(int p, int j);

int main()
{
	int mc, nc;

	while (scanf("%d%d", &m, &n) != EOF)
	{
		memset(MAP, 0x1f, sizeof(MAP));

		for (mc = 0; mc < m; mc++)/*从1开始记录*/
		{
			for (nc = 0; nc < n; nc++)
			{
				scanf("%d", &MAP[mc][nc]);
			}
		}

		for (nc = n - 2; nc >= 0; nc--)
		{
			for (mc = m - 1; mc >= 0; mc--)
			{
				MAP[mc][nc] = MAP[mc][nc] + MIN((MAP[mc][nc + 1]), (MIN(MAP[(mc + 1) % m][nc + 1], MAP[(mc - 1 + m) % m][nc + 1])));/*整个大小已经计算完毕*/
			}
		}

		int SearchMin = MAP[0][0];/*省去一个判断+省去最大值顾虑*/
		int Path = 0;
		for (mc = 1; mc < m; mc++)
		{
			if (MAP[mc][0] < SearchMin)
			{
				SearchMin = MAP[mc][0];
				Path = mc;
			}
		}

		for (nc = 0; nc < n; nc++)
		{
			printf("%d", Path + 1);
			if (nc < n - 1)/*如果没到最末尾*/
			{
				printf(" ");
			}
			if (nc == n - 1)
			{
				break;
			}
			Path = SearchPath(Path, nc);
		}
		printf("\n");
		printf("%d\n", SearchMin);
	}
}

int MIN(int a, int b)
{
	if (a <= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int SearchPath(int p, int j)
{
	int x, y, z;
	j++;/*定位到下一列*/

	x = p - 1;
	if (x == -1)
	{
		x = m - 1;
	}
	y = p;
	z = p + 1;
	if (z == m)
	{
		z = 0;
	}

	/*比起中间*/
	if (MAP[x][j] < MAP[y][j])/*右上小*/
	{
		if (MAP[x][j] < MAP[z][j])/*如果右上最小*/
		{
			return x;
		}
		else
		{
			if (MAP[x][j] == MAP[z][j])/*如果右上和右下都最小*/
			{
				return MIN(x, z);
			}
			else/*如果右下最小*/
			{
				return z;
			}
		}
	}
	else/*右上>=中间*/
	{
		if (MAP[x][j] == MAP[y][j])/*右上=中间*/
		{
			if (MAP[z][j] < MAP[x][j])/*右下最小*/
			{
				return z;
			}
			else
			{
				if (MAP[z][j] == MAP[y][j])/*如果三个都相等*/
				{
					return MIN(z,(MIN(x, y)));
				}
				else/*右上和中间最小*/
				{
					return MIN(x, y);
				}
			}
		}
		else/*右上>中间*/
		{
			if (MAP[y][j] < MAP[z][j])/*中间最小*/
			{
				return y;
			}
			else
			{
				if (MAP[y][j] == MAP[z][j])/*中间=右下*/
				{
					return MIN(y, z);
				}
				else/*右下最小*/
				{
					return z;
				}
			}
		}
	}
}