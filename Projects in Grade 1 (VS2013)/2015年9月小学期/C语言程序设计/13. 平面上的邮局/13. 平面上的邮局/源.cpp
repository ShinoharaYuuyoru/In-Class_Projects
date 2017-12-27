#include "stdio.h"
#include "stdlib.h"

int comp(const void *a, const void *b);

int main()
{
	int n;
	int nc;
	int x[100005];
	int y[100005];
	int ssmall, sbig;/*search small and big*/
	long long int ans = 0;

	scanf("%d", &n);

	for (nc = 0; nc < n; nc++)
	{
		scanf("%d%d", &x[nc], &y[nc]);
	}

	qsort(x, n, sizeof(int), comp);
	qsort(y, n, sizeof(int), comp);

	for (ssmall = 0, sbig = n - 1; ssmall <= sbig; ssmall++, sbig--)
	{
		ans = ans + (x[sbig] - x[ssmall]) + (y[sbig] - y[ssmall]);
	}

	printf("%lld\n", ans);
	return 0;
}

int comp(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}