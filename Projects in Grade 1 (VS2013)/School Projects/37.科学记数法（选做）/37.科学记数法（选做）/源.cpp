#include "stdio.h"
#define W 1000//位数
int main()
{
	int n/*幂*/;
	int i/*原始数据输入位数计数器*/,j/*eorE计数器*/,k/*换位计数器*/,l/*输出计数器*/,m/*换位次数计数器*/,o/*换位位数计数器*/;
	char num[W]/*原始数据*/, e/*判断字符eorE*/;
	char save/*临时存储器*/;
	for (i = 0; i <= W; i++)
		num[i] = '0';
	for (i = 1; num[i-1] != ' '; i++)
		scanf("%c", &num[i]);
	num[i - 1] = '\0';
	i = i - 2;/*原始数据录入完毕*/
	for (;;)
	{
		scanf("%c", &e);
		if (e != ' ')
			break;
	}
	scanf("%d", &n);
	if (n == 0)
	{
		for (i = 1; i <= 10; i++)
			printf("%c", num[i]);/*当n=0时，输出原始数据的前10位*/
	}
	if (n > 0)
	{
		save = num[2];
		for (i = 2, k = 1; k <= n; i++, k++)
		{
			num[i] = num[i + 1];
		}
		num[i] = '.';
		for (i++; i <= W; i++)
			num[i] = '0';
		for (l = 1; l <= i+8; l++)
			printf("%c", num[l]);
	}/*n>0时输出完毕*/
	if (n < 0)
	{
		n = 0 - n;
		for (i = 2; num[i] != '\0'; i++)
		{
			num[i] = num[i + 1];
		}
		for (m = 1; m <= n; m++)
		{
			for (o = 1; num[o] != '\0';o++)
			for (; o >= 1; o--)
			{
				num[o + 1] = num[o];
			}
		}
		num[1] = '.';
		for (i = 2; i <= n; i++)
			num[i] = '0';
		for (i = 0; num[i] != '\0'; i++)
			printf("%s", num[i]);
	}
}