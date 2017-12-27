#include "stdio.h"
#include "string.h"
#define N 10000
int main()
{
	char dic[N][80] = { { '\0' } }/*词典数组*/, temp[81] = { '\0' }/*临时单词寄存器*/,now/*字母寄存器*/;
	int diccount = 1/*词典下角标计数器*/, tempc = 0/*temp计数器*/, check/*检索计数器*/;
	int start = 0/*判断第一个单词是否出现 无0 有1*/;
	while (1)
	{
		now = getchar();
		if (now == EOF)
			break;
		if ((now >= 'a'&&now <= 'z') || (now >= 'A'&&now <= 'Z'))//判断是否为字母
		{
			temp[tempc] = now;//存储单词
			tempc++;
		}
		else//如果输入为非字母时
		{
			temp[tempc] = '\0';
			for (check = 1; check < diccount;check++)//检查是否有重复的 并且自动跳过第一个单词的检查
			{
				if (strcmp(dic[check], temp) == 0)
				{
					printf("%d", check);
					start++;
				}
			}
			if (start == 0)
			{
				if (temp[0] != '\0')
				{
					printf("%s", temp);
					strcpy(dic[diccount], temp);
					diccount++;
				}
			}
			tempc = 0;
			start = 0;
			putchar(now);//输出字符
		}
	}
}