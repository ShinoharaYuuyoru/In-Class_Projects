#include "stdio.h"

int main()
{
	int T;/*��������*/
	int Xc;/*���ڼ���ƽ��*/
	int nc;/*���ʹ�������*/
	int Bi, Ei, Vi;/*Bi�����ʹ���ʼλ�� Ei����ֹλ�� Vi���ٶ�*/
	int X, W, R, t, n;/*X���������� W����·���ٶ� R���ܲ����ٶ� t������������� n�����ʹ�����*/
	double tr;/*��ʣ�µ���*/
	double temp;/*���¼����ܲ�ʱ������ʱ��*/
	double Cbelt[101] = { 0 };
	int x;/*����Cbelt*/
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
			if (Cbelt[x] == 0)/*��֦*/
			{
				continue;
			}
			else
			{
				if (tr>0)/*�����ʣ���ܲ�ʱ��*/
				{
					temp = Cbelt[x] / ((double)R + x);
					if (tr >= temp)/*���ʣ���ܲ�ʱ������������*/
					{
						tr = tr - temp;
						Ans = Ans + temp;
					}
					else
					{
						/*ע��û�������֮��ʣ�µ�һ�λ�����Ҫgoto*/
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