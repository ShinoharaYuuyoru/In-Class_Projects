#include "stdio.h"
#include "stdlib.h"

int NEED(int X, int Y);

int main()
{
	int m, n, a;//地板长宽 以及地砖尺寸
	__int64 mneed, nneed;//m,n各需要的个数
	__int64 sum;//总共需要

	int mc, nc;//m需要的个数 n需要的个数

	scanf("%d%d%d", &m, &n, &a);

	mneed = NEED(m, a);
	nneed = NEED(n, a);

	sum = mneed*nneed;

	printf("%I64d\n", sum);
}

int NEED(int X, int Y)//处理
{
	int need;//是否需要加1

	need = X%Y;

	if (need == 0)
	{
		return (X / Y);
	}
	else
	{
		return (X / Y + 1);
	}
}