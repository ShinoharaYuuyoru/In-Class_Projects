#include "stdio.h"
#define N 100
int main()
{
	int n, l[N], pr[N];//n���������ֵĸ��� l���������� N��Ԥ��100�� count����������ֱ�� pr���������----------��int
	int count2, prn, mp, save, prt, count, px;//prn��pr��������� mp��ð����������� count���������ָ��������� count2�����ֱȽϼ����� save����ʱ���ݴ洢�� prt����������� px�����������-----------������int
	scanf("%d", &n);
	for (prn = 1, count = 0; count <= n - 1; count++)
	{
		scanf("%d", &l[count]);
		if (count == 0)
			pr[0] = l[count];
		else
		{
			for (count2 = prn-1; count2 >= 0; count2--)
			{
				if (l[count] == pr[count2])
					break;
				else
				{
					if (count2 == 0)
					{
						pr[prn] = l[count];
						prn++;
						for (mp = 1; mp <= prn-1; mp++)
						{
							for (px = 0; px < prn - mp; px++)
							{
								if (pr[px]>pr[px + 1])
								{
									save = pr[px];
									pr[px] = pr[px + 1];
									pr[px + 1] = save;
								}
							}
						}
					}
					else continue;
				}
			}
		}
	}
	for (prt = 0; prt <= prn - 1; prt++)
	{
		if (prt == prn-1)
			printf("%d\n", pr[prt]);
		else
			printf("%-2d", pr[prt]);
	}
}