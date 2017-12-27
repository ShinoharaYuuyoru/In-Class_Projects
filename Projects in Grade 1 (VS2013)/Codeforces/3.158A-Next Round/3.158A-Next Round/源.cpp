#include "stdio.h"

int main()
{
	int N, K;//总人数N 第K个人
	int score[70];//成绩
	int stop;//记录分数
	int all;//进入下一轮

	int Kc;//指针

	scanf("%d%d", &N, &K);
	for (Kc = 1; Kc <= N; Kc++)
	{
		scanf("%d", &score[Kc]);

		if (Kc == K)
		{
			stop = score[Kc];
		}
	}

	all = 0;

	if (stop != 0)
	{
		for (Kc = 1; Kc <= N; Kc++)
		{
			if (score[Kc] >= stop)
			{
				all++;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		for (Kc = 1; Kc <= N; Kc++)
		{
			if (score[Kc] > stop)
			{
				all++;
			}
			else
			{
				break;
			}
		}
	}
	
	printf("%d\n", all);

	return 0;
}