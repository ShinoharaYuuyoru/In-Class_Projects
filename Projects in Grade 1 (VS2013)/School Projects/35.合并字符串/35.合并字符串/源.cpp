#include "stdio.h"
#define N 100
int main()
{
	int i/*l1ƴ�Ӽ�����*/,j/*l2ƴ�Ӽ�����*/,sc/*���������*/,m/*�����м�����*/,n/*ÿһ�����м�����*/;
	char l1[N]/*��һ����������*/, l2[N]/*�ڶ�����������*/, pr[N]/*�����������*/,save/*��ʱ�Ĵ���*/;
	gets(l1);
	gets(l2);
	for (i = 0; l1[i] != '\0'; i++)
		pr[i] = l1[i];
	for (j = 0; l2[j] != '\0'; i++,j++)
		pr[i] = l2[j];
	i--;
	for (m = 1; m <= i; m++)
	{
		for (n = 0; n < i + 1 - m; n++)
		{
			if (pr[n] - ' ' >= pr[n + 1] - ' ')
			{
				save = pr[n];
				pr[n] = pr[n + 1];
				pr[n + 1] = save;
			}
		}
	}
	for (sc = 0; sc <= i; sc++)
		printf("%c", pr[sc]);
	printf("\n");
}