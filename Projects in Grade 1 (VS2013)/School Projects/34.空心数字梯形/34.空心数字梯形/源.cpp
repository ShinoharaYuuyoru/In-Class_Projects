#include "stdio.h"
int main()
{
	int n, m, countn, countm, endm, spacen, spacem;
	int countmc;//������
	scanf("%d%d", &n, &m);
	if (n % 2 == 0)
		endm = m + n - 2 + n / 2;//������ȷ��
	else
		endm = m + n - 2 + n / 2 + 1;//������ȷ��
	for (countn = 1,countm = m; countn <= n; countn++,countm++)
	{
		for (spacen = 1; spacen <= countn - 1; spacen++)
			printf("  ");//���ǰ�ÿո�
		if ((countn == 1 || countn == n)&&n!=1)//�жϵ�һ�к����һ��
		{
			for (countmc = countm; countmc <= endm; countmc++)
			{
				printf("%-2d", countmc % 10);//�����������
			}
			if (n % 2 == 0)//�ж���������Ƿ��ظ�
			{
				for (countmc = countmc - 1; countmc >= m + 1; countmc--)//�����������
				{
					if (countn == n&&countmc == endm - (n / 2)+1)
						break;
					printf("%-2d", countmc % 10);
				}
			}
			else
			for (countmc = countmc - 2; countmc >= m + 1; countmc--)//�����������
			{
				if (countn == n&&countmc == endm - (n / 2))
					break;
				printf("%-2d", countmc % 10);
			}
			printf("%d\n", countmc%10);//������һ����
		}
		else//�����ǵ�һ�к����һ�е�ʱ������
		{
			if (n != 1)
			{
				printf("%d", countm % 10);
				if (n % 2 == 0)//����ո�
				for (spacem = 1; spacem <= (endm - m - 1) * 4 + 1 - (countn - 2) * 4; spacem++)
					printf(" ");
				else
				for (spacem = 1; spacem <= (endm - m - 2) * 4 + 3 - (countn - 2) * 4; spacem++)
					printf(" ");
				printf("%d\n", countm % 10);
			}
			else printf("%d\n", countm % 10);
		}
	}
}