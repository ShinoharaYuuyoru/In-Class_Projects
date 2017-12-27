#include<stdio.h>
int main()
{
	int a, b, n, m, i, j, k, l, x = 0, count = 0;
	printf("Please input three integers:");
	scanf("%d%d%d", &a, &b, &n);

	if ((b<1) || (a>2000) || (a>b) || (n>9) || (n<1))
	{
		printf("Error");
	}
	else
	{
		for (m = a; m <= b; m++)
		{
			i = m / 1000;
			j = (m - i * 1000) / 100;
			k = (m - i * 1000 - j * 100) / 10;
			l = m - i * 1000 - j * 100 - k * 10;
			if ((i <= n) && (j >= 1) && (j <= n) && (k >= 1) && (k <= n) && (l >= 1) && (l <= n))
			{
				if ((i != j) && (i != k) && (i != l) && (j != k) && (j != l) && (k != l))
				{
					if (count == 0)
						printf("The result is:\n");
					printf("%d\t", m);
					x++;
					count++;
					if ((x != 0) && (x % 5) == 0)
					{
						printf("\n");
					}
				}
			}
			else
			{
				if ((i == 0) && (j == 0) && (k <= n) && (l >= 1) && (l <= n))
				{
					if ((k != l))
					{
						if (count == 0)
							printf("The result is:\n");
						printf("%d\t", m);
						x++;
						count++;
						if ((x != 0) && (x % 5 == 0))
						{
							printf("\n");
						}
					}
				}
			}
		}
		if (count == 0)
			printf("There is no proper number in the interval.");
	}
	return 0;
}