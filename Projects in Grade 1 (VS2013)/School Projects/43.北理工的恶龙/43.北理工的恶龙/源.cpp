#include "stdio.h"
#define N 100
void sort(int array[],int length);
int main()
{
	int n/*龙头数*/, m/*勇士个数*/, nd[N] = { 0 }/*龙头直径(数组个数=龙头数)*/, mh[N] = { 0 }/*勇士身高(数组个数=勇士个数)*/, sum = 0/*学分总和*/;
	int nc/*龙头数计数器*/, mc/*勇士个数计数器*/;
	scanf("%d %d", &n, &m);//输入龙头数和勇士个数
	for (nc = 1; nc <= n; nc++)//输入龙头直径
		scanf("%d", &nd[nc]);
	sort(nd, n);//龙头直径从小到大排序(1~n)
	for (mc = 1; mc <= m; mc++)//输入勇士个数
		scanf("%d", &mh[mc]);
	sort(mh, m);//勇士身高从小到大排序(1~m)
	if (n > m)
	{
		printf("bit is doomed!\n");
		return 0;
	}
	for (nc = 1, mc = 1; nc <= n; nc++)
	{
		for (; mc <= m; mc++)
		{
			if (nd[nc] > mh[mc])
				continue;
			else
			{
				sum = sum + mh[mc];
				mc++;
				break;
			}
		}
		if (nd[nc] > mh[m])
		{
			printf("bit is doomed!\n");
			return 0;
		}
	}
	printf("%d\n", sum);
}
void sort(int array[],int length)/*排序函数、数组长度*/
{
	int i/*第一取位计数器*/, j/*第二取位计数器*/, save/*临时存储器*/, p/*下角标记录与比较器*/;
	for (i = 1; i <= length; i++)
	{
		p = i;
		for (j = i + 1; j <= length; j++)
		{
			if (array[p] > array[j])
				p = j;
		}
		if (p != i)
		{
			save = array[p];
			array[p] = array[i];
			array[i] = save;
		}
	}
}