#include "stdio.h"

#define X 30

int N, m;//N:Ǯ<30000   m�����Թ���Ķ���<25
int price[X], level[X];//��Ӧ����Ʒ�۸�͵ȼ�
int sum[30000] = { 0 };

int main()
{
	int mcnt;//��Ʒ����������
	int money;

	scanf("%d%d", &N, &m);//������Ϣ
	for (mcnt = 0; mcnt < m; mcnt++)
	{
		scanf("%d%d", &price[mcnt], &level[mcnt]);
	}

	for (mcnt = 0; mcnt < m; mcnt++)
	{
		for (money = N; money >= price[mcnt]; money--)
		{
			if (sum[money - price[mcnt]] + price[mcnt] * level[mcnt]>sum[money])
			{
				sum[money] = sum[money - price[mcnt]] + price[mcnt] * level[mcnt];
			}
		}
	}
	printf("%d\n", sum[N]);
}