#include "stdio.h"
#include "stdlib.h"

int Program = 1;
int Physical = 1;
int Logical = 0;
int AreaNote;

void SolveDoubleB();
void SolveAt();
void SolveDoubleQ();
void SolveSingleQ();

int main()
{
	char temp;

	while (1)
	{
		scanf("%c", &temp);

		/*�жϳ���*/
		if (temp == '#')
		{
			scanf("%c", &temp);

			if (temp == '#')/*������ֹ*/
			{
				if (AreaNote == 1)
				{
					printf("Unterminated block comment at end of program.\n");
				}
				printf("Program %d contains %d logical lines and %d physical lines.\n", Program, Logical, Physical - 1);
				return 0;
			}
			else/*һ���������*/
			{
				if (AreaNote == 1)
				{
					printf("Unterminated block comment at end of program.\n");
				}
				printf("Program %d contains %d logical lines and %d physical lines.\n", Program, Logical, Physical - 1);

				Physical = 0;
				Logical = 0;
				Program++;
				AreaNote = 0;
			}
		}

		/*ע����*/
		if (temp == '(')
		{
			scanf("%c", &temp);

			if (temp == '(')
			{
				AreaNote = 1;
				SolveDoubleB();
			}
		}
		if (temp == '@')
		{
			SolveAt();
		}

		/*�ַ�����*/
		if (temp == '"')
		{
			SolveDoubleQ();
		}
		if (temp == '\'')
		{
			SolveSingleQ();
		}

		/*����������ֹ*/
		if (temp == ';')
		{
			Logical++;
		}

		/*��һ��*/
		if (temp == '\n')
		{
			Physical++;
		}
	}

	return 0;
}

void SolveDoubleB()
{
	char t;
	int flag = 0;

	for (;;)
	{
		scanf("%c", &t);

		if (t == ')')
		{
			flag++;
			if (flag == 2)
			{
				AreaNote = 0;
				return;
			}
		}
		if (t == '\n')
		{
			Physical++;
		}

		if (t == '#')
		{
			scanf("%c", &t);

			if (t == '#')/*������ֹ*/
			{
				if (AreaNote == 1)
				{
					printf("Unterminated block comment at end of program.\n");
				}
				printf("Program %d contains %d logical lines and %d physical lines.\n", Program, Logical, Physical - 1);
				exit(0);
			}
			else/*һ���������*/
			{
				if (AreaNote == 1)
				{
					printf("Unterminated block comment at end of program.\n");
				}
				printf("Program %d contains %d logical lines and %d physical lines.\n", Program, Logical, Physical - 1);

				Physical = 1;
				Logical = 0;
				Program++;
				AreaNote = 0;

				return;
			}
		}
	}
}

void SolveAt()
{
	char t;

	for (;;)
	{
		scanf("%c", &t);

		if (t == '\n')
		{
			Physical++;
			return;
		}
	}
}

void SolveDoubleQ()
{
	char t;

	for (;;)
	{
		scanf("%c", &t);

		if (t == '\n')
		{
			printf("Unterminated string in line %d.\n", Physical);
			Physical++;
			return;
		}
		if (t == '"')
		{
			return;
		}
	}
}

void SolveSingleQ()
{
	char t;

	for (;;)
	{
		scanf("%c", &t);

		if (t == '\n')
		{
			printf("Unterminated string in line %d.\n", Physical);
			Physical++;
			return;
		}
		if (t == '\'')
		{
			return;
		}
	}
}