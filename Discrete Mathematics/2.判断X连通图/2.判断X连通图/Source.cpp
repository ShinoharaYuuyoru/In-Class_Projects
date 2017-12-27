#include "stdio.h"
#include "string.h"

int main()
{
	int N;
	int Y, X;
	int YX;
	int MAP[301][301];

	memset(MAP, -1, sizeof(MAP));

	scanf("%d", &N);

	for (Y = 1;Y <= N;Y++)
	{
		for (X = 1;X <= N;X++)
		{
			scanf("%d", &MAP[Y][X]);
		}
	}

	/*Warshall*/
	for (Y = 1;Y <= N;Y++)
	{
		for (YX = 1;YX <= N;YX++)
		{
			for (X = 1;X <= N;X++)
			{
				MAP[YX][X] = (MAP[YX][X]) || (MAP[YX][Y] && MAP[Y][X]);
			}
		}
	}
	
	for (Y = 1;Y <= N;Y++)
	{
		for (X = 1;X <= N;X++)
		{
			if (MAP[Y][X] == 1)
			{
				continue;
			}
			else
			{
				if (MAP[X][Y] == 1)
				{
					printf("2\n");
					return 0;
				}
				else
				{
					printf("3\n");
					return 0;
				}
			}
		}
	}
	printf("1\n");
}