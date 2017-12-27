/*
有一种特殊形式的字符串，其正反序相同，被称为“回文字符串”。例如LeveL就是一个回文字符串。

输入：
字符串

输出：
Yes或者No

说明：
如输出Yes，说明输入的字符串是一个回文字符串
输出No，说明输入的字符串不是一个回文字符串
请使用递归算法实现。


测试用例 1	
LeveL↵

Yes↵

测试用例 10	
↵

Yes↵

*/

#include "stdio.h"
#define N 1000

int judge(char *line);

int main()
{
	char line[N] = { '\0' };

	gets(line);
	if (judge(line) == 0)
		printf("No\n");
	else
		printf("Yes\n");
}

int judge(char *l)
{
	int i = 0, j = 0;
	while (l[j] != '\0')
		j++;
	j--;
	if (i < j)
	{
		if (l[i] == l[j])
		{
			l[j] = '\0';
			return judge(l + 1);
		}
		else
			return 0;
	}
	if (i >= j)
		return 1;
}