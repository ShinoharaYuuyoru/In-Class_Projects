#include "stdio.h"
#define N 100
int main()
{
	char in[N]/*输入字符串*/;
	int i/*in数组逐个计数器*/, j/*ou数组逐个计数器*/,m/*判断重复计数器*/, ot/*输出计数器*/, ou[N]/*输出整型*/;
	scanf("%s", &in);
	ou[0] = in[0]-' '+32;
	j = 0;
	for (i = 1; in[i] != '\0'; i++)
	{
		for (m = 0; m <= j; m++)
		{
			if (in[i] - ' ' + 32 != ou[m])
			{
				if (m == j)
				{
					ou[j + 1] = in[i] - ' ' + 32;
					j++;
					break;
				}
			}
			if (in[i] - ' ' + 32 == ou[m])
				break;
		}
	}
	for (ot = 0; ot <= j;ot++)
	printf("%c", ou[ot]);
	printf("\n");
}