#include "stdio.h"
int main()
{
	double a, b, c, d, e;
	printf("Please input four float numbers£º");
	scanf_s("%lf%lf%lf%lf", &a, &b, &c, &d);
	e = (a + b)*(a - b) + c / d;
	printf("The result is %lf\n",e);
}