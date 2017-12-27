#include "stdio.h"
#include "stdlib.h"

struct Ex
{
	int Flag;/*0 is Op, 1 is Num, 2 is default*/
	char Op;
	int Num;
}Expr[85];/*Stack*/
int Point = 0;

void OPStack();

int main()
{
	int N;
	char Temp[10];
	int TempC = 0;
	char T;/*Judge minus number or a minus Op*/
	int number;/*Get the int number*/

	scanf("%d", &N);
	getchar();/*去掉\n*/

	for (Point = 0; Point < 85; Point++)
	{
		Expr[Point].Flag = 2;
		Expr[Point].Num = 0;
		Expr[Point].Op = '\0';
	}
	Point = 0;

	while (N >= 1)
	{
		T = getchar();
		if (T == ' ')
		{
			continue;
		}
		if (T == '+' || T == '*')
		{
			Expr[Point].Flag = 0;
			Expr[Point].Op = T;
			Point++;
			continue;
		}
		if (T == '-')
		{
			T = getchar();
			if (T == ' ')/*Is a Op*/
			{
				Expr[Point].Flag = 0;
				Expr[Point].Op = '-';
				Point++;
			}
			else/*Is a minus number*/
			{
				Temp[0] = '-';
				Temp[1] = T;
				for (TempC = 2;; TempC++)
				{
					T = getchar();
					if (T == ' ' || T == '\n')
					{
						Temp[TempC] = '\0';
						number = atoi(Temp);
						Expr[Point].Flag = 1;
						Expr[Point].Num = number;
						OPStack();
						Point++;
						break;
					}
					else
					{
						Temp[TempC] = T;
					}
				}
			}
		}
		if (T >= 48 && T <= 57)
		{
			Temp[0] = T;
			for (TempC = 1;; TempC++)
			{
				T = getchar();
				if (T == ' ' || T == '\n')
				{
					Temp[TempC] = '\0';
					number = atoi(Temp);
					Expr[Point].Flag = 1;
					Expr[Point].Num = number;
					OPStack();
					Point++;
					break;
				}
				else
				{
					Temp[TempC] = T;
				}
			}
		}
		if (T == '\n')
		{
			printf("%d\n", Expr[0].Num);
			N--;

			for (Point = 0; Point < 85; Point++)
			{
				Expr[Point].Flag = 2;
				Expr[Point].Num = 0;
				Expr[Point].Op = '\0';
			}
			Point = 0;
			TempC = 0;
		}
	}
}

void OPStack()/*注意在出栈的时候的初始化*/
{
	while (Point >= 2)
	{
		if (Expr[Point - 1].Flag == 1)/*如果前一个是数*/
		{
			if (Expr[Point - 2].Op == '+')
			{
				Expr[Point - 2].Flag = 1;
				Expr[Point - 2].Num = Expr[Point].Num + Expr[Point - 1].Num;
				Point = Point - 2;
				continue;
			}
			if (Expr[Point - 2].Op == '-')
			{
				Expr[Point - 2].Flag = 1;
				Expr[Point - 2].Num = Expr[Point - 1].Num - Expr[Point].Num;
				Point = Point - 2;
				continue;
			}
			if (Expr[Point - 2].Op == '*')
			{
				Expr[Point - 2].Flag = 1;
				Expr[Point - 2].Num = Expr[Point].Num * Expr[Point - 1].Num;
				Point = Point - 2;
				continue;
			}
		}
		if (Expr[Point - 1].Flag == 0)
		{
			return;
		}
	}
}