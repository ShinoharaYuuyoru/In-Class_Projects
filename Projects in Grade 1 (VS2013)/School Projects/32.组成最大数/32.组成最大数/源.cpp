#include "stdio.h"
#define N 10
int main()
{
	int n, a[N], count, i, nc, j,k,save;
	scanf("%d", &n);
	nc = n;
	for (i = 0; nc != 0; i++)
		nc = (nc - nc % 10)/10;
	for (count = 0; count <= i; count++)
	{
		a[count] = n % 10;
		n = (n - n % 10) / 10;
	}
	count = count - 1;
	for (j = 1; j <= count - 1; j++)
	{
		for (k = 0; k <= count-1 - j; k++)
		if (a[k] < a[k + 1])
		{
			save = a[k];
			a[k] = a[k + 1];
			a[k + 1] = save;
		}
	}
	for (i = 0; i <= count - 1; i++)
		printf("%d", a[i]);
	printf("\n");
}