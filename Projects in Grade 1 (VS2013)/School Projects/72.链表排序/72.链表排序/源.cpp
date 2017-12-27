#include "stdio.h"  
#include "stdlib.h"  

struct node
{
	int data;
	struct node * next;
};

typedef struct node NODE;
typedef struct node * PNODE;
void outlist(PNODE);
void sortlist(PNODE h, int num);

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
			sortlist(head, num);
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

void sortlist(PNODE h, int num)
{
	PNODE p,back,front;
	p = (PNODE)malloc(sizeof(NODE));
	p->data = num;
	p->next = NULL;
	back = h;
	if (h->next == NULL)//第一个
		h->next = p;
	else//第二个开始
	{
		front = h;
		back = front->next;
		while (front->next!=NULL)
		{
			if (back->data > num)//小数插前边
			{
				front->next = p;
				p->next = back;
				break;
			}
			else
			{
				if (back->data<num)//遇到大数 往后移动
				{
					back = back->next;
					front = front->next;
				}
				else
				{
					free(p);
					break;
				}
			}
		}
		if (front->next==NULL)
			front->next = p;
	}
}