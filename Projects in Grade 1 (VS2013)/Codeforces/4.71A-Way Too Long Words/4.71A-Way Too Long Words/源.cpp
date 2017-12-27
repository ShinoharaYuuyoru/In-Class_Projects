#include "stdio.h"
#define N 101

int main()
{
	int n;//змЪ§
	int nc;
	int sign;

	char line[N][N];

	scanf("%d", &n);

	for (nc = 0; nc < n; nc++)
	{
		scanf("%s", line[nc]);

		for (sign = 0; line[nc][sign] != '\0'; sign++);

		if (sign>10)
		{
			printf("%c%d%c\n", line[nc][0], sign - 2, line[nc][sign - 1]);
		}
		else
		{
			printf("%s\n", line[nc]);
		}
	}

	return 0;
}