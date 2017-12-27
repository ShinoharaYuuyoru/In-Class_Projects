#include "stdio.h"
#include "string.h"
#include "stdlib.h"

char Cube[55];
char Cubecpy[55];

void U();
void R();
void F();
void D();
void L();
void B();
void X();
void Y();
void Z();

int main()
{
	int CubeReset;
	char input;

	for (CubeReset = 0; CubeReset < 54; CubeReset++)
	{
		Cube[CubeReset] = 65 + CubeReset;
		Cubecpy[CubeReset] = 65 + CubeReset;
	}

	for (;;)
	{
		input = getchar();
		if (input == '\n')
		{
			break;
		}

		if (input == 'U')
		{
			U();
		}
		if (input == 'u')
		{
			U();
			U();
			U();
		}
		if (input == 'R')
		{
			R();
		}
		if (input == 'r')
		{
			R();
			R();
			R();
		}
		if (input == 'F')
		{
			F();
		}
		if (input == 'f')
		{
			F();
			F();
			F();
		}
		if (input == 'D')
		{
			D();
		}
		if (input == 'd')
		{
			D();
			D();
			D();
		}
		if (input == 'L')
		{
			L();
		}
		if (input == 'l')
		{
			L();
			L();
			L();
		}
		if (input == 'B')
		{
			B();
		}
		if (input == 'b')
		{
			B();
			B();
			B();
		}
		if (input == 'X')
		{
			X();
		}
		if (input == 'x')
		{
			X();
			X();
			X();
		}
		if (input == 'Y')
		{
			Y();
		}
		if (input == 'y')
		{
			Y();
			Y();
			Y();
		}
		if (input == 'Z')
		{
			Z();
		}
		if (input == 'z')
		{
			Z();
			Z();
			Z();
		}
	}
	if (strcmp(Cube, Cubecpy) == 0)
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}
}

void U()
{
	char temp1, temp2;
	
	temp1 = Cubecpy[2];
	Cubecpy[2] = Cubecpy[0];
	temp2 = Cubecpy[8];
	Cubecpy[8] = temp1;
	temp1 = Cubecpy[6];
	Cubecpy[6] = temp2;
	Cubecpy[0] = temp1;

	temp1 = Cubecpy[5];
	Cubecpy[5] = Cubecpy[1];
	temp2 = Cubecpy[7];
	Cubecpy[7] = temp1;
	temp1 = Cubecpy[3];
	Cubecpy[3] = temp2;
	Cubecpy[1] = temp1;

	temp1 = Cubecpy[36];
	Cubecpy[36] = Cubecpy[9];
	temp2 = Cubecpy[27];
	Cubecpy[27] = temp1;
	temp1 = Cubecpy[18];
	Cubecpy[18] = temp2;
	Cubecpy[9] = temp1;

	temp1 = Cubecpy[37];
	Cubecpy[37] = Cubecpy[10];
	temp2 = Cubecpy[28];
	Cubecpy[28] = temp1;
	temp1 = Cubecpy[19];
	Cubecpy[19] = temp2;
	Cubecpy[10] = temp1;

	temp1 = Cubecpy[38];
	Cubecpy[38] = Cubecpy[11];
	temp2 = Cubecpy[29];
	Cubecpy[29] = temp1;
	temp1 = Cubecpy[20];
	Cubecpy[20] = temp2;
	Cubecpy[11] = temp1;
}

void R()
{
	char temp1, temp2;

	temp1 = Cubecpy[11];
	Cubecpy[11] = Cubecpy[9];
	temp2 = Cubecpy[17];
	Cubecpy[17] = temp1;
	temp1 = Cubecpy[15];
	Cubecpy[15] = temp2;
	Cubecpy[9] = temp1;

	temp1 = Cubecpy[14];
	Cubecpy[14] = Cubecpy[10];
	temp2 = Cubecpy[16];
	Cubecpy[16] = temp1;
	temp1 = Cubecpy[12];
	Cubecpy[12] = temp2;
	Cubecpy[10] = temp1;

	temp1 = Cubecpy[18];
	Cubecpy[18] = Cubecpy[6];
	temp2 = Cubecpy[47];
	Cubecpy[47] = temp1;
	temp1 = Cubecpy[44];
	Cubecpy[44] = temp2;
	Cubecpy[6] = temp1;

	temp1 = Cubecpy[21];
	Cubecpy[21] = Cubecpy[7];
	temp2 = Cubecpy[46];
	Cubecpy[46] = temp1;
	temp1 = Cubecpy[41];
	Cubecpy[41] = temp2;
	Cubecpy[7] = temp1;

	temp1 = Cubecpy[24];
	Cubecpy[24] = Cubecpy[8];
	temp2 = Cubecpy[45];
	Cubecpy[45] = temp1;
	temp1 = Cubecpy[38];
	Cubecpy[38] = temp2;
	Cubecpy[8] = temp1;
}

