#include "stdio.h"
int main()
{
	char cha/*���������ĸ*/,chaplus/*ÿһ�е���ĸ*/;
	int n/*����ġ��߳���*/, line/*��*/,spacehead/*ÿһ�п�ʼʱ�Ŀո�����*/,spacemid/*ÿһ���м�Ŀո�����*/;
	int linecount/*�м�����*/,chacount/*��ĸ������*/,spaceheadcount/*ÿһ�п�ʼʱ�Ŀո������*/,spacemidcount/*ÿһ���м�Ŀո������*/;
	scanf("%d %c", &n, &cha);
	if (cha<'A' || cha>'Z')
	{
		printf("input error.\n");
		return 0;
	}
	line = n - 1;//ȷ����������
	for (chaplus = cha, chacount = 1; chacount <= line;chacount++)//ȷ����һ�е������ĸ
	{
		chaplus++;
		if (chaplus == '[')
			chaplus = 'A';
	}
	for (linecount = 1; linecount <= line; linecount++, chaplus--)//ȷ����linecount�е������ĸ
	{
		if (chaplus == '@')
			chaplus = 'Z';
		spacehead = linecount - 1;//ȷ��ÿһ�е�ǰ�ÿո���
		spacemid = (line - linecount) * 2 + 1;//ȷ��ÿһ�е��м�ո���
		for (spaceheadcount = 1; spaceheadcount <= spacehead; spaceheadcount++)//���ǰ�ÿո�
			printf(" ");
		printf("%c", chaplus);//�����һ����ĸ
		for (spacemidcount = 1; spacemidcount <= spacemid; spacemidcount++)//����м�ո�
			printf(" ");
		printf("%c\n", chaplus);//����ڶ�����ĸ������
	}
	for (spaceheadcount = 1; spaceheadcount <= line; spaceheadcount++)//�����n(�߳�)�е�ǰ�ÿո�
		printf(" ");
	printf("%c\n", cha);
	chaplus = cha;
	for (linecount = 1; linecount <= line; linecount++)//ȷ����linecount�е������ĸ
	{
		chaplus--;
		if (chaplus == '@')
			chaplus = 'Z';
		spacehead = line - linecount;//ȷ��ÿһ�е�ǰ�ÿո���
		spacemid = linecount * 2 - 1;//ȷ��ÿһ�е��м�ո���
		for (spaceheadcount = 1; spaceheadcount <= spacehead; spaceheadcount++)//���ǰ�ÿո�
			printf(" ");
		printf("%c", chaplus);//�����һ����ĸ
		for (spacemidcount = 1; spacemidcount <= spacemid; spacemidcount++)//����м�ո�
			printf(" ");
		printf("%c\n", chaplus);//����ڶ�����ĸ������
	}
}