/*view plainprint ?*/
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>  
int countsub(char *str, char *ss);
int main()
{
	char s1[1000] = { 0 }, s2[100] = { 0 };
	gets(s1);
	gets(s2);
	printf("%d\n", countsub(s1, s2));
}
int countsub(char *str, char *ss)
{
	int count = 0;
	char *sscpy;
	sscpy = ss;
	for (; *str != '\0';*(str++))
	{
		for (sscpy = ss; *sscpy != '\0'; *(str++), *(sscpy++))
		{
			if (*str == *sscpy)
			{
				if (*(sscpy + 1) == '\0')
				{
					count++;
					break;
				}
				continue;
			}
			else
			{
				if (count >= 1)
				{
					return count;
				}
				else
					break;
			}
		}
	}
	return count;
}
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */