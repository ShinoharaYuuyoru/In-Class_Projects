#include "stdio.h"
#include "string.h"
#include "math.h"
#define N 20

int main()
{
	char inp[N];//输入流
	int bin[N];//二进制记录
	int len;//位数
	int num;//次序
	int search;//位数确定

	while (scanf("%s", inp) != EOF)
	{
		len = strlen(inp);

		num = pow(2.0, len) - 1;

		for (search = len - 1; search >= 0; search--)
		{
			if (inp[search] == '4')
			{
				bin[search] = 0;
			}
			else
			{
				if (inp[search] == '7')
				{
					bin[search] = 1;
				}
				else
				{
					printf("Error.\n");
					return 0;
				}
			}

			num = num + bin[search] * pow(2.0, len - search - 1);
		}

		printf("%d\n", num);
	}
}