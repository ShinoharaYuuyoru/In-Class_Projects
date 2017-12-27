#include "stdio.h"
int main()
{
	int n,peach;
	scanf("%d",&n);
	peach = 1;
	if (n == 1)
	{
		printf("The monkey got %d peach in first day.\n", peach);
		return 0;
	}
	else for (; n -1>= 1; n--)
		peach = (peach + n - 1) * 2;
	printf("The monkey got %d peaches in first day.\n", peach);
}