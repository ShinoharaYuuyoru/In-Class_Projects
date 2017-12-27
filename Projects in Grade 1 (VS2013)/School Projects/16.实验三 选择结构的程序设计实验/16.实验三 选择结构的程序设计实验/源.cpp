/*二次方程求解问题*/
#include "stdio.h"
#include "math.h"
int main(void)
{
	int a, b, c;
	double d, e, f;
	scanf("%d%d%d", &a, &b, &c);
	d = a, e = b, f = c;
	if (a == 0)
	   if (b == 0)
		printf("Input error!\n");
	   else printf("x=%.6f\n", -f / e);
	else if (b*b - 4 * a*c == 0)
		    printf("x1=x2=%.6f\n", 0 - e / (2 * d));
	     else if (b*b - 4 * a*c > 0)
		         printf("x1=%.6f\nx2=%.6f\n", (-e + sqrt(e*e - 4 * d*f)) / (2 * d), (-e - sqrt(e*e - 4 * d*f)) / (2 * d));
	          else if (b == 0)
		              printf("x1=%0.6fi\nx2=-%0.6fi\n"), sqrt(f / d), sqrt(f / d);
	               else
		                printf("x1=%.6f+%.6fi\nx2=%.6f+%.6fi\n", -e / (2 * d), sqrt(4 * d*f - e*e) / (2 * d), -e / (2 * d), -sqrt(4 * d*f - e*e) / (2 * d));
}