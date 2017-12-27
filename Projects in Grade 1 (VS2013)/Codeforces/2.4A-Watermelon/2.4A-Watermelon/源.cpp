#include "stdio.h"

int main()
{
	int w;//weight
	int x, y;//分成两个偶数

	scanf("%d", &w);

	for (x = 2; x <= w / 2; x = x + 2)
	{
		y = w - x;

		if (y % 2 == 0)
		{
			printf("YES\n");
			return 0;
		}
	}

	printf("NO\n");
	return 0;
}