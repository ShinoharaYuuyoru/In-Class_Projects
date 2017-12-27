#include "stdio.h" 
#include "stdlib.h" 

typedef struct Member
{
	struct Member *Right;
	int Num;
	struct Member *Left;
}Mem;/*顺时针方向，即右为前一位，左为后一位*/

Mem *Head;
Mem *LeftCheck;
Mem *RightCheck;

void Creat(int n);
void CheckCount(int m);
void Out_and_Print(int Flag);

int main()
{
	int n, k, m;

	scanf("%d,%d,%d", &n, &k, &m);

	if (n == 0 || m == 0 || k == 0)
	{
		printf("n,m,k must bigger than 0.\n");
		return 0;
	}
	if (k > n)
	{
		printf("k should not bigger than n.\n");
		return 0;
	}

	Head = (Mem*)malloc(sizeof(Mem));
	Head->Right = NULL;
	Head->Num = -1;
	Head->Left = NULL;

	Creat(n);

	LeftCheck = Head->Left;
	RightCheck = Head->Left;
	for (;;LeftCheck = LeftCheck->Left, RightCheck = RightCheck->Left)
	{
		if (LeftCheck->Num == k&&RightCheck->Num == k)
		{
			break;
		}
	}

	while (1)
	{
		CheckCount(m);

		if (LeftCheck == RightCheck)//Same 
		{
			Out_and_Print(1);
		}
		else
		{
			Out_and_Print(0);
		}

		if (Head->Left == NULL)//ALL is over. 
		{
			break;
		}
	}
	printf("\n");
}

void Creat(int n)
{
	int nc;
	Mem *ADD;
	Mem *Last;

	for (nc = 1;nc <= n;nc++)
	{
		if (nc == 1)//The First Node 
		{
			ADD = (Mem*)malloc(sizeof(Mem));
			Head->Left = ADD;
			ADD->Right = ADD;
			ADD->Num = 1;
			ADD->Left = ADD;

			Last = ADD;
		}
		else
		{
			ADD = (Mem*)malloc(sizeof(Mem));
			ADD->Left = Head->Left;
			ADD->Num = nc;
			ADD->Right = Last;

			Last->Left = ADD;
			Head->Left->Right = ADD;
			Last = ADD;
		}
	}
}

void CheckCount(int m)
{
	for (m = m - 1;m >= 1;m--)
	{
		LeftCheck = LeftCheck->Left;
		RightCheck = RightCheck->Right;
	}
}

void Out_and_Print(int Flag)//1 is same, 0 is diffrent. 
{
	Mem *Delete;

	if (Flag == 1)
	{
		Delete = LeftCheck;
		LeftCheck = Delete->Left;
		RightCheck = Delete->Right;

		if (Delete == Head->Left)
		{
			Head->Left = LeftCheck;
		}
		RightCheck->Left = LeftCheck;
		LeftCheck->Right = RightCheck;

		printf("%d", Delete->Num);
		if (LeftCheck == Delete&&RightCheck == Delete)//The last one. 
		{
			Head->Left = NULL;
		}
		free(Delete);
		printf(",");
	}
	else
	{
		Delete = LeftCheck;
		LeftCheck = Delete->Left;

		if (Delete == Head->Left)
		{
			Head->Left = LeftCheck;
		}
		LeftCheck->Right = Delete->Right;
		Delete->Right->Left = LeftCheck;

		printf("%d", Delete->Num);
		free(Delete);
		printf("-");
		/*Left Delete Over*/

		if (LeftCheck->Left == RightCheck->Right&&LeftCheck->Right == RightCheck->Left&&LeftCheck == RightCheck)//Two, and one is out. 
		{
			return;
		}
		else
		{
			Delete = RightCheck;
			RightCheck = Delete->Right;

			if (Delete == Head->Left)
			{
				Head->Left = Delete->Left;
			}
			RightCheck->Left = Delete->Left;
			Delete->Left->Right = RightCheck;

			printf("%d", Delete->Num);
			free(Delete);
			printf(",");
			/*Left Delete Over*/
		}
	}
}