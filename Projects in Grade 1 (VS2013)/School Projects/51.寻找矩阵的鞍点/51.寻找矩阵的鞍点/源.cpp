#include "stdio.h"
#define N 100
int main()
{
	int m = 0/*行数*/, n = 0/*列数*/;
	int mcount/*行数计数器*/, ncount/*列数计数器*/;
	int max = 0/*每行最大值比较器*/, mpick = 0/*第mcount行最大值的行数记录器*/, npick = 0/*第mcount行最大值的列数记录器*/, suc = 0/*满足个数计数器*/, mrcount/*确定每列最小数时的重新计数器*/;
	int tra[N][N] = { { 0 } }/*矩阵*/;
	scanf("%d%d", &m, &n);
	for (mcount = 0; mcount < m; mcount++)//定位第mcount行
	{
		for (ncount = 0; ncount < n; ncount++)//确定第mcount行的所有元素
		{
			scanf("%d", &tra[mcount][ncount]);
		}
	}
	for (mcount = 0; mcount < m; mcount++)//定位第mcount行
	{
		for (ncount = 0; ncount < n; ncount++)//判断第mcount行中的最大值
		{
			if (tra[mcount][ncount]>max)
			{
				max = tra[mcount][ncount];
				mpick = mcount;
				npick = ncount;
			}
		}
		for (mrcount = 0; mrcount<m; mrcount++)
		{
			if (tra[mpick][npick]>tra[mrcount][npick])
			{
				max = 0;
				break;
			}
			else
			{
				if (mrcount == m - 1)
				{
					printf("Point:a[%d][%d]==%d\n", mpick, npick, max);
					max = 0;
					suc++;
				}
			}
		}
		if (mcount == m - 1 && suc == 0)
		{
			printf("No Point\n");
		}
	}
}