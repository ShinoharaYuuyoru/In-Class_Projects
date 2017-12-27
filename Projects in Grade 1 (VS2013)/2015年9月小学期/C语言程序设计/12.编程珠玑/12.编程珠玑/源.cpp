#include "stdio.h"
#include "string.h"

int main()
{
	int N;
	int Nc;
	int left = 0, right = 0;
	int CollectMax = 0;
	int Collect = 0;
	char Lace[360];
	char Lacecpy[360];
	char Temp;/*改变颜色或者遇到白色时记录之前的颜色*/
	int Sign[360], s;

	scanf("%d", &N);

	getchar();/*去掉空格*/

	for (Nc = 0; Nc < N; Nc++)
	{
		scanf("%c", &Lace[Nc]);
	}
	Lace[N] = '\0';

	for (s = 0; Lace[s] == 'w'&& s < N; s++);/*如果全是白色*/
	if (s == N)
	{
		printf("%d\n", N);
		return 0;
	}

	for (Nc = 0; Nc < N; Nc++)
	{
		right = Nc;
		left = Nc - 1;
		if (left < 0)
		{
			left = N - 1;
		}
		if (Collect>CollectMax)
		{
			CollectMax = Collect;
		}
		Collect = 0;
		for (s = 0; s < N; s++)
		{
			Sign[s] = 1;
		}
		strcpy(Lacecpy, Lace);

		for (;;)
		{
			if (right == N)
			{
				right = 0;
			}

			if (right == N - 1)
			{
				if (Lacecpy[0] == 'w')
				{
					Lacecpy[0] = Lacecpy[right];
				}
			}
			else
			{
				if (Lacecpy[right + 1] == 'w')
				{
					Lacecpy[right + 1] = Lacecpy[right];
				}
			}
			if (Lacecpy[right] == 'w')
			{
				int r, t;
				for (r = right; Lacecpy[r] == 'w'; r++)
				{
					if (r == N - 1)
					{
						r = -1;
					}
				}
				for (t = right; Lacecpy[t] == 'w'; t++)
				{
					if (t == N - 1)
					{
						Lacecpy[t] = Lacecpy[r];
						t = -1;
					}
					else
					{
						Lacecpy[t] = Lacecpy[r];
					}
				}
			}

			if (right + 1 == N)
			{
				if (Lacecpy[right] == Lacecpy[0])
				{
					Temp = Lacecpy[right];
					if (Sign[right] == 1)
					{
						Sign[right] = 0;
						right++;
						Collect++;
					}
					else
					{
						break;
					}
				}
				else
				{
					Sign[right] = 0;
					Collect++;
					Temp = Lacecpy[right];
					break;
				}
			}
			else
			{
				if (Lacecpy[right] == Lacecpy[right + 1])
				{
					Temp = Lacecpy[right];
					if (Sign[right] == 1)
					{
						Sign[right] = 0;
						right++;
						Collect++;
					}
					else
					{
						break;
					}
				}
				else
				{
					Sign[right] = 0;
					Collect++;
					Temp = Lacecpy[right];
					break;
				}
			}
		}

		if (Lacecpy[left] == Temp)
		{
			continue;
		}
		else
		{
			if (Lacecpy[left] == 'w')
			{
				if (Temp == 'r')
				{
					Lacecpy[left] = 'b';
				}
				if (Temp == 'b')
				{
					Lacecpy[left] = 'r';
				}
			}
		}
		for (;;)
		{
			if (left < 0)
			{
				left = N - 1;
			}

			if (left == 0)
			{
				if (Lacecpy[N - 1] == 'w')
				{
					Lacecpy[N - 1] = Lacecpy[left];
				}
			}
			else
			{
				if (Lacecpy[left - 1] == 'w')
				{
					Lacecpy[left - 1] = Lacecpy[left];
				}
			}

			if (left  == 0)
			{
				if (Lacecpy[left] == Lacecpy[N - 1])
				{
					if (Sign[left] == 1)
					{
						Sign[left] = 0;
						left--;
						Collect++;
					}
				}
				else
				{
					Sign[left] = 0;
					Collect++;
					break;
				}
			}
			else
			{
				if (Lacecpy[left] == Lacecpy[left - 1])
				{
					if (Sign[left] == 1)
					{
						Sign[left] = 0;
						left--;
						Collect++;
					}
				}
				else
				{
					Sign[left] = 0;
					Collect++;
					break;
				}
			}
		}
	}

	if (Collect>CollectMax)/*最后一个是最大值的话 会因for退出而无法记录 在此记录最后一组数据*/
	{
		CollectMax = Collect;
	}
	printf("%d\n", CollectMax);
}