/**#include "stdio.h"
#define PI 3.1415926
int main()
{
	int a, b;
	double c,d;
	scanf_s("%d", &a);
	scanf_s("%d", &b);
	c = 2 * PI*a*b;
	d = PI*a*a*b;
	printf("s=%.2f,v=%.2f\n", c, d);
	return 0;
}*/

#include<stdio.h>
#define PAI  3.1415926
int main()
{
	int r, h;
	double s, v;
	scanf_s("%d %d",&r,&h);
	s = 2 * PAI*r*h;
	v = PAI*r*r*h;
	printf("s=%.2f,v=%.2f\n",s,v);
	return 0;
}