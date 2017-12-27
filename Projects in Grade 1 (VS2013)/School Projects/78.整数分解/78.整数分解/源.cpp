#include "stdio.h"

int main()
{
	int N;
	int start = 1, end,sum=0;
	int n,count=0;

	scanf("%d", &N);

	for (; start <= N / 2; start++)
	{
		for (n = 2, end = start + 1; end <= N / 2 + 1; end++, n++)
		{
			sum = (start + end)*n / 2;
			if (N == sum)
			{
				printf("%d~%d\n", start, end);
				count++;
				break;
			}
			else
			{
				if (sum>N)
				{
					break;
				}
			}
		}
	}
	if (count == 0)
		printf("None\n");
}