#include "stdio.h"
#define N 100
int main()
{
	int i/*l1拼接计数器*/,j/*l2拼接计数器*/,sc/*输出计数器*/,m/*大排列计数器*/,n/*每一次排列计数器*/;
	char l1[N]/*第一次排列数组*/, l2[N]/*第二次排列数组*/, pr[N]/*最终输出数组*/,save/*临时寄存器*/;
	gets(l1);
	gets(l2);
	for (i = 0; l1[i] != '\0'; i++)
		pr[i] = l1[i];
	for (j = 0; l2[j] != '\0'; i++,j++)
		pr[i] = l2[j];
	i--;
	for (m = 1; m <= i; m++)
	{
		for (n = 0; n < i + 1 - m; n++)
		{
			if (pr[n] - ' ' >= pr[n + 1] - ' ')
			{
				save = pr[n];
				pr[n] = pr[n + 1];
				pr[n + 1] = save;
			}
		}
	}
	for (sc = 0; sc <= i; sc++)
		printf("%c", pr[sc]);
	printf("\n");
}