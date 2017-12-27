#include "stdio.h"
int main()
{
	int n[5], a, b, c, d, e, sum, count,i;
	n[0] =  0 ;
	for (i = 1; i <= 4; i++)
		scanf("%d", &n[i]);
	sum = 0;
	count = 1;
	s:
	for (e = 0; e <= 4; e++)
	{
		for (d = 0; d <= 4; d++)
		{
			for (c = 0; c <= 4; c++)
			{
				for (b = 0; b <= 4; b++)
				{
					for (a = 1; a <= 4; a++)
					{
						sum = n[e] + n[d] + n[c] + n[b] + n[a];
						if (count == sum)
						{
							count++;
							goto s;
						}
						else
						{
							if (e == 5)
								break;
							else continue;
						}
					}
				}
			}
		}
	}
	printf("The max is %d.\n", count-1);
}