/*����˼·����A[1][2~131172] �� B[2~131172][1]  ������ͼ���� ӳ�䵽MAP[2][2~100]��MAP[2~100][2]��OP������   Ȼ������MAP[105][105]�а���ӳ�䷽�����ó������OPSMALL������*/

#include "stdio.h"

int A[2][131175];
int Ac;
int B[131175][2];
int Bc;
int Q;
int n, m;
int MAP[105][105];/*���ڴ洢[131074~131172][131074~131172]��������*/

int OP(int j, int i);
int OPSMALL(int j, int i);

int main()
{
	freopen("input.txt", "r", stdin);//�ļ�����

	for (Ac = 2;Ac <= 131172;Ac++)//������
	{
		scanf("%d", &A[1][Ac]);
	}
	for (Bc = 2;Bc <= 131172;Bc++)//������
	{
		scanf("%d", &B[Bc][1]);
	}

	int i, j;/*i==m,j==n*/
	int Temp1, Temp2;
	for (i = 2;i <= 100;i++)
	{
		Temp1 = OP(2, i + 131072);
		Temp2 = OP(2 + 131072, i);
		MAP[2][i] = Temp1^Temp2;
	}
	for (j = 2;j <= 100;j++)
	{
		Temp1 = OP(j, 2 + 131072);
		Temp2 = OP(j + 131072, 2);
		MAP[j][2] = Temp1^Temp2;
	}

	scanf("%d", &Q);
	while (Q >= 1)
	{
		scanf("%d%d", &n, &m);

		if (n > 2 && m > 2)
		{
			MAP[n][m] = OPSMALL(n, m);
			printf("%d\n", MAP[n][m]);
		}
		else
		{
			printf("%d\n", MAP[n][m]);
		}

		Q--;
	}
}

int OP(int j, int i)
{
	int ANS = 0;
	int Nstart = j - 2;
	int Mstart = i - 2 + Nstart;
	int ADDER = 2;

	for (;Mstart >= Nstart;Mstart--)
	{
		if ((Nstart&Mstart) == Nstart)
		{
			ANS = ANS^A[1][ADDER];
			ADDER++;
			continue;
		}
		else
		{
			ADDER++;
			continue;
		}
	}

	for (ADDER = 2, Mstart = i - 2 + Nstart;Nstart >= 0;Nstart--, Mstart--)
	{
		if ((Nstart&Mstart) == Nstart)
		{
			ANS = ANS^B[ADDER][1];
			ADDER++;
			continue;
		}
		else
		{
			ADDER++;
			continue;
		}
	}

	return ANS;
}

int OPSMALL(int j, int i)
{
	int ANS = 0;
	int Nstart = j - 3;
	int Mstart = i - 3 + Nstart;
	int ADDER = 3;

	for (;Mstart >= Nstart;Mstart--)
	{
		if ((Nstart&Mstart) == Nstart)
		{
			ANS = ANS^MAP[2][ADDER];
			ADDER++;
			continue;
		}
		else
		{
			ADDER++;
			continue;
		}
	}

	for (ADDER = 3, Mstart = i - 3 + Nstart;Nstart >= 0;Nstart--, Mstart--)
	{
		if ((Nstart&Mstart) == Nstart)
		{
			ANS = ANS^MAP[ADDER][2];
			ADDER++;
			continue;
		}
		else
		{
			ADDER++;
			continue;
		}
	}

	return ANS;
}