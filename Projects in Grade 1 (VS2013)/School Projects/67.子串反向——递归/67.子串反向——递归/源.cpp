/*
请编写一个递归函数 reverse(char str[], int start, int end) ，该函数的功能是将串 str 中下标从 start 开始到 end 结束的字符颠倒顺序。假设 start 和 end 都在合理的取值范围。

例如：

执行前：str[] = "0123456"；start = 1 ；end = 4

执行后：strr[] = "0432156"

要求在该函数中不使用新的数组，没有循环。

注意：只需要编写递归函数 reverse，系统中已经设置好了main函数。



测试用例 1	
0123456↵
1 4↵

0432156↵

测试用例 6	
0123456↵
6 10↵

0123456↵

测试用例 7	
0123456↵
0 10↵

6543210↵

*/


#include <stdio.h>  
#include <stdlib.h>  

void reverse(char *a, int s, int e);
int main()
{
	char str[100];
	int start, end;
	gets(str);
	scanf("%d%d", &start, &end);
	reverse(str, start, end);
	printf("%s\n", str);
	return 0;
}

void reverse(char *a, int s, int e)
{
	int save = 0, max = 0;
	while (a[max] != '\0')
		max++;//a[max]指向'\0'
	max--;
	if (s < max&&s < e)//如果开始的地方在数组内部  且start在end前
	{
		if (e <= max)//如果结束的地方在数组内部
		{
			save = a[s];
			a[s] = a[e];
			a[e] = save;
			reverse(a, s + 1, e - 1);
		}
		else//结束的地方不在数组内部 直接转用max来代替e
		{
			e = max;
			save = a[s];
			a[s] = a[e];
			a[e] = save;
			reverse(a, s + 1, e - 1);
		}
	}
}