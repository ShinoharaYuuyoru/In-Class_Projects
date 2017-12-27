#include "stdio.h"

void BubbleSort(int *Line, int q, int r);
void Swap(int *A, int l, int r);
int Partition(int* Line, int p, int r, int x);
int Select(int *Line, int p, int r, int k);

int Pot[2000001];
int FFF = 0;

int main()
{
	int X, Y;
	int Number = 0;
	int ANS = 0;

	while (scanf("%d,%d", &X, &Y) != EOF)
	{
		Pot[Number] = Y;
		Number++;
	}

	int Mid;
	if (Number % 2 == 0)
	{
		Mid = Number / 2;
	}
	else
	{
		Mid = Number / 2 + 1;
	}
	ANS = Select(Pot, 0, Number -1, Mid);
	printf("%d\n", ANS);

	return 0;
}

void BubbleSort(int *Line, int q, int r)
{
	int i, j, Temp;

	for (j = 1;j <= r-q ; j++)
	{
		for (i = q;i < r -j+1;i++)
		{
			if (Line[i] > Line[i + 1])
			{
				Temp = Line[i];
				Line[i] = Line[i + 1];
				Line[i + 1] = Temp;
			}
		}
	}
}

void Swap(int *A, int l,int r)
{
	int Temp;
	Temp = A[l];
	A[l] = A[r];
	A[r] = Temp;

	return;
}

int Partition(int* Line, int p, int r, int k)
{
	int i = p;
	int j = r + 1;
	int x = Line[p];

	while (1)
	{
		while (Line[++i] < x&&i < r);
		while (Line[--j] > x);
		if (i >= j)
		{
			break;
		}
		Swap(Line,i, j);
	}
	Line[p] = Line[j];
	Line[j] = x;

	return j;
}

int Select(int *Line, int p, int r, int k)
{
	if (r - p < 75)
	{
		BubbleSort(Line, p, r);

		return Line[p + k - 1];
	}
	int i = 0;
	for (i = 0;i <= (r - p - 4) / 5;i++)
	{
		BubbleSort(Line, p + 5 * i, p + 5 * i + 4);
		Swap(Line, p + 5 * i + 2, p + i);
	}

	int x = Select(Line, p, p + (r - p - 4) / 5, (r - p - 4) / 10);
	i = Partition(Line, p, r, x);
	int j = i - p + 1;
	if (k <= j)
	{
		return Select(Line, p, i, k);
	}
	else
	{
		return Select(Line, i + 1, r, k - j);
	}
}