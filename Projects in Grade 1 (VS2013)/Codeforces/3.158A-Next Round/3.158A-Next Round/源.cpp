#include "stdio.h"

int main()
{
	int N, K;//������N ��K����
	int score[70];//�ɼ�
	int stop;//��¼����
	int all;//������һ��

	int Kc;//ָ��

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