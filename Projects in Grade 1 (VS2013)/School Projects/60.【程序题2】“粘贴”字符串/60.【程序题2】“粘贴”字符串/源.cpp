/*编程，输入两个字符串s1、s2和s1中任意字符k，在s1中的指定字符k的位置处插入字符串s2并输出。

例如S1=“abcde”，S2=“12345”，输入b，则输出“ab12345cde”，

若输入的字符不在s1中，则在s1的结尾处插入s2。例如S1="abcde",S2="12345",输入字符k，则输出“abcde12345”.*/
#include "stdio.h"
#include "string.h"
#define N 1000
int main()
{
	char s1[N] = { '\0' }, s2[N] = { '\0' }/*定义两个字符串*/, cha/*从s1的哪个字符插入*/, save[N] = { '\0' }/*s1剩下数组临时存储器*/;
	int s1c/*s1字符数组计数器*/,savec/*save字符数组下角标记录器*/;

	gets(s1);
	gets(s2);//录入s1,s2
	scanf("%c", &cha);//从s1的哪个字符插入
	for (s1c = 0; s1[s1c] != '\0'; s1c++)
	{
		if (s1[s1c] == cha)//如果在s1找到了相应的字符
		{
			for (s1c++, savec = 0; s1[s1c] != '\0'; s1c++, savec++)//将s1后边的字符复制到save字符数组中  并且清零
			{
				save[savec] = s1[s1c];
				s1[s1c] = '\0';
			}
			strcat(s1, s2);
			strcat(s1, save);
			printf("%s\n", s1);
			return 0;
		}
	}
	strcat(s1, s2);//到此 应为没有找到相同的字符 则直接连接s1 s2
	printf("%s\n", s1);
	return 0;
}



/*内口酱的代码*/
//#include "stdio.h"
//#include "string.h"
//int main()
//{
//	char s1[20], s2[20], k;
//	int i, n, flag1 = 0, flag2 = 0;
//	gets(s1);
//	n = strlen(s1);
//	gets(s2);
//	scanf("%c", &k);
//	s1[6] = 'P';
//	for (i = 0; i < n; i++)//此处出错  从i<=n 改为 i<n
//	{
//		printf("%c", s1[i]);
//		if (s1[i] == k&&flag2 == 0)
//		{
//			printf("%s", s2);
//			flag1 = 1;
//			flag2 = 1;
//		}
//	}
//	if (flag1 == 0)
//	{
//		printf("%s", s2);
//	}
//	printf("\n");
//	return 0;
//}