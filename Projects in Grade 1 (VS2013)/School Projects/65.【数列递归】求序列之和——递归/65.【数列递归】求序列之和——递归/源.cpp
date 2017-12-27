/*
请使用递归算法求下列序列的前n项之和。
1 + 1 / 2 - 1 / 3 + 1 / 4 - 1 / 5 ......

输入：
n

输出：
序列的前n项和（精确到小数点之后第6位）

测试用例 1	
1↵

1↵
1秒	64M	0
测试用例 2	
2↵

1.500000↵
1秒	64M	0
测试用例 3	
3↵

1.166667↵
1秒	64M	0
*/

#include "stdio.h"

float sum(int n);
int main()
{
	int n;
	float m;
	scanf("%d", &n);
	m = sum(n);
	if (m == 1)
		printf("%d\n", (int)m);
	else
		printf("%f\n", m);
}

float sum(int n)
{
	float a;
	if (n >= 1)
	{
		if (n % 2 == 0)
			a = 1.0 / n;
		else
		{
			if (n == 1)
				a = 1;
			else
				a = -1.0 / n;
		}
		n--;
		return a + sum(n);
	}
	else return 0;
}