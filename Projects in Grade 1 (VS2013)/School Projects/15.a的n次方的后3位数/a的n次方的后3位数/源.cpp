#include "stdio.h"
int main()
{
	int a, n, ys=1,i;
	scanf("%d%d", &a, &n);
	for (i = 1; i <= n; i++)
		ys = (ys*a) % 1000;
	if (ys == 0 || (n != 0 && ys < 100))
		printf("The last 3 numbers is %03d.\n", ys);
	else printf("The last 3 numbers is %d.\n", ys);
	return 0;
}