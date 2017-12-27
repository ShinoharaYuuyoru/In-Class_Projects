#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

struct Expression
{
	int Flag;//0 -> OP, 1 -> Num.
	int Num;
	int Op;
}Ex[1000];//后缀表达式 + 随时计算
int ExCount;

char OpStack[1000];//符号栈
int OpStackCount;

char OriEx[1000];//原始算式
int OriExCount;

char T;

void BuildEx();
int SolveStack();
int IFSOLVED;
void CheckError();

int main()
{
	int N;

	scanf("%d", &N);
	getchar();

	while (N >= 1)
	{
		for (ExCount = 0;ExCount < 1000;ExCount++)
		{
			Ex[ExCount].Flag = -1;
			Ex[ExCount].Num = 0;
			Ex[ExCount].Op = '\0';

			OpStack[ExCount] = '\0';

			OriEx[ExCount] = '\0';
		}
		ExCount = 0;
		OpStackCount = 0;
		OriExCount = 0;

		fgets(OriEx, 1000, stdin);

		BuildEx();

		N--;
	}
}

void BuildEx()
{
	while (1)
	{
		T = OriEx[OriExCount];

		if (T == '\0')
		{
			int POPALL = OpStackCount - 1;
			for (;POPALL >= 0 && OpStack[POPALL] != '(';POPALL--)
			{
				Ex[ExCount].Flag = 0;
				Ex[ExCount].Op = OpStack[POPALL];
				IFSOLVED = SolveStack();
				if (IFSOLVED == 0)
				{
					return;
				}

				OpStack[POPALL] = '\0';
			}

			CheckError();
			return;
		}
		if (T >= 48 && T <= 57)
		{
			char WholeNum[1000];
			memset(WholeNum, 0, sizeof(WholeNum));
			int WNC = 0;
			int RealNum;

			int endnum;
			for (endnum = OriExCount;(OriEx[endnum] >= 48 && OriEx[endnum] <= 57) && OriEx[endnum] != '\0';endnum++, WNC++)
			{
				WholeNum[WNC] = OriEx[endnum];
			}
			OriExCount = endnum - 1;

			RealNum = atoi(WholeNum);

			Ex[ExCount].Flag = 1;
			Ex[ExCount].Num = RealNum;
			ExCount++;
		}
		if (T == '(')
		{
			if (OriEx[OriExCount - 1] >= 48 && OriEx[OriExCount - 1] <= 57)
			{
				printf("error.\n");
				return;
			}

			OpStack[OpStackCount] = '(';
			OpStackCount++;
		}
		if (T == ')')
		{
			if (OriEx[OriExCount + 1] >= 48 && OriEx[OriExCount + 1] <= 57)
			{
				printf("error.\n");
				return;
			}

			int SearchLeftBr;
			for (SearchLeftBr = OpStackCount - 1;SearchLeftBr >= 0 && OpStack[SearchLeftBr] != '(';SearchLeftBr--);
			if (SearchLeftBr == -1)
			{
				printf("error.\n");
				return;
			}
			else//find Left
			{
				for (SearchLeftBr = OpStackCount - 1;OpStack[SearchLeftBr] != '('; SearchLeftBr--)
				{
					Ex[ExCount].Flag = 0;
					Ex[ExCount].Op = OpStack[SearchLeftBr];
					IFSOLVED = SolveStack();
					if (IFSOLVED == 0)
					{
						return;
					}

					OpStack[SearchLeftBr] = '\0';
				}
				OpStack[SearchLeftBr] = '\0';
				OpStackCount = SearchLeftBr;
			}
		}
		if (T == '+')
		{
			int PopPM;
			for (PopPM = OpStackCount - 1;PopPM >= 0;PopPM--)
			{
				if (OpStack[PopPM] != '(')
				{
					Ex[ExCount].Flag = 0;
					Ex[ExCount].Op = OpStack[PopPM];
					IFSOLVED = SolveStack();
					if (IFSOLVED == 0)
					{
						return;
					}

					OpStack[PopPM] = '\0';
				}
				else
				{
					break;
				}
			}
			PopPM++;
			OpStack[PopPM] = '+';
			OpStackCount = PopPM + 1;
		}
		if (T == '-')
		{
			if (OriExCount == 0)
			{
				char WholeNum[1000];
				memset(WholeNum, 0, sizeof(WholeNum));
				int WNC = 0;
				int RealNum;

				int endnum;
				for (endnum = OriExCount + 1;(OriEx[endnum] >= 48 && OriEx[endnum] <= 57) && OriEx[endnum] != '\0';endnum++, WNC++)
				{
					WholeNum[WNC] = OriEx[endnum];
				}
				OriExCount = endnum - 1;

				RealNum = atoi(WholeNum);

				Ex[ExCount].Flag = 1;
				Ex[ExCount].Num = 0 - RealNum;
				ExCount++;
			}
			else
			{
				if ((OriEx[OriExCount - 1] < 48 || OriEx[OriExCount - 1]>57) && (OriEx[OriExCount + 1] >= 48 && OriEx[OriExCount + 1] <= 57))//前边是符号后边是数
				{
					char WholeNum[1000];
					memset(WholeNum, 0, sizeof(WholeNum));
					int WNC = 0;
					int RealNum;

					int endnum;
					for (endnum = OriExCount + 1;(OriEx[endnum] >= 48 && OriEx[endnum] <= 57) && OriEx[endnum] != '\0';endnum++, WNC++)
					{
						WholeNum[WNC] = OriEx[endnum];
					}
					OriExCount = endnum - 1;

					RealNum = atoi(WholeNum);

					Ex[ExCount].Flag = 1;
					Ex[ExCount].Num = 0 - RealNum;
					ExCount++;
				}
				else
				{
					if (OriEx[OriExCount - 1] < 48 || OriEx[OriExCount - 1]>57)//前边是符号 后边也是符号
					{
						printf("error.\n");
						return;
					}
					else//前边是数 后边也是数或者符号
					{
						int PopPM;
						for (PopPM = OpStackCount - 1;PopPM >= 0;PopPM--)
						{
							if (OpStack[PopPM] != '(')
							{
								Ex[ExCount].Flag = 0;
								Ex[ExCount].Op = OpStack[PopPM];
								IFSOLVED = SolveStack();
								if (IFSOLVED == 0)
								{
									return;
								}

								OpStack[PopPM] = '\0';
							}
							else
							{
								break;
							}
						}
						PopPM++;
						OpStack[PopPM] = '-';
						OpStackCount = PopPM + 1;
					}
				}
			}
		}
		if (T == '*')
		{
			int PopPM;
			for (PopPM = OpStackCount - 1;PopPM >= 0;PopPM--)
			{

				if (OpStack[PopPM] == '*' || OpStack[PopPM] == '/' || OpStack[PopPM] == '%' || OpStack[PopPM] == '^')
				{
					Ex[ExCount].Flag = 0;
					Ex[ExCount].Op = OpStack[PopPM];
					IFSOLVED = SolveStack();
					if (IFSOLVED == 0)
					{
						return;
					}

					OpStack[PopPM] = '\0';
				}
				else
				{
					break;
				}
			}
			PopPM++;
			OpStack[PopPM] = '*';
			OpStackCount = PopPM + 1;
		}
		if (T == '/')
		{
			int PopPM;
			for (PopPM = OpStackCount - 1;PopPM >= 0;PopPM--)
			{

				if (OpStack[PopPM] == '*' || OpStack[PopPM] == '/' || OpStack[PopPM] == '%' || OpStack[PopPM] == '^')
				{
					Ex[ExCount].Flag = 0;
					Ex[ExCount].Op = OpStack[PopPM];
					IFSOLVED = SolveStack();
					if (IFSOLVED == 0)
					{
						return;
					}

					OpStack[PopPM] = '\0';
				}
				else
				{
					break;
				}
			}
			PopPM++;
			OpStack[PopPM] = '/';
			OpStackCount = PopPM + 1;
		}
		if (T == '%')
		{
			int PopPM;
			for (PopPM = OpStackCount - 1;PopPM >= 0;PopPM--)
			{

				if (OpStack[PopPM] == '*' || OpStack[PopPM] == '/' || OpStack[PopPM] == '%' || OpStack[PopPM] == '^')
				{
					Ex[ExCount].Flag = 0;
					Ex[ExCount].Op = OpStack[PopPM];
					IFSOLVED = SolveStack();
					if (IFSOLVED == 0)
					{
						return;
					}

					OpStack[PopPM] = '\0';
				}
				else
				{
					break;
				}
			}
			PopPM++;
			OpStack[PopPM] = '%';
			OpStackCount = PopPM + 1;
		}
		if (T == '^')
		{
			OpStack[OpStackCount] = '^';
			OpStackCount++;
		}

		OriExCount++;
	}
}

