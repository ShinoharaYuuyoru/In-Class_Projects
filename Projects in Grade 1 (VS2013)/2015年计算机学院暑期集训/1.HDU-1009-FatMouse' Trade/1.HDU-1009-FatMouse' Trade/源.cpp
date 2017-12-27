#include "stdio.h"

int main()
{
	int M, N;//Have M food and N rooms.
	double Beans[1001][2];//Data of rooms. 0 for Beans of thr room and 1 for food that thr room need.
	double Percent[1001];
	double Canget;

	int Ncount;
	int Nccpy;//Ncount copy.
	double savep, save0, save1;//Save percent and data of Beans.

	for (;;)
	{
		scanf("%d%d", &M, &N);

		if (M == -1 && N == -1)//Exit.
		{
			return 0;
		}
		else//Input
		{
			for (Ncount = 0; Ncount < N; Ncount++)
			{
				scanf("%lf%lf", &Beans[Ncount][0], &Beans[Ncount][1]);
			}
		}

		for (Ncount = 0; Ncount < N; Ncount++)//Cal Percent.
		{
			Percent[Ncount] = Beans[Ncount][0] / Beans[Ncount][1];
		}

		for (Nccpy = 0; Nccpy < N;Nccpy++)//Queue.
		{
			for (Ncount = 0; Ncount < N - 1; Ncount++)
			{
				if (Percent[Ncount] >= Percent[Ncount + 1])
				{
					continue;
				}
				else
				{
					savep = Percent[Ncount];
					save0 = Beans[Ncount][0];
					save1 = Beans[Ncount][1];

					Percent[Ncount] = Percent[Ncount + 1];
					Beans[Ncount][0] = Beans[Ncount + 1][0];
					Beans[Ncount][1] = Beans[Ncount + 1][1];

					Percent[Ncount + 1] = savep;
					Beans[Ncount + 1][0] = save0;
					Beans[Ncount + 1][1] = save1;
				}
			}
		}

		Canget = 0;//Reset.

		for (Ncount = 0; Ncount < N; Ncount++)
		{
			if (M >= Beans[Ncount][1])
			{
				Canget = Canget + Beans[Ncount][0];

				M = M - Beans[Ncount][1];
			}
			else
			{
				if (M == 0)
				{
					break;
				}
				else
				{
					Canget = Canget + M / Beans[Ncount][1] * Beans[Ncount][0];
					break;
				}
			}
		}

		printf("%.3lf\n",Canget);
	}
}