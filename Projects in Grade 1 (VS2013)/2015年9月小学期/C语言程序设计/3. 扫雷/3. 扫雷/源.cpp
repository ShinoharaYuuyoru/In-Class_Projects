#include "stdio.h"

char Field[105][105];
int N, M;

int Scan(int y, int x);

int main()
{
	int Count = 1;
	int Nc, Mc;

	while (1)
	{
		scanf("%d%d", &N, &M);
		getchar();//³·Ïúµô\n

		if (N == 0)
		{
			return 0;
		}
		else
		{
			if (Count > 1)
			{
				printf("\n");
			}

			for (Nc = 0; Nc < N; Nc++)
			{
				gets(Field[Nc]);
			}
		}

		for (Nc = 0; Nc < N; Nc++)
		{
			for (Mc = 0; Mc < M; Mc++)
			{
				if (Field[Nc][Mc] == '*')
				{
					continue;
				}
				else
				{
					Field[Nc][Mc] = Scan(Nc, Mc) + 48;
				}
			}
		}

		printf("Field #%d:\n", Count);
		for (Nc = 0; Nc < N; Nc++)
		{
			printf("%s\n", Field[Nc]);
		}

		Count++;
	}
}

int Scan(int y,int x)
{
	int num = 0;

	if (y - 1 >= 0)
	{
		if (x - 1 >= 0 && Field[y - 1][x - 1] == '*')
		{
			num++;
		}
		if (Field[y - 1][x] == '*')
		{
			num++;
		}
		if (x + 1 < M && Field[y - 1][x + 1] == '*')
		{
			num++;
		}
	}
	
	if (x - 1 >= 0 && Field[y][x - 1] == '*')
	{
		num++;
	}
	if (x + 1 < M && Field[y][x + 1] == '*')
	{
		num++;
	}

	if (y + 1 < N)
	{
		if (x - 1 >= 0 && Field[y + 1][x - 1] == '*')
		{
			num++;
		}
		if (Field[y + 1][x] == '*')
		{
			num++;
		}
		if (x + 1 < M && Field[y + 1][x + 1] == '*')
		{
			num++;
		}
	}

	return num;
}