#include "stdio.h"
#include <algorithm>  
using namespace std;

double CAL(double left);

const int N=25;

int KM;//比赛总距离
int NUM;//选手数量
double SPEED[N][2];//每个选手对应的速度

int main()
{
	double left, right, mid1, mid2;
	double TimeCompete;

	while (scanf("%d", &KM) != EOF)
	{
		scanf("%d", &NUM);
		
		for (int i = 1; i <= NUM; i++)//录入选手信息
		{
			scanf("%lf", &SPEED[i][0]);
			scanf("%lf", &SPEED[i][1]);
		}

		left = 0;
		right = KM;
		while (right - left > 1e-12)
		{
			mid1 = left + (right - left) / 3;
			mid2 = right - (right - left) / 3;

			if (CAL(mid1) < CAL(mid2))
			{
				left = mid1;
			}
			else
			{
				right = mid2;
			}
		}
		TimeCompete = CAL(left);
		if (TimeCompete < 0.00)
		{
			printf("The cheater cannot win.\n");
		}
		else
		{
			printf("The cheater can win by %.0f seconds with r = %.2fkm and k = %.2fkm.\n", TimeCompete * 3600, left, KM - left);
		}
	}
}

double CAL(double left)
{
	double r, k;//r：running distance      k：cycling distance
	double TimeCheater, TimeOthers;//Cheater的总时间   其他选手的时间
	double MinTime = 1e100;

	r = left;
	k = KM - r;

	TimeCheater = r / SPEED[NUM][0] + k / SPEED[NUM][1];

	for (int i = 1; i < NUM; i++)
	{
		TimeOthers = r / SPEED[i][0] + k / SPEED[i][1];
		MinTime = min(MinTime, TimeOthers - TimeCheater);
	}
	return MinTime;
}