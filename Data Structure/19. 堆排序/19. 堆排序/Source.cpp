#include "stdio.h"

int PrintCounter = 2;

void Swap(int *X, int *Y);
void BuildBigHeap(int *L, int All);
void HeapAdjust(int *L, int s, int m);
int WhichIsBigger(int x, int y);
void HeapSort(int *L, int All);

int main()
{
	int N = 0;
	int Line[1000] = { 0 };
	int NC = 0;

	scanf("%d", &N);

	for (NC = 1;NC <= N;NC++)
	{
		scanf("%d", &Line[NC]);
	}

	BuildBigHeap(Line, N);

	/*First Print*/
	int x = 0;
	for (x = 1;x <= N;x++)
	{
		printf("%d ", Line[x]);
	}
	printf("\n");
	/*First Print End*/

	HeapSort(Line, N);
}

void Swap(int *X, int *Y)//Swap two numbers
{
	int Temp;
	Temp = *X;
	*X = *Y;
	*Y = Temp;
}

void BuildBigHeap(int *L, int All)//Build First Small Heap
{
	int Root = 0;

	for (Root = All / 2;Root > 0;Root--)
	{
		HeapAdjust(L, Root, All);
	}
}

void HeapAdjust(int *L, int s, int m)//Adjust to be a small heap
{
	int Temp = 0;
	int Pointer = 0;

	Temp = L[s];
	for (Pointer = 2 * s ;Pointer <= m;Pointer = Pointer * 2)
	{
		if (Pointer < m && WhichIsBigger(L[Pointer], L[Pointer + 1]))//At left and right children, choose bigger one.
		{
			Pointer++;
		}

		if (WhichIsBigger(L[Pointer], Temp))//The child is bigger than root.
		{
			break;
		}
		else
		{
			L[s] = L[Pointer];
			s = Pointer;
		}
	}
	L[s] = Temp;
}

int WhichIsBigger(int x, int y)//x > y, return 1; else return 0.
{
	if (x > y)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void HeapSort(int *L, int All)//Based on Big Heap.
{
	int Last = 0;

	for (Last = All ;Last > 1;Last--)
	{
		Swap(&L[0], &L[Last]);

		HeapAdjust(L, 0, Last - 1);

		if (PrintCounter >= 1)//Adjust Print.
		{
			int x = 0;
			for (x = 1;x <= Last - 1;x++)
			{
				printf("%d ", L[x]);
			}
			printf("\n");

			PrintCounter--;
		}
	}
}