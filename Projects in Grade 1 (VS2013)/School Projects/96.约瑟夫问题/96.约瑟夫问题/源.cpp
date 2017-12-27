#include "stdio.h"
#include "stdlib.h"

typedef struct NODE
{
	int Number;//该人的编号
	int SayNumber;//该人的报数
	struct NODE *link;//连接
};
NODE *head;//头指针 指向编号为1的人
NODE *q;//指向p之前的节点
NODE *p;//指向元素的指针

int N;//总人数 <50人
int Ncount;//人数计数器 用于建立环形链表
int S;//从第S个开始报数
int M;//第M个死一个
int killnumber;//要死的编号

void output(NODE *h);
void pop(NODE *start);

int main()
{
	printf("请输入总人数N（N < 50）：\n");//***********其实理论上可以很大......不仅仅限制于50人......
	scanf("%d", &N);//输入总人数
	printf("\n");

	p = (NODE*)malloc(sizeof(NODE));//第一个人  head永远指向第一个人
	p->Number = 0;
	p->link = NULL;
	head = p;
	q = p;

	for (Ncount = 1; Ncount <= N; Ncount++)//生成单向链表
	{
		p = (NODE*)malloc(sizeof(NODE));
		p->Number = Ncount;//编号
		p->SayNumber = 0;//喊号重置
		q->link = p;
		q = q->link;
		p->link = NULL;
	}
	p->link = head->link;//形成环形链表  此时p为最末尾

	/*环形链表完成*/

	output(head->link);//输出编号

	printf("请输入报数开始人编号S（S <= N）：\n");
	scanf("%d", &S);
	printf("\n");
	if (S > N)
	{
		printf("您的输入有误！\n\n");
		return 0;
	}
	printf("请输入间隔人数M（M >= 2）：\n");
	scanf("%d", &M);
	printf("\n");
	if (M == 1)
	{
		printf("全部阵亡！您输入有误！\n\n");
		return 0;
	}

	p = head->link;//定位p为开头
	q = head;//q在p后边
	for (; p->Number != S;)//p定位到第S个人 q定位到S之前的人
	{
		p = p->link;
		q = q->link;
	}

	pop(p);

	printf("生存者编号：%d\n\n", p->Number);

	return 0;
}

void output(NODE *h)//打印编号
{
	NODE *print;
	int Nprint;

	print = h;
	for (Nprint = 1; Nprint <= N; Nprint++)
	{
		printf("编号：%d 	", print->Number);
		printf("报数：%d\n", print->SayNumber);
		print = print->link;
	}
	printf("\n");
}

void pop(NODE *start)//自杀处理
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
			printf("编号%d自杀！\n", p->Number);
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