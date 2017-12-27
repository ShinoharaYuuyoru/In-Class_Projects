#include "stdio.h"
#include "string.h"

int MAP[105][105];
int MAPx, MAPy;

int main()
{
	int CaseCount = 1;
	int N1, N2;
	int N1c, N2c;
	int N1ar[105], N2ar[105];
	int ANS;

	while (1)
	{
		memset(MAP, 0, sizeof(MAP));

		scanf("%d%d", &N1, &N2);
		if (N1 == 0 || N2 == 0)
		{
			return 0;
		}

		for (N1c = 0; N1c < N1; N1c++)
		{
			scanf("%d", &N1ar[N1c]);
		}
		for (N2c = 0; N2c < N2; N2c++)
		{
			scanf("%d", &N2ar[N2c]);
		}

		for (MAPy = 1; MAPy <= N1; MAPy++)/*第一个串为纵轴[y] 第二个串为横轴[x]*/
		{
			for (MAPx = 1; MAPx <= N2; MAPx++)
			{
				if (N1ar[MAPy - 1] == N2ar[MAPx - 1])
				{
					MAP[MAPy][MAPx] = MAP[MAPy - 1][MAPx - 1] + 1;
				}
				else/*如果二者不同*/
				{
					if (MAP[MAPy][MAPx - 1] >= MAP[MAPy - 1][MAPx])
					{
						MAP[MAPy][MAPx] = MAP[MAPy][MAPx - 1];
					}
					else
					{
						MAP[MAPy][MAPx] = MAP[MAPy - 1][MAPx];
					}
				}
			}
		}
		ANS = MAP[N1][N2];

		printf("Twin Towers #%d\n", CaseCount);
		printf("Number of Tiles : %d\n", ANS);
		CaseCount++;
	}

}