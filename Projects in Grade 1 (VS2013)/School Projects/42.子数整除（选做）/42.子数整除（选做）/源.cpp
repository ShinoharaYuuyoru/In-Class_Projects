#include "stdio.h"
int main()
{
	int k/*输入值k*/, i/*10000到30000的计数器*/, n1, n2, n3/*取位后的数*/;
	scanf("%d", &k);
	for (i = 10000; i <= 30000; i++)
	{
		n1 = i / 100;
		n2 = (i / 10) % 1000;
		n3 = i % 1000;
		if (n1%k == 0 && n2%k == 0 && n3%k == 0)
			printf("%d\n", i);
		else continue;
	}
}