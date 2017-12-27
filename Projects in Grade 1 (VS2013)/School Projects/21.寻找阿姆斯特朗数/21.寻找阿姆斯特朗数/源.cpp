#include "stdio.h"
int main()
{
	int n,a,ys,i,cfh,cf,max,g,xh,z,gg=0;

	scanf("%d", &n);

	i = n;
	if (n == 1)
	{
		for (g = 1; g <= 9; g++)
			printf("%d\n", g);
	}
	else
	{
		for (a = 1; i > 1; i--)
			a = a * 10;
		max = a * 10 - 1;
		for (; a <= max; a++)
		{
			for (cfh=0,xh=a;xh>=1;)
			{
				ys = xh % 10;
				xh = (xh - ys) / 10;
				for (z=n,cf=1; z >= 1; z--)
				{
					cf = cf*ys;
				}
				cfh = cfh + cf;
			}
			if (a == cfh)
			{
				printf("%d\n", a);
				gg++;
			}
		}
		if (gg == 0)
			printf("No output.\n");
	}
}