#include "stdio.h"
#define W 1000//λ��
int main()
{
	int n/*��*/;
	int i/*ԭʼ��������λ��������*/,j/*eorE������*/,k/*��λ������*/,l/*���������*/,m/*��λ����������*/,o/*��λλ��������*/;
	char num[W]/*ԭʼ����*/, e/*�ж��ַ�eorE*/;
	char save/*��ʱ�洢��*/;
	for (i = 0; i <= W; i++)
		num[i] = '0';
	for (i = 1; num[i-1] != ' '; i++)
		scanf("%c", &num[i]);
	num[i - 1] = '\0';
	i = i - 2;/*ԭʼ����¼�����*/
	for (;;)
	{
		scanf("%c", &e);
		if (e != ' ')
			break;
	}
	scanf("%d", &n);
	if (n == 0)
	{
		for (i = 1; i <= 10; i++)
			printf("%c", num[i]);/*��n=0ʱ�����ԭʼ���ݵ�ǰ10λ*/
	}
	if (n > 0)
	{
		save = num[2];
		for (i = 2, k = 1; k <= n; i++, k++)
		{
			num[i] = num[i + 1];
		}
		num[i] = '.';
		for (i++; i <= W; i++)
			num[i] = '0';
		for (l = 1; l <= i+8; l++)
			printf("%c", num[l]);
	}/*n>0ʱ������*/
	if (n < 0)
	{
		n = 0 - n;
		for (i = 2; num[i] != '\0'; i++)
		{
			num[i] = num[i + 1];
		}
		for (m = 1; m <= n; m++)
		{
			for (o = 1; num[o] != '\0';o++)
			for (; o >= 1; o--)
			{
				num[o + 1] = num[o];
			}
		}
		num[1] = '.';
		for (i = 2; i <= n; i++)
			num[i] = '0';
		for (i = 0; num[i] != '\0'; i++)
			printf("%s", num[i]);
	}
}