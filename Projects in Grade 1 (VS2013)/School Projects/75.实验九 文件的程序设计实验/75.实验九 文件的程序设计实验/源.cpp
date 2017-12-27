/*一、实验目的
通过对文件的读写、文件的二进制读写的操作练习，掌握文件的访问顺序和访问方法，学习二进制文件的存储特点。

二、实验内容

1、题目：文件读写

实验分析及提示：

程序1是一段写入文件的代码，请阅读该代码并回答程序后面的问题。*/

/*程序1*/
#include <stdio.h>

#include <stdlib.h>

int main()

{

	FILE *fp;

	char ch;

	if ((fp = fopen("demo.txt", "w")) == NULL) /* 判断文件是否成功打开 */

	{

		printf("Failure to open demo.txt!\n");

		exit(0);

	}

	ch = getchar();

	while (ch != '\n')   /* 若键入回车换行符则结束键盘输入和文件写入 */

	{

		fputc(ch, fp);

		ch = getchar();

	}

	fclose(fp);           /* 关闭由函数fopen()打开的文件demo.txt */

	return 0;

}

/*1．1文件demo.txt的路径是什么？如果我想把该文件存到桌面上，该如何操作？

1.2 请分两次写入文件，例如第一次写入“12”，第二次写入“34”，再打开demo.txt,文件里面保存的是什么呢？

1.3 如果希望把每次输入都添加到文件的尾部该如何修改程序？写出你修改的语句。*/


/*2、题目：二进制文件的读写。

程序2是写入128个字符的ASCII码值，以二进制文件存储，并将文件中的字符输出到屏幕上，程序会判断是否可打印字符，若是可打印字符，则显示该字符，若非可打印字符，则显示该字符的ASCII码值。请完成程序填空，并回答程序后面的问题。*/
/*程序2*/

#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

int main()

{

	FILE *fp;

	char ch;

	int i;

	if ((fp = fopen("demo.bin", "wb")) == NULL) /* 以二进制写方式打开文件 */

	{

		printf("Failure to open demo.bin!\n");

		exit(0);

	}

	for (i = 0; i<128; i++)

	{

		fputc(i, fp);     /* 将字符的ASCII码值写入文件 */

	}

	fclose(fp);

	if ((fp = fopen("demo.bin", "rb")) == NULL) /* 以二进制读方式打开文件 */

	{

		printf("Failure to open demo.bin!\n");

		exit(0);

	}

	while ((ch = fgetc(fp)) != EOF)     /* 从文件中读取字符直到文件末尾 */

	{

		if (isprint(ch))         /* 判断是否是可打印字符 */

		{

			printf("%c\t", ch); /* 若是可打印字符，则显示该字符 */

		}

		else

		{

			printf("%d\t", ch); /*若非可打印字符，则显示该字符的ASCII码值*/

		}

	}

	fclose(fp);

	system("pause");

	return 0;

}