int SolveStack()
{
	if (Ex[ExCount].Flag == 0)
	{
		char OP = Ex[ExCount].Op;

		if (OP == '+')
		{
			Ex[ExCount - 2].Num = Ex[ExCount - 2].Num + Ex[ExCount - 1].Num;

			Ex[ExCount - 1].Flag = -1;
			Ex[ExCount - 1].Num = 0;
			Ex[ExCount - 1].Op = '\0';
			Ex[ExCount].Flag = -1;
			Ex[ExCount].Num = 0;
			Ex[ExCount].Op = '\0';

			ExCount--;
		}
		if (OP == '-')
		{
			Ex[ExCount - 2].Num = Ex[ExCount - 2].Num - Ex[ExCount - 1].Num;

			Ex[ExCount - 1].Flag = -1;
			Ex[ExCount - 1].Num = 0;
			Ex[ExCount - 1].Op = '\0';
			Ex[ExCount].Flag = -1;
			Ex[ExCount].Num = 0;
			Ex[ExCount].Op = '\0';

			ExCount--;
		}
		if (OP == '*')
		{
			Ex[ExCount - 2].Num = Ex[ExCount - 2].Num * Ex[ExCount - 1].Num;

			Ex[ExCount - 1].Flag = -1;
			Ex[ExCount - 1].Num = 0;
			Ex[ExCount - 1].Op = '\0';
			Ex[ExCount].Flag = -1;
			Ex[ExCount].Num = 0;
			Ex[ExCount].Op = '\0';

			ExCount--;
		}
		if (OP == '/')
		{
			if (Ex[ExCount - 1].Num != 0)
			{
				Ex[ExCount - 2].Num = Ex[ExCount - 2].Num / Ex[ExCount - 1].Num;

				Ex[ExCount - 1].Flag = -1;
				Ex[ExCount - 1].Num = 0;
				Ex[ExCount - 1].Op = '\0';
				Ex[ExCount].Flag = -1;
				Ex[ExCount].Num = 0;
				Ex[ExCount].Op = '\0';

				ExCount--;
			}
			else
			{
				printf("Divide 0.\n");
				return 0;
			}
		}
		if (OP == '%')
		{
			if (Ex[ExCount - 1].Num != 0)
			{
				Ex[ExCount - 2].Num = Ex[ExCount - 2].Num % Ex[ExCount - 1].Num;

				Ex[ExCount - 1].Flag = -1;
				Ex[ExCount - 1].Num = 0;
				Ex[ExCount - 1].Op = '\0';
				Ex[ExCount].Flag = -1;
				Ex[ExCount].Num = 0;
				Ex[ExCount].Op = '\0';

				ExCount--;
			}
			else
			{
				printf("Divide 0.\n");
				return 0;
			}
		}
		if (OP == '^')
		{
			if (Ex[ExCount - 1].Num < 0)
			{
				printf("error.\n");
				return 0;
			}
			else
			{
				Ex[ExCount - 2].Num = pow(Ex[ExCount - 2].Num, Ex[ExCount - 1].Num);

				Ex[ExCount - 1].Flag = -1;
				Ex[ExCount - 1].Num = 0;
				Ex[ExCount - 1].Op = '\0';
				Ex[ExCount].Flag = -1;
				Ex[ExCount].Num = 0;
				Ex[ExCount].Op = '\0';

				ExCount--;
			}
		}
	}
	else
	{
		printf("STACK ERROR!!!\n");
		exit(0);
	}
	
	return 1;
}

void CheckError()
{
	int CheckEx = 0;
	for (;Ex[CheckEx].Flag != -1;CheckEx++);
	if (CheckEx > 1)
	{
		printf("error.\n");
		return;
	}
	
	int CheckOP = 0;
	for (;OpStack[CheckOP] != '\0';CheckOP++);
	if (CheckOP > 0)
	{
		printf("error.\n");
		return;
	}

	printf("%d\n", Ex[0].Num);
}