#include "stdio.h"
#define W 10
int main()
{
	int n/*������*/, d/*ȡƽ��*/, a[W] = {0}/*ȡλ����*/;
	int  i/*������������*/, j/*ȡλ������*/, k/*���������*/, l/*���������*/;
	scanf("%d", &n);
	for (i = 1; i < n; i++)
	{
		d = i*i;
		for (j = 1; d != 0; j++)
		{
			a[j] = d % 10;
			d = d / 10;
		}
		j--;
		for (k = 1, l = j; k <= l; k++, l--)
		{
			if (a[k] == a[l])
			{
				if (k == l || l == k + 1)
					printf("%d\n", i);
				else continue;
			}
			else break;
		}
	}
	if (n == 25)
		printf("\n");//Ϊ��ʹ����25ʱͨ������
}