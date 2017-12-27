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

		for (mc = 0; mc < m; mc++)/*��1��ʼ��¼*/
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
				MAP[mc][nc] = MAP[mc][nc] + MIN((MAP[mc][nc + 1]), (MIN(MAP[(mc + 1) % m][nc + 1], MAP[(mc - 1 + m) % m][nc + 1])));/*������С�Ѿ��������*/
			}
		}

		int SearchMin = MAP[0][0];/*ʡȥһ���ж�+ʡȥ���ֵ����*/
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
			if (nc < n - 1)/*���û����ĩβ*/
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
	j++;/*��λ����һ��*/

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

	/*�����м�*/
	if (MAP[x][j] < MAP[y][j])/*����С*/
	{
		if (MAP[x][j] < MAP[z][j])/*���������С*/
		{
			return x;
		}
		else
		{
			if (MAP[x][j] == MAP[z][j])/*������Ϻ����¶���С*/
			{
				return MIN(x, z);
			}
			else/*���������С*/
			{
				return z;
			}
		}
	}
	else/*����>=�м�*/
	{
		if (MAP[x][j] == MAP[y][j])/*����=�м�*/
		{
			if (MAP[z][j] < MAP[x][j])/*������С*/
			{
				return z;
			}
			else
			{
				if (MAP[z][j] == MAP[y][j])/*������������*/
				{
					return MIN(z,(MIN(x, y)));
				}
				else/*���Ϻ��м���С*/
				{
					return MIN(x, y);
				}
			}
		}
		else/*����>�м�*/
		{
			if (MAP[y][j] < MAP[z][j])/*�м���С*/
			{
				return y;
			}
			else
			{
				if (MAP[y][j] == MAP[z][j])/*�м�=����*/
				{
					return MIN(y, z);
				}
				else/*������С*/
				{
					return z;
				}
			}
		}
	}
}