/*ȫ���������������и��̽�����յõ���������ռ��𰸣�Answer to the Ultimate Question of Life, the Universe and the Everything����

����һ�����֡�

��һ����λ��
��һ��ż��
���д�ɶ����ƣ���ǰ��0����0��1�ĸ���һ����
���д���Ľ��ƣ���ǰ��0������λ����һ����
����д��������ͬ����������ƽ����
������������
��������������ǣ�������ռ�����ʲô��
*/

#include "stdio.h" 

int binary(int n);
int forth(int n);
int main()
{
	int n = 10/*��*/;
	int a, b, c/*����������*/;
	for (n = 10; n <= 99; n = n + 2)
	{
		if (binary(n) == 1)//��������Ƶı�ʾ  
		{
			if (forth(n) == 1)//�������Ľ���Ҫ��  
			{
				for (a = 1; a <= 9; a++)
				{
					for (b = 1; b <= 9; b++)
					{
						for (c = 1; c <= 9; c++)
						{
							if (n == a*a + b*b + c*c)//����ƽ����Ҫ�� 
							{
								printf("%d\n", n);/*�˴�ʡ�������һ�������ļ��� ��Ϊ��ʣ�´�42�� ֱ���������*/
								return 0;
							}
							else continue;//������ƽ��������  ����  
						}
					}
				}
			}
			else
				continue;//�������Ľ���Ҫ��  
		}
		else//�����������Ҫ��  
			continue;
	}
}

int binary(int n)//���ж���������  
{
	int bina[7] = { 2, 2, 2, 2, 2, 2, 2 };
	int i = 0/*bina������½Ǳ������*/, i0 = 0, i1 = 0/*0��1����������*/;
	for (i = 0; n >= 1; i++)//¼��n�Ķ����Ʊ�ʾ  
	{
		bina[i] = n % 2;
		n = n / 2;
	}
	for (i = 0; bina[i] != 2 && i <= 6; i++)
	{
		if (bina[i] == 0)
			i0++;
		if (bina[i] == 1)
			i1++;
	}
	if (i0 == i1)
		return 1;
	else
		return 0;
}


int forth(int n)//�����Ľ������Ҫ��Ľ�� 
{
	int forth[4] = { 5, 5, 5, 5 };
	int same/*��4�����µĵ�һ������*/;
	int i/*forth�����½Ǳ������*/;
	for (i = 0; n >= 1; i++)
	{
		forth[i] = n % 4;
		n = n / 4;
	}
	same = forth[0];
	for (i = 1; forth[i] != 5 && i <= 3; i++)
	{
		if (forth[i] != same)
			return 0;//��һ������ͬ�ľͷ���0 
	}
	return 1;//�Ľ����µ����ֶ���ͬ����1 
}