#include "stdio.h"

int main()
{
	int T;/*用例个数*/
	int Xc;/*用于计算平地*/
	int nc;/*传送带计数器*/
	int Bi, Ei, Vi;/*Bi：传送带起始位置 Ei：终止位置 Vi：速度*/
	int X, W, R, t, n;/*X：大厅长度 W：走路的速度 R：跑步的速度 t：最多能跑秒数 n：传送带个数*/
	double tr;/*跑剩下的秒*/
	double temp;/*重新计算跑步时的所用时间*/
	double Cbelt[101] = { 0 };
	int x;/*搜索Cbelt*/
	double Ans = 0;

	scanf("%d", &T);

	while (T >= 1)
	{
		scanf("%d%d%d%d%d", &X, &W, &R, &t, &n);

		for (x = 0; x < 101; x++)/*Reset*/
		{
			Cbelt[x] = 0;
		}
		tr = (double)t;
		Xc = X;
		temp = 0;
		Ans = 0;

		for (nc = 0; nc < n; nc++)
		{
			scanf("%d%d%d", &Bi, &Ei, &Vi);

			Xc = Xc - (Ei - Bi);
			Cbelt[Vi] = Cbelt[Vi] + Ei - Bi;

			if (nc == n - 1)
			{
				Cbelt[0] = Xc;
			}
		}

		for (x = 0; x < 101; x++)
		{
			if (Cbelt[x] == 0)/*剪枝*/
			{
				continue;
			}
			else
			{
				if (tr>0)/*如果有剩余跑步时间*/
				{
					temp = Cbelt[x] / ((double)R + x);
					if (tr >= temp)/*如果剩余跑步时间可以跑完这段*/
					{
						tr = tr - temp;
						Ans = Ans + temp;
					}
					else
					{
						/*注意没跑完这段之后剩下的一段或许需要goto*/
						Cbelt[x] = Cbelt[x] - tr*((double)R + x);
						tr = 0;
						Ans = t;
						goto k;
					}
				}
				else
				{
				k:
					temp = Cbelt[x] / ((double)W + x);
					Ans = Ans + temp;
				}
			}
		}
		printf("%.6lf\n", Ans);

		T--;
	}
}