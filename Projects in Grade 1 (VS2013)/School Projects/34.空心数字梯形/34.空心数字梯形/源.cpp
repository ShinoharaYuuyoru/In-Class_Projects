#include "stdio.h"
int main()
{
	int n, m, countn, countm, endm, spacen, spacem;
	int countmc;//复制组
	scanf("%d%d", &n, &m);
	if (n % 2 == 0)
		endm = m + n - 2 + n / 2;//结束数确定
	else
		endm = m + n - 2 + n / 2 + 1;//结束数确定
	for (countn = 1,countm = m; countn <= n; countn++,countm++)
	{
		for (spacen = 1; spacen <= countn - 1; spacen++)
			printf("  ");//输出前置空格
		if ((countn == 1 || countn == n)&&n!=1)//判断第一行和最后一行
		{
			for (countmc = countm; countmc <= endm; countmc++)
			{
				printf("%-2d", countmc % 10);//输出升序数列
			}
			if (n % 2 == 0)//判断最大数字是否重复
			{
				for (countmc = countmc - 1; countmc >= m + 1; countmc--)//输出降序数列
				{
					if (countn == n&&countmc == endm - (n / 2)+1)
						break;
					printf("%-2d", countmc % 10);
				}
			}
			else
			for (countmc = countmc - 2; countmc >= m + 1; countmc--)//输出降序数列
			{
				if (countn == n&&countmc == endm - (n / 2))
					break;
				printf("%-2d", countmc % 10);
			}
			printf("%d\n", countmc%10);//输出最后一个数
		}
		else//当不是第一行和最后一行的时候的情况
		{
			if (n != 1)
			{
				printf("%d", countm % 10);
				if (n % 2 == 0)//输出空格
				for (spacem = 1; spacem <= (endm - m - 1) * 4 + 1 - (countn - 2) * 4; spacem++)
					printf(" ");
				else
				for (spacem = 1; spacem <= (endm - m - 2) * 4 + 3 - (countn - 2) * 4; spacem++)
					printf(" ");
				printf("%d\n", countm % 10);
			}
			else printf("%d\n", countm % 10);
		}
	}
}