/*
Ln=2Rθ
L=2Rsinθ
-->Ln/L=θ/(sinθ)
-->Ln=(1+N*C)*L=L*θ/(sinθ)

-->R=L/(2*sinθ)=L/(4*sin(θ/2)*cos(θ/2))

又∵h=R-Rcosθ
     =R(1-cosθ)
	 =R*2*2sin²(θ/2)
  ∴h=(L/2)*tan(θ/2)
*/


#include "stdio.h"
#include "math.h"

double L, Ln, N, C;//L：杆的原始长度 Ln：杆加温后的长度  N：变化温度  C：热膨胀系数
double left, right, mid;//二分 区间
double h;//高度

int main()
{
	while (1)
	{
		scanf("%lf%lf%lf", &L, &N, &C);//输入数据

		if (L < 0 || N < 0 || C < 0)//判断退出条件
		{
			break;
		}
		if (L < 1e-12)
		{
			printf("0.000\n");
			continue;
		}

		Ln = (1 + N*C)*L;

		left = 0.0;
		right = asin(1.0);

		while (right - left > 1e-12)
		{
			mid = left + (right - left) / 2;

			if ((Ln*sin(mid)) / mid <= L)//单调递减
			{
				right = mid;
			}
			else
			{
				left = mid;
			}
		}

		h = (L / 2)*tan(left / 2);
		printf("%.3f\n", h);
	}
}