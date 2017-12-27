#include "stdio.h"
int main()
{
	int n,x,i,a;
	scanf("%d", &n);
	x = n*n;
	for (i = 1, a = 1; i <= x; i++)
	{
		printf("%3d", i);
		if (i == a*n)
		{
			printf("\n");
			a++;
		}
	}
}