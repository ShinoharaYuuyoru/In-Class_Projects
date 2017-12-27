#include "stdio.h"
#define N 6
int main()
{
	char number[N]/*车号数组*/;
	int count/*下角标计数器*/, charnumber = 0/*字母个数计数器*/, mnumber = 0/*数字个数计数器*/;
	gets(number);
	if (number[4] > 57 || number[4] < 48)
	{
		printf("no.\n");
		return 0;
	}
	for (count = 0; count <= 4; count++)
	{
		if ((number[count] >= 65 && number[count] <= 90)&&number[count]!=73&&number[count]!=79)
		{
			charnumber++;
		}
		else
		{
			if (number[count] >= 48 && number[count] <= 57)
				mnumber++;
		}
	}
	if (charnumber == 2 && mnumber == 3)
		printf("ok.\n");
	else
		printf("no.\n");
}