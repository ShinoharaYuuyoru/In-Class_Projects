#include "stdio.h"

int Chain[2000000] = { 0 };
int ChainC = 0;
int Visit[10005] = { 0 };

int n;/*���ָ���*/
int nc;
int c[22];/*���ִ�С*/
int m;/*ʵ��ת�ٱ�����*/
int mc;
int a, b;/*0Ϊa,1Ϊb*/

int main()
{
	scanf("%d", &n);
	for (nc = 0;nc < n;nc++)
	{
		scanf("%d", &c[nc]);
		Chain[ChainC] = c[nc];
		ChainC++;
	}

	int i, j;
	int Temp;
	for (i = 0;i < n;i++)
	{
		for (j = 0;j < n;j++)
		{
			Temp = Chain[i] % Chain[j];
			if ((Temp == 0) && (Visit[Chain[i] / Chain[j]] == 0))
			{
				Chain[ChainC] = Chain[i] / Chain[j];
				ChainC++;
				Visit[Chain[i] / Chain[j]] = 1;
			}
		}
	}

	for (i = n;i < ChainC;i++)
	{
		for (j = n;j < ChainC;j++)
		{
			if (Chain[i] == Chain[j])
			{
				continue;
			}

			Temp = Chain[i] % Chain[j];
			if ((Temp == 0) && (Visit[Chain[i] / Chain[j]] == 0))
			{
				Chain[ChainC] = Chain[i] / Chain[j];
				ChainC++;
				Visit[Chain[i] / Chain[j]] = 1;
			}
			Temp = Chain[i] * Chain[j];
			if (Temp > 10000)
			{
				continue;
			}
			else
			{
				if (Visit[Chain[i] * Chain[j]] == 0)
				{
					Chain[ChainC] = Chain[i] * Chain[j];
					ChainC++;
					Visit[Chain[i] * Chain[j]] = 1;
				}
			}
		}
	}

	int MulC = 0;
	int Do = 0;/*��������ȴ���*/
	int acopy, bcopy;

	scanf("%d", &m);
	for (mc = 0;mc < m;mc++)
	{
		scanf("%d%d", &a, &b);
		acopy = a;
		bcopy = b;

		/*��������ȴ���*/
		for (Do = 2;acopy >= Do&&bcopy >= Do;Do++)
		{
			if (acopy%Do == 0 && bcopy%Do == 0)
			{
				acopy = acopy / Do;
				bcopy = bcopy / Do;
			}
		}

		for (MulC = 1;MulC <= 10000;MulC++)
		{
			if (acopy*MulC <= 10000 && bcopy*MulC <= 10000)
			{
				if (Visit[acopy*MulC] == 1 && Visit[bcopy*MulC] == 1)
				{
					printf("Gear ratio %d:%d can be realized.\n", a, b);
					break;
				}
			}
			else
			{
				printf("Gear ratio %d:%d cannot be realized.\n", a, b);
				break;
			}
		}
	}
}