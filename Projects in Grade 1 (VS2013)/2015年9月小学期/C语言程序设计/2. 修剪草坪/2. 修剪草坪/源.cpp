#include "stdio.h"

int Search1(int a, int num);
int Search2(int b, int num);

int Field[105][105];
int n, m;

int main()
{
	int nc, mc;

	int flag;

	scanf("%d%d", &n, &m);

	for (nc = 0; nc < n; nc++)
	{
		for (mc = 0; mc < m; mc++)
		{
			scanf("%d", &Field[nc][mc]);
		}
	}

	for (nc = 0; nc < n; nc++)
	{
		for (mc = 0; mc < m; mc++)
		{
			flag = Search1(nc, Field[nc][mc]);//行搜索

			if (flag == 1)
			{
				continue;
			}
			else
			{
				flag = Search2(mc, Field[nc][mc]);//列搜索
				if (flag == 0)
				{
					printf("NO\n");
					return 0;
				}
				else
				{
					continue;
				}
			}
		}
	}

	printf("YES\n");
}

int Search1(int a, int num)//行搜索
{
	int c;
	
	for (c = 0; c < m; c++)
	{
		if (Field[a][c]>num)
		{
			return 0;
		}
	}
	return 1;//是行的最大值
}

int Search2(int b, int num)//列搜索
{
	int c;
	
	for (c = 0; c < n; c++)
	{
		if (Field[c][b]>num)
		{
			return 0;
		}
	}
	return 1;//是列的最大值
}