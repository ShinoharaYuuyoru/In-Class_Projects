#include "stdio.h"
#include "stdlib.h"

int NEED(int X, int Y);

int main()
{
	int m, n, a;//�ذ峤�� �Լ���ש�ߴ�
	__int64 mneed, nneed;//m,n����Ҫ�ĸ���
	__int64 sum;//�ܹ���Ҫ

	int mc, nc;//m��Ҫ�ĸ��� n��Ҫ�ĸ���

	scanf("%d%d%d", &m, &n, &a);

	mneed = NEED(m, a);
	nneed = NEED(n, a);

	sum = mneed*nneed;

	printf("%I64d\n", sum);
}

int NEED(int X, int Y)//����
{
	int need;//�Ƿ���Ҫ��1

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