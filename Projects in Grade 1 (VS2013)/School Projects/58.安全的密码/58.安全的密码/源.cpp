/*���ŵ����豸�Ĺ㷺���ã�����Ҳ��������ÿ���˵�������������룬������ϵ��������˽������ϵ�����˵ĲƲ��Ͱ�ȫ��һ����ȫ�����룬����ɴ�Сд��ĸ�����ֻ������ɡ�����Խ��������ַ����䰲ȫ�Ծ�Խ�ߡ�ͬʱ���뻹��Ҫ��һ���ĳ��ȣ�ͨ������Ҫ���������ϵ��ַ���ɡ�

������ÿ���˶�ϲ���������ӵ����룬�ܶ��������������ʱ��ϲ��ʹ���Լ������ֻ������գ������Ǻܴ�İ�ȫ������

����
������������һ�����罻��ϵͳ��Ϊ�˱�֤�û������밲ȫ������Ҫһ�������ж��û��Լ����õ������Ƿ�ȫ���������ȫ���������ʾ�����������������������æ���һ�����������������⡣

Ӧ���������µĹ������ж������Ƿ�ȫ��

������볤��С�� 6 λ���򲻰�ȫ
������������ַ�ֻ��һ�࣬�򲻰�ȫ
������������ַ������࣬��Ϊ�жȰ�ȫ
������������ַ�����������ϣ���Ϊ��ȫ
ͨ����������Ϊ���֡���д��ĸ��Сд��ĸ����������Ϊ���಻ͬ���ַ���

����
����ĵ�һ����һ������ N�����������ж��������롣���� N ��������� N �����룬ÿ������ĳ��Ⱦ�С�� 20 ���ַ���

���
���ÿһ�������жϲ�������Ƿ�ȫ�����ڲ���ȫ��������� "Not Safe"�������жȰ�ȫ��������� "Medium Safe"�����ڰ�ȫ��������� "Safe"

��������

4
1234
abcdef
ABC123
1#c3Gh

�������
Not Safe
Not Safe
Medium Safe
Safe


�������� 1	���ı���ʽ��ʾ
10?
abcDEF?
ABC?
qw?
`?
ABCDEFGHIJKLMNOPQRST?
12345678901234567890?
1aB?
1 B?
a X   ?
qwe123%^&ABC?

���ı���ʽ��ʾ
Medium Safe?
Not Safe?
Not Safe?
Not Safe?
Not Safe?
Not Safe?
Safe?
Not Safe?
Safe?
Safe?
1��	64M	0*/
#include "stdio.h"
#include "string.h"
int main()
{
	char password[21]/*�����ַ�����*/;
	int n/*�����������*/, len = 0/*���볤��*/, smallword = 0, bigword = 0, math = 0, others = 0/*�����ַ� ֻ��Ϊ0��1  ����1 ����0*/, all = 0/*�����в�ͬ�ַ�����*/;
	int point/*����ÿһλ������*/;

	scanf("%d", &n);/*������������*/
	getchar();
	for (; n >= 1;n--)
	{
		smallword = 0;
		bigword = 0;
		math = 0;
		others = 0;
		gets(password);
		len = strlen(password);//ȡ���볤��
		if (len < 6)//������λ��С��6ʱ ֱ���ж�NOT SAFE ��������һ��������ж�
		{
			printf("Not Safe\n");
			continue;
		}
		else//�������λ�����ڵ���6
		{
			for (point = 0; password[point] != '\0'; point++)//����ÿһλ�ж�
			{
				if (password[point] >= 97 && password[point] <= 122)//�Ƿ�ΪСд��ĸ
				{
					smallword = 1;
					continue;
				}
				if (password[point] >= 65 && password[point] <= 90)//�Ƿ�Ϊ��д��ĸ
				{
					bigword = 1;
					continue;
				}
				if (password[point] >= 48 && password[point] <= 57)//�Ƿ�Ϊ����
				{
					math = 1;
					continue;
				}
				if (1)//��ǰ�����ж϶�û�н��� ���ж�Ϊ�������
				{
					others = 1;
					continue;
				}
			}
			all = smallword + bigword + math + others;
			if (all == 1)
			{
				printf("Not Safe\n");
			}
			if (all == 2)
			{
				printf("Medium Safe\n");
			}
			if (all >= 3)
			{
				printf("Safe\n");
			}
		}
	}
	return 0;
}