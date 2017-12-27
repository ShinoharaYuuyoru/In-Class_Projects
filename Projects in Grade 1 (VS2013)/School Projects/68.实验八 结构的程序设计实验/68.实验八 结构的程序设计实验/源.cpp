/*一、实验目的
通过对结构的程序的分析、结构成员的访问、链表的操作练习，掌握结构中成员的访问方法，学习链表的增加、删除和内存释放的方法，理解利用链表遍历节点的优点。

二、实验内容

1、题目：结构成员的访问

实验分析及提示：

程序1包含了两个结构：student和date，分别表示学生的基本信息和学生的出生日期，已经对学生基本情况和成绩结构初始化，要求完成程序填空，实现对学生基本情况、考试成绩以及个人平均成绩的输出，输出样式参见图1.
*/

///*程序一*/
//
//#include  <stdio.h>
//
//typedef struct date
//{
//	int   year;
//	int   month;
//	int   day;
//}DATE;
//
//typedef struct student
//{
//	long  studentID;             /* 学号 */
//	char  studentName[10];       /* 姓名 */
//	char  studentSex;            /* 性别 */
//	DATE  birthday;              /* 出生日期 */
//	int score[4];                /* 4门课程的成绩 */
//}STUDENT;
//
//int main()
//{
//	int i, j, sum[30];
//	STUDENT stu[30] =
//	{
//		{ 100310121, "王刚", 'M', { 1991, 5, 19 }, { 72, 83, 90, 82 } },
//		{ 100310122, "李小明", 'M', { 1992, 8, 20 }, { 88, 92, 78, 78 } },
//		{ 100310123, "王丽红", 'F', { 1991, 9, 19 }, { 98, 72, 89, 66 } },
//		{ 100310124, "陈莉莉", 'F', { 1992, 3, 22 }, { 87, 95, 78, 90 } }
//	};
//	for (i = 0; i < 4; i++)
//	{
//		sum[i] = 0;
//		for (j = 0; j < 4; j++)
//		{
//			sum[i] = sum[i] + stu[i].score[j];
//		}
//		printf(" %ld  %6s  %c  %d/%02d/%d  %d  %d  %d  %d  %.1f\n",
//			stu[i].studentID,
//			stu[i].studentName,
//			stu[i].studentSex,
//			stu[i].birthday.year,//年
//			stu[i].birthday.month,//月
//			stu[i].birthday.day,//日
//			stu[i].score[0],
//			stu[i].score[1],
//			stu[i].score[2],
//			stu[i].score[3],
//			(float)sum[i] / 4);
//	}
//	return 0;
//}

/*2、题目：链表的操作。

实验分析及提示：

程序1是一个关于链表的实验，实验了对链表各节点内容的显示，增加一个链表节点、删除一个链表节点、以及释放链表所有节点所占用的内存空间，请阅读程序1并完成程序填空。*/
///*程序二*/
//
//#include <stdio.h>
//#include <stdlib.h>
//
//struct link *AppendNode(struct link *head);
//void DisplyNode(struct link *head);
//void DeleteMemory(struct link *head);
//struct link *DeleteNode(struct link *head, int nodeData);
//
//struct link
//{
//	int data;
//	struct link *next;
//};
//
//int main()
//{
//	int i = 0;
//	char c;
//	struct link *head = NULL;   /* 链表头指针 */
//	printf("Do you want to append a new node(Y/N)?");//此时为空表
//	scanf(" %c", &c);               /* %c前面有一个空格 */
//	while (c == 'Y' || c == 'y')
//	{
//		head = AppendNode(head);
//		DisplyNode(head);           /* 显示当前链表中的各节点信息 */
//		printf("Do you want to append a new node(Y/N)?");
//		scanf(" %c", &c);          /* %c前面有一个空格 */
//		i++;
//	}
//	printf("%d new nodes have been apended!\n", i);
//	head = DeleteNode(head, 20);
//	DisplyNode(head);
//	DeleteMemory(head);           /* 释放所有动态分配的内存 */
//	return 0;
//}
//
//
///* 函数功能：新建一个节点并添加到链表末尾，返回添加节点后的链表的头指针 */
//struct link *AppendNode(struct link *head)
//{
//	struct link *p = NULL;
//	struct link *pr = head;
//	int data;
//	p = (link*)malloc(sizeof(link)); /* 让p指向新建节点 */
//	if (p == NULL)//申请空间失败 退出
//	{
//		printf("No enough memory to allocate!\n");
//		exit(0);
//	}
//	if (head == NULL)              /* 若原链表为空表，则将新建节点p置为首节点 */
//	{
//		head = p;
//	}
//	else                             /* 若原链表为非空，则将新建节点添加到表尾 */
//	{
//		while (pr->next!=NULL)/* 若未到表尾，则移动pr直到pr指向表尾 */
//		{
//			pr = pr->next;     /* 让pr指向下一个节点 */
//		}
//		pr->next = p;            /* 将新建节点添加到链表的末尾 */
//	}
//	pr = p;                        /* 让pr指向新建节点 */
//	printf("Input node data:");
//	scanf("%d", &data);           /* 输入节点数据 */
//	pr->data = data;
//	pr->next = NULL;           /* 将新建节点置为表尾 */
//	return head;                   /* 返回添加节点后的链表的头节点指针 */
//}
//
//
///* 函数的功能：显示链表中所有节点的节点号和该节点中数据项内容 */
//void DisplyNode(struct link *head)
//{
//	struct link *p = head;
//	int j = 1;
//	while (p != NULL)                       /* 若不是表尾，则循环打印 */
//	{
//		printf("%5d%10d\n", j, p->data);/* 打印第j个节点的数据 */
//		p = p->next;                    /* 让p指向下一个节点 */
//		j++;
//	}
//}
//
//
///*  函数功能：释放head指向的链表中所有节点占用的内存 */
//void DeleteMemory(struct link *head)
//{
//	struct link *p = head, *pr = NULL;
//	while (p!=NULL)             /* 若不是表尾，则释放节点占用的内存 */
//	{
//		pr = p;                    /* 在pr中保存当前节点的指针 */
//		p = p->next;              /* 让p指向下一个节点 */
//		pr = NULL;                /* 释放pr指向的当前节点占用的内存 */
//	}
//}
//
//
///*  函数功能：从head指向的链表中删除一个节点，返回删除节点后的链表的头指针 */
//struct link *DeleteNode(struct link *head, int nodeData)
//{
//	struct link *p = head, *pr = head;
//	if (head == NULL)       /* 若链表为空表，则退出程序 */
//	{
//		printf("Linked Table is empty!\n");
//		return(NULL);
//	}
//	while (p->data!=nodeData&& p->next != NULL)/* 未找到且未到表尾 */
//	{
//		pr = p;
//		p = p->next;
//	}
//	if (nodeData == p->data)    /* 若找到节点nodeData，则删除该节点 */
//	{
//		if (p == head)       /* 若待删除节点为首节点，则让head指向第2个节点 */
//		{
//			head = p->next;
//		}
//		else /*若待删除节点不是首节点，则将前一节点的指针指向当前节点的下一节点*/
//		{
//			pr->next=p->next;
//		}
//		free(p);              /* 释放为已删除节点分配的内存 */
//	}
//	else                         /* 没有找到待删除节点 */
//	{
//		printf("This Node has not been found!\n");
//	}
//	return head;               /* 返回删除节点后的链表的头节点指针 */
//}