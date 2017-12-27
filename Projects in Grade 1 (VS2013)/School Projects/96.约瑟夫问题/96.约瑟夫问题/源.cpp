#include "stdio.h"
#include "stdlib.h"

typedef struct NODE
{
	int Number;//���˵ı��
	int SayNumber;//���˵ı���
	struct NODE *link;//����
};
NODE *head;//ͷָ�� ָ����Ϊ1����
NODE *q;//ָ��p֮ǰ�Ľڵ�
NODE *p;//ָ��Ԫ�ص�ָ��

int N;//������ <50��
int Ncount;//���������� ���ڽ�����������
int S;//�ӵ�S����ʼ����
int M;//��M����һ��
int killnumber;//Ҫ���ı��

void output(NODE *h);
void pop(NODE *start);

int main()
{
	printf("������������N��N < 50����\n");//***********��ʵ�����Ͽ��Ժܴ�......������������50��......
	scanf("%d", &N);//����������
	printf("\n");

	p = (NODE*)malloc(sizeof(NODE));//��һ����  head��Զָ���һ����
	p->Number = 0;
	p->link = NULL;
	head = p;
	q = p;

	for (Ncount = 1; Ncount <= N; Ncount++)//���ɵ�������
	{
		p = (NODE*)malloc(sizeof(NODE));
		p->Number = Ncount;//���
		p->SayNumber = 0;//��������
		q->link = p;
		q = q->link;
		p->link = NULL;
	}
	p->link = head->link;//�γɻ�������  ��ʱpΪ��ĩβ

	/*�����������*/

	output(head->link);//������

	printf("�����뱨����ʼ�˱��S��S <= N����\n");
	scanf("%d", &S);
	printf("\n");
	if (S > N)
	{
		printf("������������\n\n");
		return 0;
	}
	printf("������������M��M >= 2����\n");
	scanf("%d", &M);
	printf("\n");
	if (M == 1)
	{
		printf("ȫ������������������\n\n");
		return 0;
	}

	p = head->link;//��λpΪ��ͷ
	q = head;//q��p���
	for (; p->Number != S;)//p��λ����S���� q��λ��S֮ǰ����
	{
		p = p->link;
		q = q->link;
	}

	pop(p);

	printf("�����߱�ţ�%d\n\n", p->Number);

	return 0;
}

void output(NODE *h)//��ӡ���
{
	NODE *print;
	int Nprint;

	print = h;
	for (Nprint = 1; Nprint <= N; Nprint++)
	{
		printf("��ţ�%d 	", print->Number);
		printf("������%d\n", print->SayNumber);
		print = print->link;
	}
	printf("\n");
}

void pop(NODE *start)//��ɱ����
{
	int count = 1;

	while (p != q)
	{
		if (count > M)
		{
			count = 1;
		}

		p->SayNumber = count;
		count++;

		if (p->SayNumber == M)
		{
			printf("���%d��ɱ��\n", p->Number);
			q->link = p->link;
			free(p);
			p = q->link;
		}
		else
		{
			p = p->link;
			q = q->link;
		}
	}
	printf("\n");
}