#include "stdio.h"
int main()
{
	int n,i,a,h,s;
	scanf("%d", &n);
	for (i = n - 1, h = 1; i >= 1; i--, h++)
	{
		for (s=1;s<=n-h;s++)
		printf("  ");
		for (a = n; a >= n + 1 - h; a--)
			printf("%-2d", a);
		for (a = a + 2; a <= n; a++)
			printf("%-2d", a);
		printf("\n");
	}
	for (a = n; a >= 1; a--)
		printf("%-2d", a);
	for (a = a + 2; a <= n; a++)
		printf("%-2d", a);
	printf("\n");
	for (i = n - 1, h = 1; i >= 1; i--, h++)
	{
		for (s = n-1; s >= n - h; s--)
			printf("  ");
		for (a = n; a >= h+1; a--)
			printf("%-2d", a);
		for (a = a + 2; a <= n; a++)
			printf("%-2d", a);
		printf("\n");
	}
}