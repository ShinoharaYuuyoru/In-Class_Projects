#include "stdio.h"
#define N 13
int main()
{
	int year, day, daysum, week,yearday,monthday[N] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int daycount/*具体年的日计数器*/,monthcount/*monthday数组的计数器*/,i/*符合个数计数器*/;
	scanf("%d", &year);
	yearday = 365;
	i = 0;
	if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
	{
		monthday[2] = 29;
		yearday++;
	}
	daysum = (year - 1900) * 365 + (year - 1900 - 1) / 4;
	for (daycount = 1; daycount <= yearday; daycount++)
	{
		daysum++;
		week = daysum % 7;
		for (day = daycount, monthcount = 0;; monthcount++)
		{
			day = day - monthday[monthcount];
			if (day > monthday[monthcount + 1])
				continue;
			else break;
		}
		if (week == 5 && day == 13)
			i++;
	}
	if (i == 1)
	{
		printf("There is %d Black Friday in year %d.\n", i, year);
		printf("It is:\n");
	}
	else
	{
		printf("There are %d Black Fridays in year %d.\n", i, year);
		printf("They are:\n");
	}
	daysum = (year - 1900) * 365 + (year - 1900 - 1) / 4;
	for (daycount = 1; daycount <= yearday; daycount++)
	{
		daysum++;
		week = daysum % 7;
		for (day = daycount, monthcount = 0;; monthcount++)
		{
			day = day - monthday[monthcount];
			if (day > monthday[monthcount + 1])
				continue;
			else break;
		}
		if (week == 5 && day == 13)
			printf("%d/%d/%d\n", year, monthcount + 1, day);
	}
}