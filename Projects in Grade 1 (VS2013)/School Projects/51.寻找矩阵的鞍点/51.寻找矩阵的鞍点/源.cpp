#include "stdio.h"
#define N 100
int main()
{
	int m = 0/*����*/, n = 0/*����*/;
	int mcount/*����������*/, ncount/*����������*/;
	int max = 0/*ÿ�����ֵ�Ƚ���*/, mpick = 0/*��mcount�����ֵ��������¼��*/, npick = 0/*��mcount�����ֵ��������¼��*/, suc = 0/*�������������*/, mrcount/*ȷ��ÿ����С��ʱ�����¼�����*/;
	int tra[N][N] = { { 0 } }/*����*/;
	scanf("%d%d", &m, &n);
	for (mcount = 0; mcount < m; mcount++)//��λ��mcount��
	{
		for (ncount = 0; ncount < n; ncount++)//ȷ����mcount�е�����Ԫ��
		{
			scanf("%d", &tra[mcount][ncount]);
		}
	}
	for (mcount = 0; mcount < m; mcount++)//��λ��mcount��
	{
		for (ncount = 0; ncount < n; ncount++)//�жϵ�mcount���е����ֵ
		{
			if (tra[mcount][ncount]>max)
			{
				max = tra[mcount][ncount];
				mpick = mcount;
				npick = ncount;
			}
		}
		for (mrcount = 0; mrcount<m; mrcount++)
		{
			if (tra[mpick][npick]>tra[mrcount][npick])
			{
				max = 0;
				break;
			}
			else
			{
				if (mrcount == m - 1)
				{
					printf("Point:a[%d][%d]==%d\n", mpick, npick, max);
					max = 0;
					suc++;
				}
			}
		}
		if (mcount == m - 1 && suc == 0)
		{
			printf("No Point\n");
		}
	}
}