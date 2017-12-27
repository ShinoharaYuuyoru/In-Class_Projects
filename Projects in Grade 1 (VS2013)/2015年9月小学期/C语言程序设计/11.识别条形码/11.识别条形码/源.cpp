#include "stdio.h"

int main()
{
	int n;
	int nc;
	double barcode[20];
	double barMAX = 0, barMIN = 100000000, Half;/*最大条最小条*/
	char bar[20];
	int flag = 0;

	scanf("%d", &n);
	nc = n;

	for (nc = 0; nc < n; nc++)
	{
		scanf("%lf", &barcode[nc]);
		if (barcode[nc]>barMAX)
		{
			barMAX = barcode[nc];
		}
		if (barcode[nc] < barMIN)
		{
			barMIN = barcode[nc];
		}
	}

	if (barMAX / barMIN <= 1.05 / 0.95)/*如果全是宽条*/
	{
		for (nc = 0; nc < n; nc++)
		{
			printf("1");
		}
		printf("\n");
	}
	else
	{
		Half = (barMAX + barMIN) / 2;

		for (nc = 0; nc < n; nc++)
		{
			if (barcode[nc] < Half)
			{
				bar[nc] = '0';
				barcode[nc] = barcode[nc] * 2;
			}
			else
			{
				bar[nc] = '1';
			}
		}
		bar[nc] = '\0';

		barMAX = 0;
		barMIN = 100000000;
		for (nc = 0; nc < n; nc++)
		{
			if (barcode[nc]>barMAX)
			{
				barMAX = barcode[nc];
			}
			if (barcode[nc] < barMIN)
			{
				barMIN = barcode[nc];
			}
		}
		if (barMAX / barMIN <= 1.05 / 0.95)
		{
			printf("%s\n", bar);
		}
		else
		{
			printf("Bad Barcodes\n");
		}
	}
	return 0;
}