void F()
{
	char temp1, temp2;

	temp1 = Cubecpy[38];
	Cubecpy[38] = Cubecpy[36];
	temp2 = Cubecpy[44];
	Cubecpy[44] = temp1;
	temp1 = Cubecpy[42];
	Cubecpy[42] = temp2;
	Cubecpy[36] = temp1;

	temp1 = Cubecpy[41];
	Cubecpy[41] = Cubecpy[37];
	temp2 = Cubecpy[43];
	Cubecpy[43] = temp1;
	temp1 = Cubecpy[39];
	Cubecpy[39] = temp2;
	Cubecpy[37] = temp1;

	temp1 = Cubecpy[9];
	Cubecpy[9] = Cubecpy[0];
	temp2 = Cubecpy[45];
	Cubecpy[45] = temp1;
	temp1 = Cubecpy[35];
	Cubecpy[35] = temp2;
	Cubecpy[0] = temp1;

	temp1 = Cubecpy[12];
	Cubecpy[12] = Cubecpy[3];
	temp2 = Cubecpy[48];
	Cubecpy[48] = temp1;
	temp1 = Cubecpy[32];
	Cubecpy[32] = temp2;
	Cubecpy[3] = temp1;

	temp1 = Cubecpy[15];
	Cubecpy[15] = Cubecpy[6];
	temp2 = Cubecpy[51];
	Cubecpy[51] = temp1;
	temp1 = Cubecpy[29];
	Cubecpy[29] = temp2;
	Cubecpy[6] = temp1;
}

void D()
{
	char temp1, temp2;

	temp1 = Cubecpy[47];
	Cubecpy[47] = Cubecpy[45];
	temp2 = Cubecpy[53];
	Cubecpy[53] = temp1;
	temp1 = Cubecpy[51];
	Cubecpy[51] = temp2;
	Cubecpy[45] = temp1;

	temp1 = Cubecpy[50];
	Cubecpy[50] = Cubecpy[46];
	temp2 = Cubecpy[52];
	Cubecpy[52] = temp1;
	temp1 = Cubecpy[48];
	Cubecpy[48] = temp2;
	Cubecpy[46] = temp1;

	temp1 = Cubecpy[24];
	Cubecpy[24] = Cubecpy[15];
	temp2 = Cubecpy[33];
	Cubecpy[33] = temp1;
	temp1 = Cubecpy[42];
	Cubecpy[42] = temp2;
	Cubecpy[15] = temp1;

	temp1 = Cubecpy[25];
	Cubecpy[25] = Cubecpy[16];
	temp2 = Cubecpy[34];
	Cubecpy[34] = temp1;
	temp1 = Cubecpy[43];
	Cubecpy[43] = temp2;
	Cubecpy[16] = temp1;

	temp1 = Cubecpy[26];
	Cubecpy[26] = Cubecpy[17];
	temp2 = Cubecpy[35];
	Cubecpy[35] = temp1;
	temp1 = Cubecpy[44];
	Cubecpy[44] = temp2;
	Cubecpy[17] = temp1;
}

void L()
{
	char temp1, temp2;

	temp1 = Cubecpy[29];
	Cubecpy[29] = Cubecpy[27];
	temp2 = Cubecpy[35];
	Cubecpy[35] = temp1;
	temp1 = Cubecpy[33];
	Cubecpy[33] = temp2;
	Cubecpy[27] = temp1;

	temp1 = Cubecpy[32];
	Cubecpy[32] = Cubecpy[28];
	temp2 = Cubecpy[34];
	Cubecpy[34] = temp1;
	temp1 = Cubecpy[30];
	Cubecpy[30] = temp2;
	Cubecpy[28] = temp1;

	temp1 = Cubecpy[36];
	Cubecpy[36] = Cubecpy[2];
	temp2 = Cubecpy[51];
	Cubecpy[51] = temp1;
	temp1 = Cubecpy[26];
	Cubecpy[26] = temp2;
	Cubecpy[2] = temp1;

	temp1 = Cubecpy[39];
	Cubecpy[39] = Cubecpy[1];
	temp2 = Cubecpy[52];
	Cubecpy[52] = temp1;
	temp1 = Cubecpy[23];
	Cubecpy[23] = temp2;
	Cubecpy[1] = temp1;

	temp1 = Cubecpy[42];
	Cubecpy[42] = Cubecpy[0];
	temp2 = Cubecpy[53];
	Cubecpy[53] = temp1;
	temp1 = Cubecpy[20];
	Cubecpy[20] = temp2;
	Cubecpy[0] = temp1;
}

