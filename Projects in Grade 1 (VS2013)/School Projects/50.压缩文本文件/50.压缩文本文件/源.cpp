#include "stdio.h"
#include "string.h"
#define N 10000
int main()
{
	char dic[N][80] = { { '\0' } }/*�ʵ�����*/, temp[81] = { '\0' }/*��ʱ���ʼĴ���*/,now/*��ĸ�Ĵ���*/;
	int diccount = 1/*�ʵ��½Ǳ������*/, tempc = 0/*temp������*/, check/*����������*/;
	int start = 0/*�жϵ�һ�������Ƿ���� ��0 ��1*/;
	while (1)
	{
		now = getchar();
		if (now == EOF)
			break;
		if ((now >= 'a'&&now <= 'z') || (now >= 'A'&&now <= 'Z'))//�ж��Ƿ�Ϊ��ĸ
		{
			temp[tempc] = now;//�洢����
			tempc++;
		}
		else//�������Ϊ����ĸʱ
		{
			temp[tempc] = '\0';
			for (check = 1; check < diccount;check++)//����Ƿ����ظ��� �����Զ�������һ�����ʵļ��
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
			putchar(now);//����ַ�
		}
	}
}