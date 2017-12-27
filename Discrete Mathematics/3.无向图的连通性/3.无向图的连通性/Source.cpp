#include "stdio.h"

int N;
int MAP[3001][3001];
int LineC = 0;
int RowC = 0;

int main()
{
	scanf("%d", &N);

	for (LineC = 0;LineC < N;LineC++)
	{
		for (RowC = 0;RowC < N;RowC++)
		{
			scanf("%d", &MAP[LineC][RowC]);
		}
	}

	/*Warshall*/
	int Y, YX, X = 0;
	for (Y = 0;Y < N;Y++)
	{
		for (YX = 0;YX < N;YX++)
		{
			if (MAP[Y][YX] == 1)
			{
				for (X = 0;X < N;X++)
				{
					if (MAP[YX][X] == 1)
					{
						MAP[Y][X] = 1;
					}
				}
			}
		}
	}

	for (LineC = 0;LineC < N;LineC++)
	{
		for (RowC = LineC;RowC < N;RowC++)
		{
			if (MAP[LineC][RowC] == 0)
			{
				printf("no\n");

				return 0;
			}
		}
	}
	printf("yes\n");

	return 0;
}