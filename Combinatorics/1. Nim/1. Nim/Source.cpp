#include "iostream"

using namespace std;

int N;
int A[1005];
char Bina[1005][33];
int Length[1005];
int Nc;
int ANS;
int MaxL;

void Reset();
void BinaChange(int A);
void Add();

int main()
{
	while (1)
	{
		Reset();
		cin >> N;
		if (N == 0)
		{
			break;
		}
		else
		{
			for (Nc = 1;Nc <= N;Nc++)
			{
				cin >> A[Nc];

				BinaChange(A[Nc]);
			}

			Add();
			cout << ANS << endl;
		}
	}
}

void Reset()
{

	N = 0;

	int R;
	int All;
	for (All = 0;All < 1005;All++)
	{
		A[All] = 0;
		Length[All] = 0;
		for (R = 0;R < 33;R++)
		{
			Bina[All][R] = '\0';
		}
	}

	Nc = 0;
	ANS = 0;
	MaxL = 0;

	return;
}

void BinaChange(int A)
{
	int InputCounter;
	
	int AC = A;
	for (InputCounter = 0;AC != 1;AC = AC / 2)
	{
		Bina[Nc][InputCounter] = ((AC % 2) + 48);
		InputCounter++;
	}
	Bina[Nc][InputCounter] = '1';
	Length[Nc] = InputCounter;
	if (InputCounter > MaxL)
	{
		MaxL = InputCounter;
	}

	return;
}

void Add()
{
	int PCounter = 0;
	int NCounter = 0;
	int Check = 0;

	for (PCounter = MaxL;PCounter >= 0;PCounter--)
	{
		for (NCounter = 1;NCounter <= N;NCounter++)
		{
			if (Length[NCounter] < PCounter)
			{
				continue;
			}
			else
			{
				if (Bina[NCounter][PCounter] == '1')
				{
					Check++;
				}
				else
				{
					continue;
				}
			}
		}
		if (Check % 2 == 1)
		{
			ANS = Check;

			break;
		}
		else
		{
			Check = 0;
		}
	}

	return;
}