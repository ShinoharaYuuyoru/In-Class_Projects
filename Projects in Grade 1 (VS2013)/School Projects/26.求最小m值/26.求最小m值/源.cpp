#include "stdio.h"
int main()
{
	int m, n, x;
	scanf("%d", &n);
	for (m = 1;; m++)
	{
		x = (1+m)*m / 2;
		if ((x > n&&x -m < n)||x==n)
		{
			printf("%d\n", m);
			break;
		}
	}
}