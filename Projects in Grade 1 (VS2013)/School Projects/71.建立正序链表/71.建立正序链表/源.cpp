/*请按照输入整数的顺序建立一个带表头节点的链表。已知程序的基本结构如下，请你编写 ins_list 函数。*/

#include "stdio.h"  
#include "stdlib.h"  

struct node
{
	int data;
	struct node * next;
};

typedef struct node NODE;
typedef struct node *PNODE;

void outlist(PNODE);
void ins_list(PNODE h, int num);
int main()
{
	int num = 1;
	PNODE head;

	head = (PNODE)malloc(sizeof(NODE));
	head->next = NULL;
	head->data = -1;

	while (num != 0)
	{
		scanf("%d", &num);
		if (num != 0)
			ins_list(head, num);
	}

	outlist(head);
	return 0;
}


void outlist(PNODE head)
{
	PNODE p;
	p = head->next;
	while (p != NULL)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}


void ins_list(PNODE h, int num)
{
	PNODE list;
	PNODE pr = h;
	while (pr->next != NULL)//先指向链表有NULL(最后)的节点
		pr = pr->next;
	list = (PNODE)malloc(sizeof(NODE));
	list->data = num;
	list->next = NULL;
	pr->next = list;
}