/*#include <stdio.h>

#include <stdlib.h>

int main()
{
	int a[5];//没有初始化赋值；
	int i;
	for (i = 0; i<10; i++)   
		printf("%d\n",a[i]); //输出10个整数-----【1】
	for (i = 0; i<5; i++)   
		scanf("%d",&a[i]);//输入5个整数--------【2】
	for (i = 0; i<5; i++)  
		printf("%d",a[i]);//输出10个整数-------【3】
	return 0;
}*///第一题

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//	char str[100], c;
//	int i, j;
//	printf("Enter string:");
//	gets(str);
//	for (i = 0;str[i]!='\0'; i++); /* 定位到字符串串尾的'\0'*/
//	i--;                             /* 寻找到'\0'的前一个字符*/
//	for (j = 0; j < i; i--, j++) /* 进行逆序排列*/
//	{
//		c=str[i];
//		str[i] = str[j];
//		str[j]=c;
//	}
//	printf("Output string : %s\n", str);
//	return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
int main()
{
	char str[100], sub[100]; /* 字符数组str用来存放字符串，sub用来存放m和n之间的子串 */
	int m, n, k, p;
	printf("Enter string:");
	gets(str);
	/*printf("%d\n", strlen(str));*/
	printf("Enter m n : ");
	scanf("%d%d", &m, &n);
	if (m<0 || n>strlen(str) - 1)
		printf("Error!\n");
	else
	{
		for (k = 0; k<m &&str[k] != '/0'; k++);
		k++;
		for (p = 0; k<n; k++, p++)          /* 复制子串*/
			sub[p] = str[k];
		sub[p] = '\0';      /* 在串sub的后面加上串结束标记 */
		printf("sub = %s\n", sub);
	}
}