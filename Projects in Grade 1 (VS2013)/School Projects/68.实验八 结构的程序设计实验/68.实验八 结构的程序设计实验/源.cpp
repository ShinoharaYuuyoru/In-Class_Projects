/*һ��ʵ��Ŀ��
ͨ���Խṹ�ĳ���ķ������ṹ��Ա�ķ��ʡ�����Ĳ�����ϰ�����սṹ�г�Ա�ķ��ʷ�����ѧϰ��������ӡ�ɾ�����ڴ��ͷŵķ��������������������ڵ���ŵ㡣

����ʵ������

1����Ŀ���ṹ��Ա�ķ���

ʵ���������ʾ��

����1�����������ṹ��student��date���ֱ��ʾѧ���Ļ�����Ϣ��ѧ���ĳ������ڣ��Ѿ���ѧ����������ͳɼ��ṹ��ʼ����Ҫ����ɳ�����գ�ʵ�ֶ�ѧ��������������Գɼ��Լ�����ƽ���ɼ�������������ʽ�μ�ͼ1.
*/

///*����һ*/
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
//	long  studentID;             /* ѧ�� */
//	char  studentName[10];       /* ���� */
//	char  studentSex;            /* �Ա� */
//	DATE  birthday;              /* �������� */
//	int score[4];                /* 4�ſγ̵ĳɼ� */
//}STUDENT;
//
//int main()
//{
//	int i, j, sum[30];
//	STUDENT stu[30] =
//	{
//		{ 100310121, "����", 'M', { 1991, 5, 19 }, { 72, 83, 90, 82 } },
//		{ 100310122, "��С��", 'M', { 1992, 8, 20 }, { 88, 92, 78, 78 } },
//		{ 100310123, "������", 'F', { 1991, 9, 19 }, { 98, 72, 89, 66 } },
//		{ 100310124, "������", 'F', { 1992, 3, 22 }, { 87, 95, 78, 90 } }
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
//			stu[i].birthday.year,//��
//			stu[i].birthday.month,//��
//			stu[i].birthday.day,//��
//			stu[i].score[0],
//			stu[i].score[1],
//			stu[i].score[2],
//			stu[i].score[3],
//			(float)sum[i] / 4);
//	}
//	return 0;
//}

/*2����Ŀ������Ĳ�����

ʵ���������ʾ��

����1��һ�����������ʵ�飬ʵ���˶�������ڵ����ݵ���ʾ������һ������ڵ㡢ɾ��һ������ڵ㡢�Լ��ͷ��������нڵ���ռ�õ��ڴ�ռ䣬���Ķ�����1����ɳ�����ա�*/
///*�����*/
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
//	struct link *head = NULL;   /* ����ͷָ�� */
//	printf("Do you want to append a new node(Y/N)?");//��ʱΪ�ձ�
//	scanf(" %c", &c);               /* %cǰ����һ���ո� */
//	while (c == 'Y' || c == 'y')
//	{
//		head = AppendNode(head);
//		DisplyNode(head);           /* ��ʾ��ǰ�����еĸ��ڵ���Ϣ */
//		printf("Do you want to append a new node(Y/N)?");
//		scanf(" %c", &c);          /* %cǰ����һ���ո� */
//		i++;
//	}
//	printf("%d new nodes have been apended!\n", i);
//	head = DeleteNode(head, 20);
//	DisplyNode(head);
//	DeleteMemory(head);           /* �ͷ����ж�̬������ڴ� */
//	return 0;
//}
//
//
///* �������ܣ��½�һ���ڵ㲢��ӵ�����ĩβ��������ӽڵ��������ͷָ�� */
//struct link *AppendNode(struct link *head)
//{
//	struct link *p = NULL;
//	struct link *pr = head;
//	int data;
//	p = (link*)malloc(sizeof(link)); /* ��pָ���½��ڵ� */
//	if (p == NULL)//����ռ�ʧ�� �˳�
//	{
//		printf("No enough memory to allocate!\n");
//		exit(0);
//	}
//	if (head == NULL)              /* ��ԭ����Ϊ�ձ����½��ڵ�p��Ϊ�׽ڵ� */
//	{
//		head = p;
//	}
//	else                             /* ��ԭ����Ϊ�ǿգ����½��ڵ���ӵ���β */
//	{
//		while (pr->next!=NULL)/* ��δ����β�����ƶ�prֱ��prָ���β */
//		{
//			pr = pr->next;     /* ��prָ����һ���ڵ� */
//		}
//		pr->next = p;            /* ���½��ڵ���ӵ������ĩβ */
//	}
//	pr = p;                        /* ��prָ���½��ڵ� */
//	printf("Input node data:");
//	scanf("%d", &data);           /* ����ڵ����� */
//	pr->data = data;
//	pr->next = NULL;           /* ���½��ڵ���Ϊ��β */
//	return head;                   /* ������ӽڵ��������ͷ�ڵ�ָ�� */
//}
//
//
///* �����Ĺ��ܣ���ʾ���������нڵ�Ľڵ�ź͸ýڵ������������� */
//void DisplyNode(struct link *head)
//{
//	struct link *p = head;
//	int j = 1;
//	while (p != NULL)                       /* �����Ǳ�β����ѭ����ӡ */
//	{
//		printf("%5d%10d\n", j, p->data);/* ��ӡ��j���ڵ������ */
//		p = p->next;                    /* ��pָ����һ���ڵ� */
//		j++;
//	}
//}
//
//
///*  �������ܣ��ͷ�headָ������������нڵ�ռ�õ��ڴ� */
//void DeleteMemory(struct link *head)
//{
//	struct link *p = head, *pr = NULL;
//	while (p!=NULL)             /* �����Ǳ�β�����ͷŽڵ�ռ�õ��ڴ� */
//	{
//		pr = p;                    /* ��pr�б��浱ǰ�ڵ��ָ�� */
//		p = p->next;              /* ��pָ����һ���ڵ� */
//		pr = NULL;                /* �ͷ�prָ��ĵ�ǰ�ڵ�ռ�õ��ڴ� */
//	}
//}
//
//
///*  �������ܣ���headָ���������ɾ��һ���ڵ㣬����ɾ���ڵ��������ͷָ�� */
//struct link *DeleteNode(struct link *head, int nodeData)
//{
//	struct link *p = head, *pr = head;
//	if (head == NULL)       /* ������Ϊ�ձ����˳����� */
//	{
//		printf("Linked Table is empty!\n");
//		return(NULL);
//	}
//	while (p->data!=nodeData&& p->next != NULL)/* δ�ҵ���δ����β */
//	{
//		pr = p;
//		p = p->next;
//	}
//	if (nodeData == p->data)    /* ���ҵ��ڵ�nodeData����ɾ���ýڵ� */
//	{
//		if (p == head)       /* ����ɾ���ڵ�Ϊ�׽ڵ㣬����headָ���2���ڵ� */
//		{
//			head = p->next;
//		}
//		else /*����ɾ���ڵ㲻���׽ڵ㣬��ǰһ�ڵ��ָ��ָ��ǰ�ڵ����һ�ڵ�*/
//		{
//			pr->next=p->next;
//		}
//		free(p);              /* �ͷ�Ϊ��ɾ���ڵ������ڴ� */
//	}
//	else                         /* û���ҵ���ɾ���ڵ� */
//	{
//		printf("This Node has not been found!\n");
//	}
//	return head;               /* ����ɾ���ڵ��������ͷ�ڵ�ָ�� */
//}