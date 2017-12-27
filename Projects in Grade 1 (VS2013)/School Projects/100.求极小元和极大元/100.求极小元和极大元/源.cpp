#include "stdio.h"
#include "stdlib.h"

void deal(char cha, int sg);

typedef struct element
{
	int up;//上边有无元素标记
	char ele;//元素符号 a b c d e ......
	int down;//下边有无元素标记
	struct element *next;
}Element;

Element *head = NULL;//始终定位在第一个元素位置
Element *point = NULL;//指针
Element *pointfr = NULL;//用于构建链表和最终的free

int main()
{
	char temp;//临时记录
	char line[500];//关系
	int search;//关系搜索
	int sign = 0;//如果是关系的第一个元素 则为1  若为第二个元素 则为2
	char print[20];//输出
	int printp = 0;//输出搜索

	/*重置\0*/
	for (printp = 0; printp <= 19; printp++)
	{
		print[printp] = '\0';
	}

	for (search = 0; search <= 499; search++)
	{
		line[search] = '\0';
	}

	for (;;)//输入
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

	gets(line);//输入关系

	for (search = 0; line[search] != '\0'; search++)//搜索关系
	{
		if (line[search] == '<')//如果是左括号
		{
			if (line[search + 1] != line[search + 3])//检测是否是<a,a>
			{
				sign = 1;
				deal(line[search + 1], sign);
			}
			else//跳过两个相等的情况
			{
				continue;
			}
		}
		if (line[search] == '>')//右括号
		{
			if (line[search - 1] != line[search - 3])//再次检测
			{
				sign = 2;
				deal(line[search - 1], sign);
			}
		}
	}

	point = head;//开始检查
	printp = 0;

	for (;;)//极小元检查
	{
		if (point != NULL)
		{
			if (point->down == 0)//如果此元素下边没有（极小元）
			{
				print[printp] = point->ele;//纳入打印数组
				printp++;
			}
		}
		else
		{
			break;
		}
		point = point->next;
	}
	for (printp = 0; print[printp] != '\0'; printp++)//输出极小元
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

	point = head;//开始检查
	printp = 0;

	for (;;)//极大元检查
	{
		if (point != NULL)
		{
			if (point->up == 0)//如果此元素上边没有（极大元）
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

	print[printp] = '\0';//设置终结点 防止越界

	for (printp = 0; print[printp] != '\0'; printp++)//输出极大元
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
		if (point->ele != cha)//如果没搜索到进入函数的字母 则指向下一个
		{
			point = point->next;
		}
		else
		{
			if (sg == 1)//上有元素
			{
				point->up = 1;
			}
			else//下有元素 sg==2
			{
				point->down = 1;
			}

			break;
		}
	}
}