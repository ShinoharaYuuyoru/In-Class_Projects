#include "stdio.h"
#include "stdlib.h"

char Command[200][257];
char SaveA = 48;
char SaveB = 48;
int CommandRow;
int CommandLine;

void LD();
void ST();
void SWP();
void ADD();
void INC();
void DEC();
void BZ();
void BR();
int HexToDec(char *T);

int main()
{
	for (CommandRow = 0;;CommandRow++)
	{
		scanf("%s", Command[CommandRow]);
		if (Command[CommandRow][0] == '8')
		{
			return 0;
		}

		for (CommandLine = 0;;)
		{
			if (Command[CommandRow][CommandLine] == '0')
			{
				LD();
			}
			if (Command[CommandRow][CommandLine] == '1')
			{
				ST();
			}
			if (Command[CommandRow][CommandLine] == '2')
			{
				SWP();
			}
			if (Command[CommandRow][CommandLine] == '3')
			{
				ADD();
			}
			if (Command[CommandRow][CommandLine] == '4')
			{
				INC();
			}
			if (Command[CommandRow][CommandLine] == '5')
			{
				DEC();
			}
			if (Command[CommandRow][CommandLine] == '6')
			{
				BZ();
			}
			if (Command[CommandRow][CommandLine] == '7')
			{
				BR();
			}
			if (Command[CommandRow][CommandLine] == '8')
			{
				SaveA = 48;
				SaveB = 48;
				break;
			}
		}

		printf("%s\n", Command[CommandRow]);
	}
}

void LD()
{
	char Temp[5];
	int ADDR;

	Temp[0] = Command[CommandRow][CommandLine + 1];
	Temp[1] = Command[CommandRow][CommandLine + 2];
	Temp[2] = '\0';

	ADDR = HexToDec(Temp);

	SaveA = Command[CommandRow][ADDR];

	CommandLine = CommandLine + 3;

	return;
}
void ST()
{
	char Temp[5];
	int ADDR;

	Temp[0] = Command[CommandRow][CommandLine + 1];
	Temp[1] = Command[CommandRow][CommandLine + 2];
	Temp[2] = '\0';

	ADDR = HexToDec(Temp);

	Command[CommandRow][ADDR] = SaveA;

	CommandLine = CommandLine + 3;

	return;
}
void SWP()
{
	char T;
	
	T = SaveA;
	SaveA = SaveB;
	SaveB = T;

	CommandLine++;

	return;
}
void ADD()
{
	int ADD;

	if (SaveA <= 57)
	{
		SaveA = SaveA - 48;
	}
	else
	{
		SaveA = SaveA - 55;
	}
	if (SaveB <= 57)
	{
		SaveB = SaveB - 48;
	}
	else
	{
		SaveB = SaveB - 55;
	}
	ADD = SaveA + SaveB;

	SaveA = ADD % 16;
	if (SaveA >= 10)
	{
		SaveA = SaveA + 55;
	}
	else
	{
		SaveA = SaveA + 48;
	}
	
	SaveB = ADD / 16;
	if (SaveB >= 10)
	{
		SaveB = SaveB + 55;
	}
	else
	{
		SaveB = SaveB + 48;
	}

	CommandLine++;

	return;
}
void INC()
{
	SaveA++;

	if (SaveA == 58)
	{
		SaveA = 65;
	}
	if (SaveA == 71)
	{
		SaveA = 48;
	}

	CommandLine++;
	return;
}
void DEC()
{
	SaveA--;

	if (SaveA == 47)
	{
		SaveA = 70;
	}
	if (SaveA == 64)
	{
		SaveA = 57;
	}

	CommandLine++;

	return;
}
void BZ()
{
	if (SaveA == 48)
	{
		char Temp[5];

		Temp[0] = Command[CommandRow][CommandLine + 1];
		Temp[1] = Command[CommandRow][CommandLine + 2];
		Temp[2] = '\0';

		CommandLine = HexToDec(Temp);

		return;
	}
	else
	{
		CommandLine = CommandLine + 3;

		return;
	}
}
void BR()
{
	char Temp[5];

	Temp[0] = Command[CommandRow][CommandLine + 1];
	Temp[1] = Command[CommandRow][CommandLine + 2];
	Temp[2] = '\0';

	CommandLine = HexToDec(Temp);

	return;
}

int HexToDec(char *T)
{
	int Tc;
	int ANS = 0;

	for (Tc = 0;T[Tc] != '\0';Tc++)
	{
		ANS = ANS * 16;
		
		if (T[Tc] <= 57)
		{
			ANS = ANS + T[Tc] - 48;
		}
		if (T[Tc] >= 65)
		{
			ANS = ANS + T[Tc] - 55;
		}
	}

	return ANS;
}