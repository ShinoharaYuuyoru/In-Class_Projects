#include "stdio.h"
#include "stdlib.h"

struct T
{
	int TeamNum;
	int ProblemSolved;
	int Fault[15];
	int SolveSign[15];
	int Point;
}TEAM[105];/*�½Ǳ�Ĭ��Ϊ������*/
int StructReset = 0;/*ר����Struct������*/
int ArReset = 0;

int comp(const void *a, const void *b);

int main()
{
	int n = 1;
	int TeamSum;/*��������*/
	int SolveTime;/*�ύʱ��*/
	int TeamNumber;/*������*/
	int ProblemNum;/*������*/
	char YN;/*YNΪ�ж��������*/
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
		if (TeamSum == 0)/*�˳�����*/
		{
			break;
		}

		for (;;)
		{
			scanf("%d", &SolveTime);
			if (SolveTime == 0)/*�˳�����*/
			{
				break;
			}
			scanf("%d", &TeamNumber);
			scanf("%d", &ProblemNum);

			getchar();/*�����ո�*/

			YN = getchar();
			if (YN == 'y')
			{
				if (TEAM[TeamNumber - 1].SolveSign[ProblemNum - 1] == 1)/*������A�� �����*/
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
			if (Print == 0)/*��һ���ǲ���� ֱ�����*/
			{
				printf("%d %d %d %d\n", TEAM[Print].TeamNum, TEAM[Print].ProblemSolved, TEAM[Print].Point, RANK);
				PRTED++;
			}
			else/*�ӵڶ�����ʼ*/
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