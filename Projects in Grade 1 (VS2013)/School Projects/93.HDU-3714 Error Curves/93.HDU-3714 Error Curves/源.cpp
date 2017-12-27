#include "stdio.h"

double CAL(double x);

int T;//输入组数
int I;//输入的函数个数

double y[100005];//每个函数对应的值

struct Fc
{
	double a;
	double b;
	double c;
}S[100005];

int main()
{
	double left, right;
	double mid1, mid2;

	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &I);
		for (int i = 0; i < I; i++)
		{
			scanf("%lf%lf%lf", &S[i].a, &S[i].b, &S[i].c);
		}

		left = 0; 
		right = 1000;

		while ((right-left)>1e-12)
		{
			mid1 = left + (right - left) / 3;
			mid2 = right - (right - left) / 3;

			if (CAL(mid1) < CAL(mid2))
			{
				right = mid2;
			}
			else
			{
				left = mid1;
			}
		}
		printf("%.4f\n", CAL(left));
	}
}

double CAL (double x)
{
	double max=-10000000;

	for (int i = 0; i < I; i++)
	{
		y[i] = S[i].a*x*x + S[i].b*x + S[i].c;
		if (y[i]>max)
		{
			max = y[i];
		}
	}
	return max;
}