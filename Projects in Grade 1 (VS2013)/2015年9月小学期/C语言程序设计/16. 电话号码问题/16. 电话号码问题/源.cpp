#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct R
{
	int Pnum;/*电话号码*/
	int Re;/*重复次数*/
}Repeat[1510];

unsigned int M[62502] = { 0 };/*Bitmap*/

void set(int i);
int test(int i);
int comp(const void *a, const void *b);

int main()
{
	char Input[22];
	int searchQZ;/*用于搜索QZ*/
	int searchNum;/*用于搜索数字*/
	int Numtemp;/*直接记录数字*/
	int Numtempcount;
	int Repeatcount;
	int Print;
	int searchHave;/*看结构里是否已有此数*/
	int firstflag = 0;
	int ErrorNum = 0;
	int in;/*进入搜索*/

	for (Repeatcount = 0; Repeatcount < 1510; Repeatcount++)
	{
		Repeat[Repeatcount].Pnum = 999999999;
		Repeat[Repeatcount].Re = 1;
	}
	Repeatcount = 0;

	printf("Error:\n");

	while (scanf("%s", Input) != EOF)
	{
		Numtemp = 0;
		for (in = 0; Input[in] != '\0'; in++)
		{
			if (Input[in] == '-')
			{
				continue;
			}
			if (Input[in] == '3' || Input[in] == '6' || Input[in] == 'D' || Input[in] == 'E' || Input[in] == 'F' || Input[in] == 'M' || Input[in] == 'N' || Input[in] == 'O')/*如果检测到合法数字*/
			{
				for (searchQZ = 0; Input[searchQZ] != '\0'; searchQZ++)/*顺带把DEFMNO改成数字*/
				{
					if (Input[searchQZ] == 'Q' || Input[searchQZ] == 'Z')
					{
						printf("%s\n", Input);
						ErrorNum++;
						Input[0] = '\0';
						break;
					}
					if (65 <= Input[searchQZ] && Input[searchQZ] <= 67)
					{
						Input[searchQZ] = '2';
					}
					if (68 <= Input[searchQZ] && Input[searchQZ] <= 70)
					{
						Input[searchQZ] = '3';
					}
					if (71 <= Input[searchQZ] && Input[searchQZ] <= 73)
					{
						Input[searchQZ] = '4';
					}
					if (74 <= Input[searchQZ] && Input[searchQZ] <= 76)
					{
						Input[searchQZ] = '5';
					}
					if (77 <= Input[searchQZ] && Input[searchQZ] <= 79)
					{
						Input[searchQZ] = '6';
					}
					if (80 <= Input[searchQZ] && Input[searchQZ] <= 83)
					{
						Input[searchQZ] = '7';
					}
					if (84 <= Input[searchQZ] && Input[searchQZ] <= 86)
					{
						Input[searchQZ] = '8';
					}
					if (87 <= Input[searchQZ] && Input[searchQZ] <= 89)
					{
						Input[searchQZ] = '9';
					}
				}

				for (Numtempcount = 0, Numtemp = 0, searchNum = 0; Input[searchNum] != '\0'; searchNum++)/*把电话号码以数的形式表示*/
				{
					if (Input[searchNum] >= 48 && Input[searchNum] <= 57)
					{
						Numtemp = Numtemp * 10;
						Numtemp = Numtemp + (Input[searchNum] - 48);
					}
				}

				if (Numtemp >= 6000000 && Numtemp < 7000000)/*6开头的*/
				{
					if (test(Numtemp - 5000000) == 0)
					{
						set(Numtemp - 5000000);
					}
					else
					{
						if (firstflag == 0)
						{
							Repeat[Repeatcount].Pnum = Numtemp;
							Repeat[Repeatcount].Re++;
							Repeatcount++;
							firstflag = 1;
							break;
						}
						else
						{
							for (searchHave = 0; searchHave < Repeatcount; searchHave++)
							{
								if (Numtemp == Repeat[searchHave].Pnum)/*如果已有*/
								{
									Repeat[searchHave].Re++;
									break;
								}
							}
							/*如果没有*/
							if (searchHave == Repeatcount)
							{
								Repeat[Repeatcount].Pnum = Numtemp;
								Repeat[Repeatcount].Re++;
								Repeatcount++;
							}
							break;
						}
					}
				}
				if (Numtemp >= 3000000 && Numtemp < 4000000)/*3开头的*/
				{
					if (test(Numtemp - 3000000) == 0)
					{
						set(Numtemp - 3000000);
					}
					else
					{
						if (firstflag == 0)
						{
							Repeat[Repeatcount].Pnum = Numtemp;
							Repeat[Repeatcount].Re++;
							Repeatcount++;
							firstflag = 1;
							break;
						}
						else
						{
							for (searchHave = 0; searchHave < Repeatcount; searchHave++)
							{
								if (Numtemp == Repeat[searchHave].Pnum)/*如果已有*/
								{
									Repeat[searchHave].Re++;
									break;
								}
							}
							/*如果没有*/
							if (searchHave == Repeatcount)
							{
								Repeat[Repeatcount].Pnum = Numtemp;
								Repeat[Repeatcount].Re++;
								Repeatcount++;
							}
							break;
						}
					}
				}
			}
			else
			{
				printf("%s\n", Input);
				ErrorNum++;
				break;
			}
			break;
		}
	}
	if (ErrorNum == 0)
	{
		printf("Not found.\n");
	}

	printf("\n");

	qsort(Repeat, Repeatcount + 1, sizeof(Repeat[0]), comp);

	printf("Duplication:\n");
	if (Repeatcount == 0)
	{
		printf("Not found.\n");
	}
	else
	{
		for (Print = 0; Repeat[Print].Re > 1; Print++)
		{
			printf("%d-%04d %d\n", Repeat[Print].Pnum / 10000, Repeat[Print].Pnum % 10000, Repeat[Print].Re);
		}
	}

	return 0;
}

void set(int i)/*置入*/
{
	M[i >> 5] |= (1 << (i & 0x1f));
}

int test(int i)/*如果是0 则没有记录 1为有记录*/
{
	return M[i >> 5] & (1 << (i & 0x1f));
}

int comp(const void *a, const void *b)
{
	struct R*c = (struct R*)a;
	struct R*d = (struct R*)b;

	return c->Pnum - d->Pnum;
}