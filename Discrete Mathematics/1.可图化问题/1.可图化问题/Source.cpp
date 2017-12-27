#include "stdio.h"

int main()
{
	int N;
	int Ar[3005];
	int Counter;
	int Minuser;
	int C;

	scanf("%d", &N);

	for (Minuser = 0, Counter = 0;Counter < N;Minuser++, Counter++)
	{
		scanf("%d", &Ar[Counter]);
	}
	Counter--;
	Minuser = Counter - 1;

	for (;Counter > 0;Counter--)
	{
		for (Minuser = Counter - 1, C = 1;C <= Ar[Counter];C++, Minuser--)
		{
			Ar[Minuser]--;

			if (Ar[Minuser] < 0)
			{
				printf("no\n");
				return 0;
			}
		}
	}
	if (Ar[0] == 0)
	{
		printf("yes\n");
		return 0;
	}
}