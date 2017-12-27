#include "stdio.h"
#include "stdlib.h"
int main()
{
	int a;
	a = 42;
	printf("%5c\n",a);
	printf("%4c%2c\n",a,a);
	printf("%3c%4c\n", a, a);
	printf("%2c%6c\n",a,a);
	printf("%1c%8c\n",a,a);
	printf("%2c%6c\n", a, a);
	printf("%3c%4c\n", a, a);
	printf("%4c%2c\n", a, a);
	printf("%5c\n", a);
	system("pause");
}