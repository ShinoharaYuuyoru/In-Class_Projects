#include "stdio.h"
#define N 50000
int main()
{
	int n/*����2n���Ƶ�һ������*/, all[N] = { 0 }/*ԭʼ������*/, change[N] = { 0 }/*ϴ������*/, save1[N] = { 0 }/*��ʱ�洢ǰn����*/, save2[N] = { 0 }/*��ʱ�洢��n����*/;
	int i/*������¼�������&������*/,j/*ϴ�ƴ���*/,k/*ȡǰn���Ƽ�����*/,l/*ȡ��n���Ƽ�����*/,c/*����Ƚϼ�����*/,x/*ǰn�������������*/,y/*��n�������������*/,z/*���ռ�����*/;
	scanf("%d", &n);
	for (i = 1; i <= 2 * n; i++)
	{
		all[i] = i;
		change[i] = i;
	}
	i--;
	for (j = 1;1;j++)
	{
		for (c = 1; c <= i; c++)
		{
			if (change[c] == all[c] && j != 1)
			{
				printf("%d\n", j - 1);
				return 0;
			}
			else break;
		}
		for (k = 1; k <= n; k++)
			save1[k] = change[k];
		for (l = 1; l <= n; l++, k++)
			save2[l] = change[k];
		for (z = 1, x = 1, y = 1; z <= i; z++)
		{
			if (z % 2 == 0)
			{
				change[z] = save1[x];
				x++;
			}
			else
			{
				change[z] = save2[y];
				y++;
			}
		}
	}
}