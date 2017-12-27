#include "stdio.h"

int main()
{
	printf("Hello,world!!!\n\n");
	double a;
	int b;
	float c;
	scanf_s("%d%f",&b,&c);
	a = b + c;
	printf("a=%lf\nb=%d\nc=%f\n", a, b, c);

	double d;
	int e;
	float f;
	scanf_s("%d%f", &e, &f);
	d=e+f;
	printf("d=%lf\ne=%d\nf=%f\n", d, e, f);
	return 0;
}