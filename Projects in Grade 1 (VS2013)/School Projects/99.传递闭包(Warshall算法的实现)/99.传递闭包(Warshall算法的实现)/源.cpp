#include "stdio.h"
#define N 20

int MTX[N][N];//�������

int main()
{
	char input;//������
	int line, row;//�С���
	int linec, rowc;//���м�����
	int delive;//����

	line = 1;
	row = 1;

	while (scanf("%c", &input) != EOF)//�������
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
	row = line;//ȷ�������С

	for (delive = 1; delive <= line; delive++)//����
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

	for (linec = 1; linec <= line; linec++)//���
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
