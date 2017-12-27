#include "stdio.h"
#define X 99999
int main()
{
	int T, N, sam,  count, sum = 0, summax,i=0,j=0;
	int happy[X] = {0}, pri[X] = { 0 };
	scanf("%d", &T);//输入案例个数
	for (sam = 1; sam <= T; sam++)
	{
		scanf("%d ", &N);//输入菜品个数
		for (count = 0; count <= N - 1; count++)
		{
			scanf("%d", &happy[count]);//count：数组角标+菜品个数计数器
		}
		for (summax = happy[0], count = 0; count <= N - 1; count++)
		{
			sum = sum + happy[count];//计算好感度和;
			if (sum >= summax)
				summax = sum;
		}
		pri[i] = summax;
		i++;
		summax = 0;
		sum = 0;
	}
	for (; j <= i-1; j++)
		printf("%d\n", pri[j]);
}

//以下为网络正确代码
#include <stdio.h>  
#include <stdlib.h>  
int main(void)
{
	int i, t;
	scanf("%d", &t);
	for (i = 1; i <= t; i++){
		int j, n, max = -1001, sum = 0, tmp = 1, *a;
		int first = 0, last = 0;
		scanf("%d", &n);
		a = (int *)malloc(n*sizeof(int));
		for (j = 0; j<n; j++){
			scanf("%d", a + j);
			sum += a[j];
			if (sum>max){
				max = sum; first = tmp; last = j + 1;
			}
			if (sum<0){
				sum = 0; tmp = j + 2;
			}
		}
		printf("%d\n", max);
		free(a); a = NULL;
	}
	return 0;
}