void B()
{
	char temp1, temp2;

	temp1 = Cubecpy[20];
	Cubecpy[20] = Cubecpy[18];
	temp2 = Cubecpy[26];
	Cubecpy[26] = temp1;
	temp1 = Cubecpy[24];
	Cubecpy[24] = temp2;
	Cubecpy[18] = temp1;

	temp1 = Cubecpy[23];
	Cubecpy[23] = Cubecpy[19];
	temp2 = Cubecpy[25];
	Cubecpy[25] = temp1;
	temp1 = Cubecpy[21];
	Cubecpy[21] = temp2;
	Cubecpy[19] = temp1;

	temp1 = Cubecpy[27];
	Cubecpy[27] = Cubecpy[8];
	temp2 = Cubecpy[53];
	Cubecpy[53] = temp1;
	temp1 = Cubecpy[17];
	Cubecpy[17] = temp2;
	Cubecpy[8] = temp1;

	temp1 = Cubecpy[30];
	Cubecpy[30] = Cubecpy[5];
	temp2 = Cubecpy[50];
	Cubecpy[50] = temp1;
	temp1 = Cubecpy[14];
	Cubecpy[14] = temp2;
	Cubecpy[5] = temp1;

	temp1 = Cubecpy[33];
	Cubecpy[33] = Cubecpy[2];
	temp2 = Cubecpy[47];
	Cubecpy[47] = temp1;
	temp1 = Cubecpy[11];
	Cubecpy[11] = temp2;
	Cubecpy[2] = temp1;
}

void X()
{
	char temp1, temp2;

	temp1 = Cubecpy[39];
	Cubecpy[39] = Cubecpy[12];
	temp2 = Cubecpy[30];
	Cubecpy[30] = temp1;
	temp1 = Cubecpy[21];
	Cubecpy[21] = temp2;
	Cubecpy[12] = temp1;

	temp1 = Cubecpy[40];
	Cubecpy[40] = Cubecpy[13];
	temp2 = Cubecpy[31];
	Cubecpy[31] = temp1;
	temp1 = Cubecpy[22];
	Cubecpy[22] = temp2;
	Cubecpy[13] = temp1;

	temp1 = Cubecpy[41];
	Cubecpy[41] = Cubecpy[14];
	temp2 = Cubecpy[32];
	Cubecpy[32] = temp1;
	temp1 = Cubecpy[23];
	Cubecpy[23] = temp2;
	Cubecpy[14] = temp1;
}

void Y()
{
	char temp1, temp2;

	temp1 = Cubecpy[19];
	Cubecpy[19] = Cubecpy[3];
	temp2 = Cubecpy[50];
	Cubecpy[50] = temp1;
	temp1 = Cubecpy[43];
	Cubecpy[43] = temp2;
	Cubecpy[3] = temp1;

	temp1 = Cubecpy[22];
	Cubecpy[22] = Cubecpy[4];
	temp2 = Cubecpy[49];
	Cubecpy[49] = temp1;
	temp1 = Cubecpy[40];
	Cubecpy[40] = temp2;
	Cubecpy[4] = temp1;

	temp1 = Cubecpy[25];
	Cubecpy[25] = Cubecpy[5];
	temp2 = Cubecpy[48];
	Cubecpy[48] = temp1;
	temp1 = Cubecpy[37];
	Cubecpy[37] = temp2;
	Cubecpy[5] = temp1;
}

void Z()
{
	char temp1, temp2;

	temp1 = Cubecpy[10];
	Cubecpy[10] = Cubecpy[1];
	temp2 = Cubecpy[46];
	Cubecpy[46] = temp1;
	temp1 = Cubecpy[34];
	Cubecpy[34] = temp2;
	Cubecpy[1] = temp1;

	temp1 = Cubecpy[13];
	Cubecpy[13] = Cubecpy[4];
	temp2 = Cubecpy[49];
	Cubecpy[49] = temp1;
	temp1 = Cubecpy[31];
	Cubecpy[31] = temp2;
	Cubecpy[4] = temp1;

	temp1 = Cubecpy[16];
	Cubecpy[16] = Cubecpy[7];
	temp2 = Cubecpy[52];
	Cubecpy[52] = temp1;
	temp1 = Cubecpy[28];
	Cubecpy[28] = temp2;
	Cubecpy[7] = temp1;
}