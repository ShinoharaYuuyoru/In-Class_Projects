#include "stdio.h"
#include "stdlib.h"

int comp(const void *a, const void *b);

int main()
{
	int n;
	int nc;
	int checkin;
	int Q[10010] = { 0 };
	long long int ans = 0;
	int temp;

	scanf("%d", &n);

	for (nc = 0; nc < n; nc++)
	{
		scanf("%d", &Q[nc]);
	}

	if (n == 1)
	{
		printf("0\n");
		return 0;
	}

	qsort(Q, n, sizeof(Q[0]), comp);

	for (nc = 1; nc < n; nc++)
	{
		Q[nc] = Q[nc - 1] + Q[nc];
		ans = ans + Q[nc];

		for (checkin = nc; checkin < n - 1 && Q[checkin] > Q[checkin + 1]; checkin++)
		{
			temp = Q[checkin];
			Q[checkin] = Q[checkin + 1];
			Q[checkin + 1] = temp;
		}
	}

	printf("%lld\n", ans);
}

int comp(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}