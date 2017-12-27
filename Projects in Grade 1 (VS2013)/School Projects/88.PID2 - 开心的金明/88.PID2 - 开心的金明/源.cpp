#include "stdio.h"

#define X 30

int N, m;//N:钱<30000   m：可以购买的东西<25
int price[X], level[X];//对应的物品价格和等级
int sum[30000] = { 0 };

int main()
{
	int mcnt;//物品个数计数器
	int money;

	scanf("%d%d", &N, &m);//输入信息
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