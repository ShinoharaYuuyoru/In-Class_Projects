#include "stdio.h"

int N = 0;
int A[2002];
char Final[10000];
int Min[2002][2002];
int Solution[2002][2002];
int End = 0;

void MatrixChain();
void BestSolution(int i, int j);
void AddBracket(int Left, int Right);
void Print();

int main()
{
	scanf("%d", &N);
	End = N - 1;
	int Nc = 0;
	for (Nc = 0;Nc <= N;Nc++)
	{
		scanf("%d", &A[Nc]);
		Final[Nc] = 'A';
	}
	Final[Nc - 1] = '\0';

	if (N == 1)
	{
		printf("0\n(A1)\n");

		return 0;
	}

	MatrixChain();
	BestSolution(1, N);
	Print();

	return 0;
}

void MatrixChain()
{
	int i = 0;
	for (i = 1;i <= N;i++)
	{
		Min[i][i] = 0;
	}

	int r = 0;
	int j = 0;
	int k = 0;
	int t = 0;
	for (r = 2;r <= N;r++)
	{
		for (i = 1;i <= N - r + 1;i++)
		{
			j = i + r - 1;
			Min[i][j] = Min[i + 1][j] + A[i - 1] * A[i] * A[j];
			Solution[i][j] = i;

			for (k = i + 1;k < j;k++)
			{
				t = Min[i][k] + Min[k + 1][j] + A[i - 1] * A[k] * A[j];
				if (t < Min[i][j])
				{
					Min[i][j] = t;
					Solution[i][j] = k;
				}
			}
		}
	}

	return;
}

void BestSolution(int i, int j)
{
	if (i == j)
	{
		return;
	}

	BestSolution(i, Solution[i][j]);
	BestSolution(Solution[i][j] + 1, j);

	AddBracket(i, j);

	return;
}

void AddBracket(int Left, int Right)
{
	int ACounter = 0;
	int Search = 0;
	int Move = 0;
	int Step = 0;

	for (Search = 0;Search <= End;Search++)
	{
		if (Final[Search] == 'A')
		{
			ACounter++;
		}
		if (ACounter == Left)
		{
			for (Move = End + 1, Step = 1;Step <= End - Search + 1;Step++)
			{
				Final[Move] = Final[Move - 1];
				Move--;
			}
			Final[Search] = '(';
			End++;
			break;
		}
	}
	for (ACounter = 0;Search <= End;Search++)
	{
		if (Final[Search] == 'A')
		{
			ACounter++;
		}
		if (ACounter == Right - Left + 1)
		{
			Search++;
			for (Move = End + 1, Step = 1;Step <= End - Search + 1;Step++)
			{
				Final[Move] = Final[Move - 1];
				Move--;
			}
			Final[Search] = ')';
			End++;
			break;
		}
	}

	return;
}

void Print()
{
	printf("%d\n", Min[1][N]);

	int P = 0;
	int AddNumber = 1;
	
	for (P = 0;P <= End;P++)
	{
		if (Final[P] == 'A')
		{
			printf("A%d", AddNumber);
			AddNumber++;
		}
		else
		{
			printf("%c", Final[P]);
		}
	}
	printf("\n");

	return;
}