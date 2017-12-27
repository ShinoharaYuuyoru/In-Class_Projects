#include "stdio.h"
#include "stdlib.h"

struct T
{
	int TeamNum;
	int ProblemSolved;
	int Fault[15];
	int SolveSign[15];
	int Point;
}TEAM[105];/*下角标默认为队伍编号*/
int StructReset = 0;/*专用于Struct的重置*/
int ArReset = 0;

int comp(const void *a, const void *b);

int main()
{
	int n = 1;
	int TeamSum;/*队伍总数*/
	int SolveTime;/*提交时间*/
	int TeamNumber;/*队伍编号*/
	int ProblemNum;/*问题编号*/
	char YN;/*YN为判断正误变量*/
	int Print;
	int PRTED;
	int RANK;

	for (;; n++)
	{
		/*Reset*/
		for (StructReset = 0; StructReset < 105; StructReset++)
		{
			TEAM[StructReset].ProblemSolved = 0;
			TEAM[StructReset].Point = 0;
			TEAM[StructReset].TeamNum = StructReset + 1;
			for (ArReset = 0; ArReset < 15; ArReset++)
			{
				TEAM[StructReset].Fault[ArReset] = 0;
				TEAM[StructReset].SolveSign[ArReset] = 0;
			}
		}

		scanf("%d", &TeamSum);
		if (TeamSum == 0)/*退出条件*/
		{
			break;
		}

		for (;;)
		{
			scanf("%d", &SolveTime);
			if (SolveTime == 0)/*退出输入*/
			{
				break;
			}
			scanf("%d", &TeamNumber);
			scanf("%d", &ProblemNum);

			getchar();/*消除空格*/

			YN = getchar();
			if (YN == 'y')
			{
				if (TEAM[TeamNumber - 1].SolveSign[ProblemNum - 1] == 1)/*如果多次A题 则不算分*/
				{
					getchar();
					getchar();
					getchar();
					continue;
				}
				else
				{
					TEAM[TeamNumber - 1].ProblemSolved++;
					TEAM[TeamNumber - 1].SolveSign[ProblemNum - 1] = 1;
					TEAM[TeamNumber - 1].Point = TEAM[TeamNumber - 1].Point + SolveTime + TEAM[TeamNumber - 1].SolveSign[ProblemNum - 1] * TEAM[TeamNumber - 1].Fault[ProblemNum - 1];
					getchar();
					getchar();
					getchar();
					continue;
				}
			}
			if (YN == 'n')
			{
				TEAM[TeamNumber - 1].Fault[ProblemNum - 1] = TEAM[TeamNumber - 1].Fault[ProblemNum - 1] + 20;

				getchar();
				getchar();
				continue;
			}
		}
		qsort(TEAM, 105, sizeof(TEAM[0]), comp);

		printf("case %d:\n", n);

		for (PRTED = 0, RANK = 1, Print = 0; RANK <= 3 && TEAM[Print].TeamNum <= TeamSum; Print++)
		{
			if (Print == 0)/*第一名是不变的 直接输出*/
			{
				printf("%d %d %d %d\n", TEAM[Print].TeamNum, TEAM[Print].ProblemSolved, TEAM[Print].Point, RANK);
				PRTED++;
			}
			else/*从第二名开始*/
			{
				if (PRTED < 3)
				{
					if (TEAM[Print].ProblemSolved == TEAM[Print - 1].ProblemSolved&&TEAM[Print].Point == TEAM[Print - 1].Point)
					{
						printf("%d %d %d %d\n", TEAM[Print].TeamNum, TEAM[Print].ProblemSolved, TEAM[Print].Point, RANK);
						PRTED++;
					}
					else
					{
						if (Print == 2 && RANK == 1)
						{
							RANK = 3;
							printf("%d %d %d %d\n", TEAM[Print].TeamNum, TEAM[Print].ProblemSolved, TEAM[Print].Point, RANK);
							PRTED++;
						}
						else
						{
							RANK++;
							printf("%d %d %d %d\n", TEAM[Print].TeamNum, TEAM[Print].ProblemSolved, TEAM[Print].Point, RANK);
							PRTED++;
						}
					}
				}
				else
				{
					if (TEAM[Print].ProblemSolved == TEAM[Print - 1].ProblemSolved&&TEAM[Print].Point == TEAM[Print - 1].Point)
					{
						printf("%d %d %d %d\n", TEAM[Print].TeamNum, TEAM[Print].ProblemSolved, TEAM[Print].Point, RANK);
					}
					else
					{
						break;
					}
				}
			}
		}
	}
}

int comp(const void *a, const void *b)
{
	struct T *c = (struct T*)a;
	struct T *d = (struct T*)b;

	if (c->ProblemSolved != d->ProblemSolved)
	{
		return d->ProblemSolved - c->ProblemSolved;
	}
	else
	{
		if (c->Point != d->Point)
		{
			return c->Point - d->Point;
		}
		else
		{
			return c->TeamNum - d->TeamNum;
		}
	}
}