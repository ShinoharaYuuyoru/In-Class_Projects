#include "stdio.h"
int main()
{
	    int min, max, a, ws;
		int num1, num2, num3, num4, counter;
		k:
		scanf("%d%d", &min, &max);
		if (min == 0 && max == 0)
			return 0;
		else 
		{
			a = min;
			for (ws = 0; a > 0; ws++)
				a = a / 10;
			a = min;
			if (ws < 4)
				printf("Error\n");
			else
			{
				for (counter = 0, a = min; min <= max; min++, a = min)
				{
					if (a % 2 == 0)
					{
						num1 = a / 1000;
						num2 = a / 100 % 10;
						num3 = a / 10 % 10;
						num4 = a % 10;
						if (num1 != num2&&num1 != num3&&num1 != num4&&num2 != num3&&num2 != num4&&num3 != num4)
						{
							counter++;
							printf("%-6d", a);
						}
					}
				}
				if (min == max + 1)
				{
					printf("\n");
					printf("counter=%d\n", counter);
				}
			}
		}
		goto k;
}