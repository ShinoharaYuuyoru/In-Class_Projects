#include "stdio.h"
#include "string.h"
#define N 50
int main()
{
	char string[5][N]/*输入的字符数组*/,save[N];
	int count/*单词个数计数器*/, i, j, k/*i,j,k为选择排序的计数器*/;
	for (count = 0; count <= 4; count++)
		scanf("%s", &string[count]);
	for (i = 0; i < 4; i++)
	{
		k = i;
		for (j = i + 1; j < 5; j++)
		{
			if (strcmp(string[j], string[k])>0)
				k = j;
		}
		if (k != i)
		{
			strcpy(save, string[k]);
			strcpy(string[k], string[i]);
			strcpy(string[i], save);
		}
	}
	for (count = 0; count <= 4; count++)
	{
		printf("%s\n", string[count]);
	}
}