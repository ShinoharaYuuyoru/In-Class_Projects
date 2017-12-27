#include "stdio.h"
#define N 20

int MTX[N][N];//输入矩阵

int main()
{
	char input;//输入检测
	int line, row;//行、列
	int linec, rowc;//行列计数器
	int delive;//传递

	line = 1;
	row = 1;

	while (scanf("%c", &input) != EOF)//输入完毕
	{
		if (input == '\n')
		{
			line++; 
			row = 1;
		}
		if (input == ' ')
		{
			continue;
		}
		if (input == '0' || input == '1')
		{
			MTX[line][row] = input - 48;
			row++;
		}
	}

	line--;
	row = line;//确定矩阵大小

	for (delive = 1; delive <= line; delive++)//处理
	{
		for (linec = 1; linec <= line; linec++)
		{
			if (MTX[linec][delive] == 1)
			{
				for (rowc = 1; rowc <= row; rowc++)
				{
					if (MTX[linec][rowc] == 0 && MTX[delive][rowc] == 0)
					{
						MTX[linec][rowc] = 0;
					}
					else
					{
						MTX[linec][rowc] = 1;
					}
				}
			}
		}
	}

	for (linec = 1; linec <= line; linec++)//输出
	{
		for (rowc = 1; rowc <= row; rowc++)
		{
			if (rowc < row)
			{
				printf("%d ", MTX[linec][rowc]);
			}
			else
			{
				printf("%d\n", MTX[linec][rowc]);
			}
		}
	}
}
