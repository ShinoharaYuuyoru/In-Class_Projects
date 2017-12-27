#include "stdio.h"
#include "string.h"

char Dic[400][205];
int Dicc;
char Secr[205];
char Table[2][27];
int TableC;

int OP();
void CHANGE();

int main()
{
	int N;
	char Temp[205];
	char *END;

	for (TableC = 0; TableC < 26; TableC++)
	{
		Table[0][TableC] = 97 + TableC;
	}
	Table[0][TableC] = '\0';

	scanf("%d", &N);
	getchar();

	gets(Secr);
	getchar();

	while (N >= 1)
	{
		END = gets(Temp);

		if (END == NULL)
		{
			Dic[Dicc][0] = '\0';
			if (OP())
			{
				CHANGE();
				for (Dicc = 0; Dic[Dicc][0] != '\0'; Dicc++)
				{
					printf("%s\n", Dic[Dicc]);
				}
			}
			else
			{
				printf("No solution.\n");
			}
			return 0;
		}

		strcpy(Dic[Dicc], Temp);
		Dicc++;
		if (Temp[0] == '\0')
		{
			if (OP())
			{
				CHANGE();
				for (Dicc = 0; Dic[Dicc][0] != '\0'; Dicc++)
				{
					printf("%s\n", Dic[Dicc]);
				}
			}
			else
			{
				printf("No solution.\n");
			}
			printf("\n");

			Dicc = 0;
			for (TableC = 0; TableC < 26; TableC++)
			{
				Table[1][TableC] = '\0';
			}
			N--;
		}
	}
}

int OP()
{
	int check;

	for (Dicc = 0; Dic[Dicc][0] != '\0'; Dicc++)
	{
		if (strlen(Secr) == strlen(Dic[Dicc]))
		{
			for (check = 0; Secr[check] != '\0'; check++)
			{
				if (Secr[check] == ' ')
				{
					if (Dic[Dicc][check] == ' ')
					{
						continue;
					}
					else
					{
						break;
					}
				}
				else
				{
					if (Dic[Dicc][check] == ' ')
					{
						break;
					}
				}
				if (Table[1][Secr[check] - 97] == '\0')
				{
					for (TableC = 0; TableC < 26; TableC++)
					{
						if (Table[1][TableC] == Dic[Dicc][check])
						{
							for (TableC = 0; TableC < 26; TableC++)
							{
								Table[1][TableC] = '\0';
							}
							goto k;
						}
					}
					Table[1][Secr[check] - 97] = Dic[Dicc][check];
				}
				else
				{
					if (Table[1][Secr[check] - 97] != Dic[Dicc][check])
					{
						for (TableC = 0; TableC < 26; TableC++)
						{
							Table[1][TableC] = '\0';
						}
						break;
					}
				}
			}
		}
		if (strlen(Table[1]) == 26)
		{
			return 1;
		}
	k:;
	}

	if (strlen(Table[1]) < 26)
	{
		return 0;
	}
}

void CHANGE()
{
	int change = 0;
	int searchTable = 0;

	for (Dicc = 0; Dic[Dicc][0] != '\0'; Dicc++)
	{
		for (change = 0; Dic[Dicc][change] != '\0'; change++)
		{
			for (searchTable = 0; searchTable < 26; searchTable++)
			{
				if (Dic[Dicc][change] == Table[1][searchTable])
				{
					Dic[Dicc][change] = Table[0][searchTable];
					break;
				}
			}
		}
	}
}