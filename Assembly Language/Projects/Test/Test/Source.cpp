#include "stdio.h"
#include "string.h"

int main()
{
	int	Input = 0;
	int	Output = 123456;

	char	str1[5] = "abc";
	char	str2[5];

	scanf("%d", &Input);

	printf("%d\n", Output);

	strcpy(str2, str1);
}