#include "stdio.h"
#include "stdlib.h"

struct Line
{
	int P;
	int D;
}L[10005];

int comp(const void *a, const void *b);

int main()
{
	int n;
	int nc;
	int Ans = 0;
	int Day[10005] = { 0 };
	int Dayc;/*ÓÃÓÚËÑË÷Ìì*/

	scanf("%d", &n);
	for (nc = 0; nc < n; nc++)
	{
		scanf("%d", &L[nc].P);
	}
	for (nc = 0; nc < n; nc++)
	{
		scanf("%d", &L[nc].D);

	}

	qsort(L, n, sizeof(L[0]), comp);

	for (nc = 0; nc < n; nc++)
	{
		for (Dayc = L[nc].D - 1; Dayc >= 0; Dayc--)
		{
			if (Day[Dayc] == 0)
			{
				Day[Dayc] = 1;
				Ans = Ans + L[nc].P;
				break;
			}
		}
	}

	printf("%d\n", Ans);
}

int comp(const void *a, const void *b)
{
	struct Line *c = (struct Line*)a;
	struct Line *d = (struct Line*)b;

	if (c->P != d->P)
	{
		return d->P - c->P;
	}
	else
	{
		return c->D - d->D;
	}
}