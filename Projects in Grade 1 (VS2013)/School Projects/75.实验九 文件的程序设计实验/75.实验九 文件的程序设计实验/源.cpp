/*һ��ʵ��Ŀ��
ͨ�����ļ��Ķ�д���ļ��Ķ����ƶ�д�Ĳ�����ϰ�������ļ��ķ���˳��ͷ��ʷ�����ѧϰ�������ļ��Ĵ洢�ص㡣

����ʵ������

1����Ŀ���ļ���д

ʵ���������ʾ��

����1��һ��д���ļ��Ĵ��룬���Ķ��ô��벢�ش�����������⡣*/

/*����1*/
#include <stdio.h>

#include <stdlib.h>

int main()

{

	FILE *fp;

	char ch;

	if ((fp = fopen("demo.txt", "w")) == NULL) /* �ж��ļ��Ƿ�ɹ��� */

	{

		printf("Failure to open demo.txt!\n");

		exit(0);

	}

	ch = getchar();

	while (ch != '\n')   /* ������س����з����������������ļ�д�� */

	{

		fputc(ch, fp);

		ch = getchar();

	}

	fclose(fp);           /* �ر��ɺ���fopen()�򿪵��ļ�demo.txt */

	return 0;

}

/*1��1�ļ�demo.txt��·����ʲô���������Ѹ��ļ��浽�����ϣ�����β�����

1.2 �������д���ļ��������һ��д�롰12�����ڶ���д�롰34�����ٴ�demo.txt,�ļ����汣�����ʲô�أ�

1.3 ���ϣ����ÿ�����붼��ӵ��ļ���β��������޸ĳ���д�����޸ĵ���䡣*/


/*2����Ŀ���������ļ��Ķ�д��

����2��д��128���ַ���ASCII��ֵ���Զ������ļ��洢�������ļ��е��ַ��������Ļ�ϣ�������ж��Ƿ�ɴ�ӡ�ַ������ǿɴ�ӡ�ַ�������ʾ���ַ������ǿɴ�ӡ�ַ�������ʾ���ַ���ASCII��ֵ������ɳ�����գ����ش�����������⡣*/
/*����2*/

#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

int main()

{

	FILE *fp;

	char ch;

	int i;

	if ((fp = fopen("demo.bin", "wb")) == NULL) /* �Զ�����д��ʽ���ļ� */

	{

		printf("Failure to open demo.bin!\n");

		exit(0);

	}

	for (i = 0; i<128; i++)

	{

		fputc(i, fp);     /* ���ַ���ASCII��ֵд���ļ� */

	}

	fclose(fp);

	if ((fp = fopen("demo.bin", "rb")) == NULL) /* �Զ����ƶ���ʽ���ļ� */

	{

		printf("Failure to open demo.bin!\n");

		exit(0);

	}

	while ((ch = fgetc(fp)) != EOF)     /* ���ļ��ж�ȡ�ַ�ֱ���ļ�ĩβ */

	{

		if (isprint(ch))         /* �ж��Ƿ��ǿɴ�ӡ�ַ� */

		{

			printf("%c\t", ch); /* ���ǿɴ�ӡ�ַ�������ʾ���ַ� */

		}

		else

		{

			printf("%d\t", ch); /*���ǿɴ�ӡ�ַ�������ʾ���ַ���ASCII��ֵ*/

		}

	}

	fclose(fp);

	system("pause");

	return 0;

}