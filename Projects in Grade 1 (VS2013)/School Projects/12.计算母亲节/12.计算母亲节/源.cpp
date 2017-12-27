#include "stdio.h"
int main()
{
	int year, day, may1, mother;
	scanf("%d", &year);
	year = year - 1900;
	if (((year+1900)% 4 == 0 && (year+1900) % 100 != 0)||((year+1900) % 400 == 0))
		day = year * 365 +(year/4-1)+ 122 ;
	else if ((year+1900)%100==0)
		day = year * 365 + (year-1) / 4 + 121;
		else day = year * 365 +year/4+ 121;
	may1 = day % 7;
	if (may1 == 0)
		may1 = 7;
	mother = 15 - may1;
	printf("%d\n", mother);
}