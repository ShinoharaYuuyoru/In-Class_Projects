/*��̣����������ַ���s1��s2��s1�������ַ�k����s1�е�ָ���ַ�k��λ�ô������ַ���s2�������

����S1=��abcde����S2=��12345��������b���������ab12345cde����

��������ַ�����s1�У�����s1�Ľ�β������s2������S1="abcde",S2="12345",�����ַ�k���������abcde12345��.*/
#include "stdio.h"
#include "string.h"
#define N 1000
int main()
{
	char s1[N] = { '\0' }, s2[N] = { '\0' }/*���������ַ���*/, cha/*��s1���ĸ��ַ�����*/, save[N] = { '\0' }/*s1ʣ��������ʱ�洢��*/;
	int s1c/*s1�ַ����������*/,savec/*save�ַ������½Ǳ��¼��*/;

	gets(s1);
	gets(s2);//¼��s1,s2
	scanf("%c", &cha);//��s1���ĸ��ַ�����
	for (s1c = 0; s1[s1c] != '\0'; s1c++)
	{
		if (s1[s1c] == cha)//�����s1�ҵ�����Ӧ���ַ�
		{
			for (s1c++, savec = 0; s1[s1c] != '\0'; s1c++, savec++)//��s1��ߵ��ַ����Ƶ�save�ַ�������  ��������
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
	strcat(s1, s2);//���� ӦΪû���ҵ���ͬ���ַ� ��ֱ������s1 s2
	printf("%s\n", s1);
	return 0;
}



/*�ڿڽ��Ĵ���*/
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
//	for (i = 0; i < n; i++)//�˴�����  ��i<=n ��Ϊ i<n
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