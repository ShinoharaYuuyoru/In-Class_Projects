#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char LDR[1000];//����
char LRD[1000];//����

int BaseRoot;
int RootDevide;
int RootSearch;

typedef struct Node
{
	char Value;

	struct Node *Left;
	struct Node *Right;
}Leaf;

Leaf *Head;
Leaf *NODE;

void BuildTree(Leaf *PRoot, int ParentPosition);
void Print();

int main()
{
	scanf("%s", LDR);
	scanf("%s", LRD);

	Head = NULL;

	/*Confirm Left and Right Tree*/
	for (BaseRoot = 0;LRD[BaseRoot] != '\0';BaseRoot++);
	BaseRoot--;//�Ӻ������ȷ���ܸ�ֵ
	RootSearch = BaseRoot;
	//for (RootDevide = 0;LDR[RootDevide] != LRD[BaseRoot];RootDevide++);//��������е�һ��ȷ���ܸ�λ��

	BuildTree(Head, 0);//BaseRoot->���������ֵ 0->���������� BaseRoot=���������� 0->��Ӱ��

	Print();
	printf("\n");

	return 0;
}

void BuildTree(Leaf *PRoot,int ParentPosition)
{
	int Devide;
	int Flag = 0;

	for (Devide = 0;LDR[Devide] != LRD[RootSearch];Devide++);//�������ȷ����λ��
	RootSearch--;

	if (Head == NULL)
	{
		Head = (Leaf*)malloc(sizeof(Leaf));
		Head->Left = NULL;
		Head->Right = NULL;
		Head->Value = LDR[Devide];
		PRoot = Head;
	}
	else
	{
		NODE = (Leaf*)malloc(sizeof(Leaf));
		NODE->Left = NULL;
		NODE->Right = NULL;
		NODE->Value = LDR[Devide];
		if (Devide > ParentPosition)
		{
			PRoot->Right = NODE;
			PRoot = NODE;
		}
		if (Devide < ParentPosition)
		{
			PRoot->Left = NODE;
			PRoot = NODE;
		}
	}
	LDR[Devide] = '*';

	if (Devide + 1 <= BaseRoot&&LDR[Devide + 1] != '*')//��������
	{
		BuildTree(PRoot, Devide);
	}
	if (Devide - 1 >= 0 && LDR[Devide - 1] != '*')//��������
	{
		BuildTree(PRoot, Devide);
	}
	return;
}

void Print()
{
	Leaf* Queue[1000];
	int Front = 0;
	int Rear = 0;

	Leaf *P = Head;
	
	Queue[Rear] = P;
	Rear++;

	while (1)
	{
		if (Front >= Rear)
		{
			break;
		}
		P = Queue[Front];

		if (P->Left != NULL)
		{
			Queue[Rear] = P->Left;
			Rear++;
		}
		if (P->Right != NULL)
		{
			Queue[Rear] = P->Right;
			Rear++;
		}

		printf("%c", P->Value);
		Front++;
	}

	return;
}