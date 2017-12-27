/*����DP*/

#include "stdio.h"
#include "string.h"

double PROB[105][105][105];

int main()
{
	int r, s, p;/*ʯͷ����������*/
	int rc, sc, pc;

	double PROBTOTAL;
	double ANSr = 0, ANSs = 0, ANSp = 0;/*��*/

	memset(PROB, 0.0, sizeof(PROB));/*��ʼ��*/

	scanf("%d%d%d", &r, &s, &p);
	PROB[r][s][p] = 1.0;/*��������������״̬�ĸ���Ϊ1*/

	for (rc = r; rc >= 0; rc--)
	{
		for (sc = s; sc >= 0; sc--)
		{
			for (pc = p; pc >= 0; pc--)
			{
				PROBTOTAL = rc*sc + sc*pc + rc*pc;
				if (rc + sc == 0 || rc + pc == 0 || sc + pc == 0)
				{
					continue;
				}
				else
				{
					if (pc != 0)/*����������� ��ô�����ٿ��ǲ������*/
					{
						PROB[rc][sc][pc - 1] = PROB[rc][sc][pc - 1] + (PROB[rc][sc][pc] * sc*pc) / PROBTOTAL;
					}
					if (sc != 0)
					{
						PROB[rc][sc - 1][pc] = PROB[rc][sc - 1][pc] + (PROB[rc][sc][pc] * rc*sc) / PROBTOTAL;
					}
					if (rc != 0)
					{
						PROB[rc - 1][sc][pc] = PROB[rc - 1][sc][pc] + (PROB[rc][sc][pc] * pc*rc) / PROBTOTAL;
					}
				}
			}
		}
	}

	int print;
	for (print = 0; print <= r; print++)
	{
		ANSr = ANSr + PROB[print][0][0];
	}
	for (print = 0; print <= s; print++)
	{
		ANSs = ANSs + PROB[0][print][0];
	}
	for (print = 0; print <= p; print++)
	{
		ANSp = ANSp + PROB[0][0][print];
	}
	printf("%.6lf %.6lf %.6lf\n", ANSr, ANSs, ANSp);
}