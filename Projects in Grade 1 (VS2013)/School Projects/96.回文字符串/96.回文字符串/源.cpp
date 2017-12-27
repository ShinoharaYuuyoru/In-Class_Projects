#include  "stdio.h"
#define N 1000

int main()
{
	char ch[N];//ÊäÈë×Ö·û´®
	int start, end;

	scanf("%s", ch);

	for (end = 0; ch[end] != '@'; end++);
	end--;

	for (start = 0; start < end; start++, end--)
	{
		if (ch[start] != ch[end])
		{
			printf("No.\n");
			return 0;
		}
	}
	printf("Yes.\n");
	return 0;
}