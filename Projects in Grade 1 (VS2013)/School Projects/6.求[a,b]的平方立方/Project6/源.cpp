#include "stdio.h"
int main()
{
	int a, b,c,d;
	printf("Please input two intergers:");
	scanf_s("%d%d" ,&a,&b);
	printf("number\tsquare\tcube\t\n");
	do {
		c = a*a;
		d = a*a*a;
		printf("%d\t%d\t%d\t\n",a,c,d);
		a = a + 1;
	} while (a <=b);
}