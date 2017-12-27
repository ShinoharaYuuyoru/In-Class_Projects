#include "stdio.h"
#define N 9
int match(int num1, int num2, int num3);
int main()
{
	int number/*开头数字*/,m1,m2,m3/*第一二三个三位数*/;
	int count1/*第一个三位数十位计数器*/,count2/*第一个三位数个位计数器*/,fin=0/*成功个数计数器*/;
	scanf("%d", &number);
	if (number >= 4)
	{
		printf("0,0,0\n");
		return 0;
	}
	for (count1 = 1; count1 <= 9; count1++)
	{
		if (count1 != number)//至此确定第一个三位数的十位
		{
			for (count2 = 1; count2 <= 9; count2++)
			{
				if (count2 != count1&&count2 != number)
				{
					m1 = number * 100 + count1 * 10 + count2;//至此确定m1
					m2 = m1 * 2;//确定m2
					m3 = m1 * 3;//确定m3
					if (match(m1, m2, m3) == 1)
					{
						printf("%d,%d,%d\n", m1, m2, m3);
						fin++;
					}
				}
				else
					continue;
			}
		}
		else
			continue;
	}
	if (fin==0)
		printf("0,0,0\n");
}
int match(int num1, int num2, int num3)
{
	int C[N]/*取三个三位数的每一位数列*/;
	int countC/*C数列下角标计数器*/;
	int i/*数字对比用计数器*/;
	for (countC = 0; countC <= 2; countC++)
	{
		C[countC] = num1 % 10;
		num1 = num1 / 10;
	}
	for (countC = 3; countC <= 5; countC++)
	{
		C[countC] = num2 % 10;
		num2 = num2 / 10;
	}	
	for (; countC <= 8; countC++)
	{
		C[countC] = num3 % 10;
		num3 = num3 / 10;
	}
	for (i = 1; i <= 9;)
	{
		for (countC = 0; countC <= 8; countC++)
		{
			if (C[countC] == i)
			{
				i++;
				break;
			}
			if (C[countC] != i&&countC == 8)
				return 0;
		}
		if (i == 10)
			return 1;
	}
}