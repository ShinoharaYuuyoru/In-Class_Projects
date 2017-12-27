#include <stdio.h>  
#include <stdlib.h>  

typedef struct sdata
{
	int num;
	struct sdata *next;
} SNODE;

void movenode(SNODE *head, int n);

void setlink(SNODE *head, int n)
{
	SNODE *p;

	while (n > 0)
	{
		p = (SNODE *)malloc(sizeof(SNODE));
		p->num = n;
		p->next = head->next;
		head->next = p;
		n--;
	}
}

void outlink(SNODE * head)
{
	while (head->next != NULL)
	{
		head = head->next;
		printf("%d,", head->num);
	}
	return;
}

int main()
{
	int n, m;
	SNODE * head = NULL;

	scanf("%d%d", &n, &m);
	head = (SNODE *)malloc(sizeof(SNODE));
	head->num = -1;
	head->next = NULL;
	setlink(head, n);

	movenode(head, m);   /* This is waiting for you. */

	outlink(head);
	printf("\n");
	return 0;
}

void movenode(SNODE *head, int n)
{
	SNODE *p=head->next,*save,*front;
	front = head;
	while (front->next != NULL)
	{
		if (n == p->num)
		{
			front->next = p->next;
			save = head->next;
			head->next = p;
			p->next = save;
			break;
		}
		else
		{
			p = p->next;
			front = front->next;
		}
	}
}