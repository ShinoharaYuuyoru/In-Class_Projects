/*#include <stdio.h>

#include <stdlib.h>

int main()
{
	int a[5];//û�г�ʼ����ֵ��
	int i;
	for (i = 0; i<10; i++)   
		printf("%d\n",a[i]); //���10������-----��1��
	for (i = 0; i<5; i++)   
		scanf("%d",&a[i]);//����5������--------��2��
	for (i = 0; i<5; i++)  
		printf("%d",a[i]);//���10������-------��3��
	return 0;
}*///��һ��

//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//	char str[100], c;
//	int i, j;
//	printf("Enter string:");
//	gets(str);
//	for (i = 0;str[i]!='\0'; i++); /* ��λ���ַ�����β��'\0'*/
//	i--;                             /* Ѱ�ҵ�'\0'��ǰһ���ַ�*/
//	for (j = 0; j < i; i--, j++) /* ������������*/
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
	char str[100], sub[100]; /* �ַ�����str��������ַ�����sub�������m��n֮����Ӵ� */
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
		for (p = 0; k<n; k++, p++)          /* �����Ӵ�*/
			sub[p] = str[k];
		sub[p] = '\0';      /* �ڴ�sub�ĺ�����ϴ�������� */
		printf("sub = %s\n", sub);
	}
}