#include "stdio.h"
#include "stdlib.h"

void deal(char cha, int sg);

typedef struct element
{
	int up;//�ϱ�����Ԫ�ر��
	char ele;//Ԫ�ط��� a b c d e ......
	int down;//�±�����Ԫ�ر��
	struct element *next;
}Element;

Element *head = NULL;//ʼ�ն�λ�ڵ�һ��Ԫ��λ��
Element *point = NULL;//ָ��
Element *pointfr = NULL;//���ڹ�����������յ�free

int main()
{
	char temp;//��ʱ��¼
	char line[500];//��ϵ
	int search;//��ϵ����
	int sign = 0;//����ǹ�ϵ�ĵ�һ��Ԫ�� ��Ϊ1  ��Ϊ�ڶ���Ԫ�� ��Ϊ2
	char print[20];//���
	int printp = 0;//�������

	/*����\0*/
	for (printp = 0; printp <= 19; printp++)
	{
		print[printp] = '\0';
	}

	for (search = 0; search <= 499; search++)
	{
		line[search] = '\0';
	}

	for (;;)//����
	{
		scanf("%c", &temp);

		if (temp == ',')
		{
			continue;
		}
		if (temp == '\n')
		{
			break;
		}
		if (temp >= 'a'&&temp <= 'z')
		{
			if (head == NULL)
			{
				head = (Element*)malloc(sizeof(Element));
				point = head;
				pointfr = head;

				head->up = 0;
				head->ele = temp;
				head->down = 0;
				head->next = NULL;
			}
			else
			{
				point = (Element*)malloc(sizeof(Element));
				
				point->up = 0;
				point->ele = temp;
				point->down = 0;
				point->next = NULL;

				pointfr->next = point;
				pointfr = point;
			}
		}
	}

	gets(line);//�����ϵ

	for (search = 0; line[search] != '\0'; search++)//������ϵ
	{
		if (line[search] == '<')//�����������
		{
			if (line[search + 1] != line[search + 3])//����Ƿ���<a,a>
			{
				sign = 1;
				deal(line[search + 1], sign);
			}
			else//����������ȵ����
			{
				continue;
			}
		}
		if (line[search] == '>')//������
		{
			if (line[search - 1] != line[search - 3])//�ٴμ��
			{
				sign = 2;
				deal(line[search - 1], sign);
			}
		}
	}

	point = head;//��ʼ���
	printp = 0;

	for (;;)//��СԪ���
	{
		if (point != NULL)
		{
			if (point->down == 0)//�����Ԫ���±�û�У���СԪ��
			{
				print[printp] = point->ele;//�����ӡ����
				printp++;
			}
		}
		else
		{
			break;
		}
		point = point->next;
	}
	for (printp = 0; print[printp] != '\0'; printp++)//�����СԪ
	{
		if (print[printp + 1] != '\0')
		{
			printf("%c,",print[printp]);
		}
		else
		{
			printf("%c\n", print[printp]);
		}
	}

	point = head;//��ʼ���
	printp = 0;

	for (;;)//����Ԫ���
	{
		if (point != NULL)
		{
			if (point->up == 0)//�����Ԫ���ϱ�û�У�����Ԫ��
			{
				print[printp] = point->ele;
				printp++;
			}
		}
		else
		{
			break;
		}
		point = point->next;
	}

	print[printp] = '\0';//�����ս�� ��ֹԽ��

	for (printp = 0; print[printp] != '\0'; printp++)//�������Ԫ
	{
		if (print[printp + 1] != '\0')
		{
			printf("%c,", print[printp]);
		}
		else
		{
			printf("%c\n", print[printp]);
		}
	}

	point = head->next;
	pointfr = head;

	for (; pointfr != NULL;)//free
	{
		free(pointfr);
		pointfr = point;
		if (point == NULL)
		{
			break;
		}
		else
		{
			point = point->next;
		}
	}
}

void deal(char cha, int sg)
{
	point = head;

	for (;;)
	{
		if (point->ele != cha)//���û���������뺯������ĸ ��ָ����һ��
		{
			point = point->next;
		}
		else
		{
			if (sg == 1)//����Ԫ��
			{
				point->up = 1;
			}
			else//����Ԫ�� sg==2
			{
				point->down = 1;
			}

			break;
		}
	}
}