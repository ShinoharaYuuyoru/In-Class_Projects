#include "stdio.h"
#include "stdlib.h"

int M3[100] = { 0 };
int M3C = 0;

void InsertSort(int *L, int Low, int High);
void Swap(int *X, int *Y);
int Pivot(int *L, int Low, int High);
//int PivotKeyPartition(int *L, int Low, int High);
void QuickSort(int *L, int Low, int High);
//void Median3(int *L, int All);
void Print(int *L, int All);

int main()
{
	int N = 0;
	char Temp[1000];
	int Line[10000] = { 0 };

	for (N = 1;;N++)
	{
		scanf("%s", Temp);

		if (Temp[0] == '#')
		{
			N--;
			break;
		}
		else
		{
			Line[N - 1] = atoi(Temp);
		}
	}

	QuickSort(Line, 0, N - 1);

	Print(Line, N);
	printf("Median3 Value:\n");
	if (M3C == 0)
	{
		printf("none\n");
	}
	else
	{
		int M3P = 0;
		for (M3P = 0;M3P < M3C;M3P++)
		{
			printf("%d ", M3[M3P]);
		}
		printf("\n");
	}

	return 0;
}

void InsertSort(int *L,int Low, int High)//Direct Insert
{
	int Sort[10000] = { 0 };
	int Catch = Low;
	int Search = 0;

	for (Catch = Low;Catch <= High;Catch++)
	{
		for (Search = 0;Search <= (Catch - Low);Search++)
		{
			if (Sort[Search] > L[Catch])
			{
				int Move = 0;
				for (Move = Catch - 1;Move >= Search;Move--)
				{
					Sort[Move + 1] = Sort[Move];
				}
				Sort[Search] = L[Catch];

				break;
			}
			else
			{
				continue;
			}
		}
		if (Search > (Catch - Low))
		{
			Sort[Search - 1] = L[Catch];
		}
	}

	for (Catch = Low, Search = 0;Catch <= High;Catch++,Search++)
	{
		L[Catch] = Sort[Search];
	}
}

void Swap(int *X, int *Y)//Swap two numbers
{
	int Temp;
	Temp = *X;
	*X = *Y;
	*Y = Temp;
}

int Pivot(int *L, int Low, int High)//Confirm the first PivotKey
{
	int Center = (Low + High) / 2;

	if (L[Low] > L[Center])
	{
		Swap(&L[Low], &L[Center]);
	}
	if (L[Low] > L[High])
	{
		Swap(&L[Low], &L[High]);
	}
	if (L[Center] > L[High])
	{
		Swap(&L[Center], &L[High]);
	}

	Swap(&L[Center], &L[High - 1]);

	return L[High - 1];
}

//int PivotKeyPartition(int *L, int Low, int High)//Search new PivotKey Partition and change with QuickSort's rules during QuickSorting
//{
//	int PivotKey = L[Low];
//
//	while (Low < High)
//	{
//		while (Low < High&&L[High] >= PivotKey)
//		{
//			High--;
//		}
//		L[Low] = L[High];
//
//		while (Low < High&&L[Low] <= PivotKey)
//		{
//			Low++;
//		}
//		L[High] = L[Low];
//	}
//	L[Low] = PivotKey;
//
//	return Low;
//}

//void QuickSort(int *L,int Low, int High)//QuickSort
//{
//	if (Low < High)
//	{
//		if (High - Low + 1 <= 5)
//		{
//			InsertSort(L, Low, High);
//		}
//		else
//		{
//			int PivotLocation = PivotKeyPartition(L, Low, High);
//
//			QuickSort(L, Low, PivotLocation - 1);
//			QuickSort(L, PivotLocation + 1, High);
//		}
//	}
//}

void QuickSort(int *L, int Low, int High)//Use Median 3 solution(include QuickSort) to sort
{
	if (High - Low + 1 > 5)
	{
		int PivotKey = 0;

		PivotKey = Pivot(L, Low, High);
		M3[M3C] = PivotKey;
		M3C++;

		/*Exchange*/
		int Left = Low + 1;
		int Right = High - 2;//(All - 2) links to PivotKey

		while (1)
		{
			while (L[Left] <= PivotKey&&Left <= High)
			{
				Left++;
			}
			while (L[Right] > PivotKey&&Right >= 0)
			{
				Right--;
			}

			if (Left < Right)
			{
				Swap(&L[Left], &L[Right]);
			}
			else
			{
				break;
			}
		}
		/*Exchange End*/

		Swap(&L[Left], &L[High - 1]);

		QuickSort(L, Low, Left - 1);
		QuickSort(L, Left + 1, High);
	}
	else
	{
		InsertSort(L, Low, High);
	}
}

void Print(int *L,int All)//Print
{
	int PrintCounter = 0;
	
	printf("After Sorting:\n");
	for (PrintCounter = 0;PrintCounter < All;PrintCounter++)
	{
		printf("%d ", L[PrintCounter]);
	}
	printf("\n");
}