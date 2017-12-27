#include <stdio.h>  
#include <stdlib.h>  

struct node
{
	int data;
	struct node * next;
};

typedef struct node NODE;
typedef struct node * PNODE;

PNODE constructlist(PNODE head, int num);
void outlist(PNODE head);
void deleteneg(PNODE head);

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
			constructlist(head, num);
	}
	deleteneg(head);
	outlist(head);
	return 0;
}

PNODE constructlist(PNODE head, int num)//插入到head和head之后的节点中间
{
	PNODE p;
	p = (PNODE)malloc(sizeof(NODE));
	p->data = num;
	p->next = head->next;
	head->next = p;
	return head;
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


void deleteneg( PNODE head )
{
	PNODE p,pback;
	p = head->next;
	pback = head;
	while (p != NULL)
	{
		if (p->data < 0)
		{
			pback->next = p->next;
			free(p);
			p = pback->next;
		}
		else
		{
			p = p->next;
			pback = pback->next;
		}
	}
}