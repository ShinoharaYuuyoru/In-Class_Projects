#include "stdio.h"
#define N 100
int main()
{
	char in[N]/*�����ַ���*/;
	int i/*in�������������*/, j/*ou�������������*/,m/*�ж��ظ�������*/, ot/*���������*/, ou[N]/*�������*/;
	scanf("%s", &in);
	ou[0] = in[0]-' '+32;
	j = 0;
	for (i = 1; in[i] != '\0'; i++)
	{
		for (m = 0; m <= j; m++)
		{
			if (in[i] - ' ' + 32 != ou[m])
			{
				if (m == j)
				{
					ou[j + 1] = in[i] - ' ' + 32;
					j++;
					break;
				}
			}
			if (in[i] - ' ' + 32 == ou[m])
				break;
		}
	}
	for (ot = 0; ot <= j;ot++)
	printf("%c", ou[ot]);
	printf("\n");
}