#include "stdio.h"
#define N 50000
int main()
{
	int n/*输入2n张牌的一半张数*/, all[N] = { 0 }/*原始牌数组*/, change[N] = { 0 }/*洗牌数组*/, save1[N] = { 0 }/*临时存储前n数组*/, save2[N] = { 0 }/*临时存储后n数组*/;
	int i/*总牌数录入计数器&总牌数*/,j/*洗牌次数*/,k/*取前n个牌计数器*/,l/*取后n个牌计数器*/,c/*数组比较计数器*/,x/*前n个数排序计数器*/,y/*后n个数排序计数器*/,z/*最终计数器*/;
	scanf("%d", &n);
	for (i = 1; i <= 2 * n; i++)
	{
		all[i] = i;
		change[i] = i;
	}
	i--;
	for (j = 1;1;j++)
	{
		for (c = 1; c <= i; c++)
		{
			if (change[c] == all[c] && j != 1)
			{
				printf("%d\n", j - 1);
				return 0;
			}
			else break;
		}
		for (k = 1; k <= n; k++)
			save1[k] = change[k];
		for (l = 1; l <= n; l++, k++)
			save2[l] = change[k];
		for (z = 1, x = 1, y = 1; z <= i; z++)
		{
			if (z % 2 == 0)
			{
				change[z] = save1[x];
				x++;
			}
			else
			{
				change[z] = save2[y];
				y++;
			}
		}
	}
}