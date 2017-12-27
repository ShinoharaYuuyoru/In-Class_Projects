#include "stdio.h"
int main()
{
	int a,i,j;
	scanf("%d", &a);
	for (i = 1,j=1; i <= a*a; i++)
	{
		printf("%3d", i);
		if (i == a*j)
		{
			j++;
			printf("\n");
		}
		else continue;
	}
}