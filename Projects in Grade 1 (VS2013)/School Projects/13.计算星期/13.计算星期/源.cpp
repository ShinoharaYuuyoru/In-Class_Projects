#include "stdio.h"
int main()
{
	int year, day, week,month,mont[13] = { 0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },i,montd=0;
	scanf("%d%d%d", &year, &month, &day);
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		mont[2] = 29;
	if (month >= 13)
	    {
		printf("month is error.\n"); goto end;
	    }
	if (day > mont[month])
	    {
		printf("day is error.\n"); goto end;
	    }
	for (i=0;i<month;i++)
		montd = montd + mont[i];
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	    day = (year-1900) * 365 + ((year-1900) / 4 - 1) + montd+day;
	else if (year  % 100 == 0)
		      day = (year - 1900) * 365 + ((year - 1900) - 1) / 4 + montd + day;
	     else day = (year - 1900) * 365 + (year - 1900) / 4 + montd + day;
		week = day % 7;
		printf("%d\n", week);
		return 0;
	end:;
}