#include "stdio.h"
#define N 81
int main()
{
	char s[N] = { '0' }/*��һ���ַ�*/, t[N] = { '0' }/*�ڶ����ַ�*/, u[N] = { '0' }/*����ַ�*/;
	int sc/*s���������*/, tc/*t���������*/, uc/*u���������*/;
	int sn/*s�������ݸ���*/, tn/*t�������ݸ���*/, un/*u�������ݸ���*/;
	for (sc = 1; s[sc - 1] != '\n'; sc++)
		scanf("%c", &s[sc]);
		sn = sc - 1;
	for (tc = 1; t[tc - 1] != '\n'; tc++)
		scanf("%c", &t[tc]);
		tn = tc - 1;
	for (uc = 1;;)
	{
		for (sc = 1; sc <= sn; sc++)
		{
			for (tc = 1; tc <= tn; tc++)
			{
				if (s[sc] == t[tc])
					break;
				if (s[sc] != t[tc])
				{
					if (tc != tn)
						continue;
					else
					{
						u[uc] = s[sc];
						uc++;
					}
				}
			}
		}
		if (sc > sn)
		{
			un = uc - 1;
			break;
		}
	}
	for (uc = 1; uc <= un; uc++)
		printf("%c", u[uc]);
	printf("\n");
}