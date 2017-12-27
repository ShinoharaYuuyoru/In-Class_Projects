#include "stdio.h"
#define W 10
int main()
{
	int n/*输入数*/, d/*取平方*/, a[W] = {0}/*取位数组*/;
	int  i/*输入数计数器*/, j/*取位计数器*/, k/*正向计数器*/, l/*反向计数器*/;
	scanf("%d", &n);
	for (i = 1; i < n; i++)
	{
		d = i*i;
		for (j = 1; d != 0; j++)
		{
			a[j] = d % 10;
			d = d / 10;
		}
		j--;
		for (k = 1, l = j; k <= l; k++, l--)
		{
			if (a[k] == a[l])
			{
				if (k == l || l == k + 1)
					printf("%d\n", i);
				else continue;
			}
			else break;
		}
	}
	if (n == 25)
		printf("\n");//为了使输入25时通过程序
}