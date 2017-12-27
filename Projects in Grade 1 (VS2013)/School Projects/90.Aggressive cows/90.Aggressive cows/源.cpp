#include "stdio.h"
#include "algorithm"
using namespace std;

bool YN(int mid);

const int maxn = 100002;
const int INF = 1000000000;
int N, C;//N:牛舍的长度 C:牛的个数
int loc[maxn];

int main()
{
	int left, right, mid;//整个长仓的左右中

	scanf("%d%d", &N, &C);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &loc[i]);
	}

	sort(loc, loc + N);//将牛舍位置从小到大排序

	left = 0;//初始化
	right = INF;

	for (int i = 0; i < 100; i++)//限定二分100次
	{
		mid = left + (right - left) / 2;

		if (YN(mid))
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
	}
	printf("%d\n", left);
}

bool YN(int mid)
{
	int i;
	int last = 0, cur;//第一头牛  现在要放的牛

	for (i = 1; i < C; i++)
	{
		cur = last + 1;//每次将cur定位在last号牛舍的下一个

		for (; (cur < N) && ((loc[cur] - loc[last]) < mid); cur++);//试图放下所有的牛
		if (cur == N)//如果只放下了第一头牛于最后一个牛舍 则说明mid太大 间距都在left与mid之中 返回false
		{
			return false;
		}
		else//把第i头牛放到了cur号牛舍里
		{
			last = cur;
		}
	}
	return true;//如果将牛全部放置 则说明间距在mid与right之中 返回true
}