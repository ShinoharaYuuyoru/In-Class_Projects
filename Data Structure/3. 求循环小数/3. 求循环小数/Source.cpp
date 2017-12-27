#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct node
{
	int data;
	struct node * next;
} NODE;

void output(NODE *);
void change(int, int, NODE *);

int main()
{
	int n, m;
	NODE * head;

	scanf("%d%d", &n, &m);

	head = (NODE *)malloc(sizeof(NODE));
	head->next = NULL;
	head->data = -1;

	change(n, m, head);
	output(head);

	return 0;
}

void change(int n, int m, NODE* Head)
{
	int Ratio;
	int Remainder;
	int BeDivide[100];
	int BDCounter;
	int BDADDer;
	int Counter;
	int Check;
	int Flag;
	int Search;
	NODE* ADD;
	NODE* LAST;
	NODE* LOOPER;

	memset(BeDivide, -1, sizeof(BeDivide));
	BDCounter = 0;
	Flag = 0;
	BDADDer = 0;
	LAST = Head;
	LOOPER = Head;

	for (Counter = 0;Counter <= 50;Counter++)
	{
		Ratio = (n * 10) / m;
		Remainder = (n * 10) % m;

		if (Remainder != 0)
		{
			for (BDCounter = 0;BeDivide[BDCounter] != -1;BDCounter++)
			{
				if ((n*10) == BeDivide[BDCounter])//LOOP
				{
					for (Search = 0;Search <= BDCounter;Search++)
					{
						LOOPER = LOOPER->next;
					}
					LAST->next = LOOPER;

					Flag = 1;
					
					return;
				}
			}

			if (Flag == 0)//ADD
			{
				BeDivide[BDADDer] = n * 10;
				BDADDer++;

				ADD = (NODE*)malloc(sizeof(NODE));
				ADD->data = Ratio;
				ADD->next = LAST->next;
				LAST->next = ADD;
				LAST = ADD;
			}

			Flag = 0;
		}
		else
		{
			ADD = (NODE*)malloc(sizeof(NODE));
			ADD->data = Ratio;
			ADD->next = LAST->next;
			LAST->next = ADD;
			LAST = ADD;

			return;
		}

		n = Remainder;
	}
}

void output(NODE * head)
{
	int k = 0;

	printf("0.");

	while (head->next != NULL && k<50)
	{
		printf("%d", head->next->data);
		head = head->next;

		k++;
	}
	printf("\n");
}