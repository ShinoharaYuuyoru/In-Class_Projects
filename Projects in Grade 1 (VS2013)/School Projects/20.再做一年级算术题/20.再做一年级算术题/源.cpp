#include "stdio.h"
int main()
{
	int max = 0, min = 9, jg = 0, op=0;
	char c;
	for (;;)
	{
		scanf("%c", &c);
		if (c >= '0'&&c <= '9')
		{
			if (c - '0' > max)
				max = c - '0';
			if (c - '0' < min)
				min = c - '0';
		}
		else
		if (c == '+')
			op = '+';
		if (c == '-')
			op = '-';
		if (c == '*')
			op = '*';
		if (c == '/')
			op = '/';
		if (c == '%')
			op = '%';
		if (c == ',')
			continue;
		if (c == '=')
			break;
	}
	if (min == 0 && op == '/')
		printf("Error!\n");
	else
	{
		switch (op)
		{
		case '+':jg = max + min; break;
		case '-':jg = max - min; break;
		case '*':jg = max*min; break;
		case '/':jg = max / min; break;
		case '%':jg = max%min; break;
		}
		printf("%d%c%d=%d\n", max, op, min, jg);
	}
}