#include "stdio.h"

int FirstCheck(int N);
void Duel(int N, int S);

int ANS;

int main()
{
	int N;

	scanf("%d", &N);

	if (FirstCheck(N) == 1)
	{
		Duel(N, (1 + N)*N / 2 / 2);

		printf("%d\n", ANS / 2);
	}
	else
	{
		printf("0\n");
	}

	return 0;
}

int FirstCheck(int N)
{
	if (((1 + N)*N / 2) % 2 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Duel(int N, int S)
{

	if (N >= 0)
	{
		if ((1 + N)*N / 2 >= S)
		{
			if (S > 0)
			{
				Duel(N - 1, S);
				Duel(N - 1, S - N);
			}
			else
			{
				if (S == 0)
				{
					ANS++;
				}
				else
				{
					return;
				}
			}

		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}