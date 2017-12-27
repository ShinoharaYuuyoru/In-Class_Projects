/*输入顶行字符和图形的高。输出如下例（顶行字符为'A'，图形的高为5）所示的图形，

    A
   BCD
  EFGHI
 JKLMNOP
QRSTUVWXY*/
#include "stdio.h"
int main()
{
	char word/*输出字母*/;
	int n/*行数*/;
	int spacec/*输出空格计数器*/,wordc/*字母计数器*/,nc/*行数计数器*/;

	scanf("%c%d", &word, &n);

	for (nc = 1; nc <= n; nc++)//每一行
	{
		for (spacec = 1; spacec <= n - nc; spacec++)//输出前置空格
		{
			printf(" ");
		}
		for (wordc = 1; wordc <= nc * 2 - 1; wordc++)
		{
			printf("%c", word);
			word++;
			if (word == '[')
				word = 'A';
		}
		printf("\n");
	}
}