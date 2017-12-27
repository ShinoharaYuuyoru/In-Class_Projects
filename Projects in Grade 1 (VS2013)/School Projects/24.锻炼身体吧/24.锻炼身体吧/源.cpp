#include "stdio.h"
int main()
{
	int a, b, c,i=0;
	scanf("%d", &c);
	for (;c>=3;c--)
	for (a = 1;a<=c-2;a++)
	{
		for (b=c-1; a <= b; b--)
		{
			if (c*c == a*a + b*b)
			{
				i++;
			}
		}
	}
	printf("%d\n", i);
}