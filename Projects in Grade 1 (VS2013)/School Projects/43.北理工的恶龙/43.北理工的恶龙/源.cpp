#include "stdio.h"
#define N 100
void sort(int array[],int length);
int main()
{
	int n/*��ͷ��*/, m/*��ʿ����*/, nd[N] = { 0 }/*��ͷֱ��(�������=��ͷ��)*/, mh[N] = { 0 }/*��ʿ���(�������=��ʿ����)*/, sum = 0/*ѧ���ܺ�*/;
	int nc/*��ͷ��������*/, mc/*��ʿ����������*/;
	scanf("%d %d", &n, &m);//������ͷ������ʿ����
	for (nc = 1; nc <= n; nc++)//������ͷֱ��
		scanf("%d", &nd[nc]);
	sort(nd, n);//��ͷֱ����С��������(1~n)
	for (mc = 1; mc <= m; mc++)//������ʿ����
		scanf("%d", &mh[mc]);
	sort(mh, m);//��ʿ��ߴ�С��������(1~m)
	if (n > m)
	{
		printf("bit is doomed!\n");
		return 0;
	}
	for (nc = 1, mc = 1; nc <= n; nc++)
	{
		for (; mc <= m; mc++)
		{
			if (nd[nc] > mh[mc])
				continue;
			else
			{
				sum = sum + mh[mc];
				mc++;
				break;
			}
		}
		if (nd[nc] > mh[m])
		{
			printf("bit is doomed!\n");
			return 0;
		}
	}
	printf("%d\n", sum);
}
void sort(int array[],int length)/*�����������鳤��*/
{
	int i/*��һȡλ������*/, j/*�ڶ�ȡλ������*/, save/*��ʱ�洢��*/, p/*�½Ǳ��¼��Ƚ���*/;
	for (i = 1; i <= length; i++)
	{
		p = i;
		for (j = i + 1; j <= length; j++)
		{
			if (array[p] > array[j])
				p = j;
		}
		if (p != i)
		{
			save = array[p];
			array[p] = array[i];
			array[i] = save;
		}
	}
}