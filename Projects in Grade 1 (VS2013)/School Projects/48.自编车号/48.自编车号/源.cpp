#include "stdio.h"
#define N 6
int main()
{
	char number[N]/*��������*/;
	int count/*�½Ǳ������*/, charnumber = 0/*��ĸ����������*/, mnumber = 0/*���ָ���������*/;
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