/*���붥���ַ���ͼ�εĸߡ�����������������ַ�Ϊ'A'��ͼ�εĸ�Ϊ5����ʾ��ͼ�Σ�

    A
   BCD
  EFGHI
 JKLMNOP
QRSTUVWXY*/
#include "stdio.h"
int main()
{
	char word/*�����ĸ*/;
	int n/*����*/;
	int spacec/*����ո������*/,wordc/*��ĸ������*/,nc/*����������*/;

	scanf("%c%d", &word, &n);

	for (nc = 1; nc <= n; nc++)//ÿһ��
	{
		for (spacec = 1; spacec <= n - nc; spacec++)//���ǰ�ÿո�
		{
			printf(" ");
		}
		for (wordc = 1; wordc <= nc * 2 - 1; wordc++)
		{
			printf("%c", word);
			word++;
			if (word == '[')
				word = 'A';
		}
		printf("\n");
	}
}