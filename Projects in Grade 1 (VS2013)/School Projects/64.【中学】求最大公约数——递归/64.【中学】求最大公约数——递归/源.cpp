/*请使用递归算法计算正整数n和m的最大公约数GCD(n,m)。

　　          = m             当 m<=n 且 n mod m =0
GCD(N,M) = GCD(m,n)   当n<m时
                  = GCD(m, n mod m)     其他

输入：
        n和m

输出：
n和m的最大公约数



测试用例 1	
24 48↵

24↵
1秒	64M	0

测试用例 2	
13 15↵

1↵
1秒	64M	0*/

#include "stdio.h"
int GCD(int j, int i);
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	printf("%d\n",GCD(n, m));
}

int GCD(int j, int  i)//j>i
{
	if (j < i)//j>i处理(若m>n , n m调换)
	{
		return GCD(i, j);
	}//每一次最多可运行一次
	if (j%i == 0)
		return i;
	if (j > i)
	{
		return GCD(i, j%i);
	}
}