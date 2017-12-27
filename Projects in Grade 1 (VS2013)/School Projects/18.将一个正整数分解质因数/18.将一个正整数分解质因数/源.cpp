/*题目：将一个正整数分解质因数。例如：输入90,打印出90=2*3*3*5。*/
#include "stdio.h"
int main()
{
	int n, i;
	printf("\nplease input a number:\n");
	scanf("%d", &n);
	printf("%d=", n);
	for (i = 2; n>=i; i++)
	{
		while (n!=i)
		{
			if (n%i == 0)
			{
				printf("%d*", i);
				n = n / i;
			}
			else break;
		}
	}
	printf("%d", n);
}