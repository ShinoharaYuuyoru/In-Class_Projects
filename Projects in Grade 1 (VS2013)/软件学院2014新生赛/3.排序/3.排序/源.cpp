#include "stdio.h"
#define N 2003

int main()
{
	int temp;
	int tempc;
	int line[N];
	int x, y;
	int num = 0;

	while (scanf("%d", &temp) != EOF)
	{
		num = 0;

		for (tempc = 0; tempc < N; tempc++)
		{
			line[tempc] = 0;
		}
		
		for (tempc = 1; tempc <= temp; tempc++)
		{
			scanf("%d", &line[tempc]);
		}

		for (x = 1; x < temp; x++)
		{
			for (y = x + 1; y <= temp; y++)
			{
				if (line[x]<line[y] && line[line[x]]>line[line[y]] || line[x]>line[y] && line[line[x]] < line[line[y]])
				{
					num++;
				}
			}
		}

		printf("%d\n", num % 1000000007);
	}
}