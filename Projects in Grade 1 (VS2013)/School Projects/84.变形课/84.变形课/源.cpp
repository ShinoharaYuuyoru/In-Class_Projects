#include "stdio.h"
#define N 10000

int DFS(int head);

bool visit[N];//���ʷ���
char word[N][N], wordhe[N][2];//�����б�&��ȡͷβ
char cha[30000];//ȷ��ÿһ����Ҫ���ݵ���ĸ
int wordend;//�����б��ĩβ
int stack[N];//ջ

int main()
{
	int wordin;//�������������
	int head, end;//һ�����ʵĵ�һ����ĸ�����һ����ĸ  ����headֱ�����ڵ��ʸ����ļ�����

	while (scanf("%s", word[0]) != EOF)
	{
		for (wordin = 1;; wordin++)
		{
			gets(word[wordin]);//���뵥���б�
			if (word[wordin][0] == '0')
			{
				break;
			}
		}

		for (wordin = 0; word[wordin][0] != '0'; wordin++)//��ÿ�����ʵ�ͷ��β��ȡ��wordhe
		{
			wordhe[wordin][0] = word[wordin][0];//��ÿ�����ʵ�ͷ��ȡ

			for (end = 0; word[wordin][end] != '\0'; end++);//��end��λ����һ��'\0'
			end--;//��λ�����ʵ�β

			wordhe[wordin][1] = word[wordin][end];//��ȡ����β��

			visit[wordin] = 1;//��ʼ������  ���Ϊ�ɷ���
		}
		wordend = wordin - 1;//ȷ�������б�ĩβ(��ʵ�ʵ�������1 ��Ϊ��0����)

		/*���¾���wordhe���в���*/
		for (head = 0; head <= wordend; head++)
		{
			for (int visx = 0; visx < wordend; visx++)//���÷���
			{
				visit[visx] = 1;
			}

			if (wordhe[head][0] == 'b')//�������b��ͷ�ĵ���
			{
				cha[0] = 'b';
				cha[1] = wordhe[head][1];
				if (DFS(head) == 1)
				{
					printf("Yes.\n");
					goto k;//�ɹ� ��������  ����
				}
			}
		}
		printf("No.\n");
	k:;
	}
}

int DFS(int head)
{
	int top = 0;//��λ�����ϲ�
	int now = head;//ĳһ��ĵ��ʱ��
	int search;//Ѱ�ұ�

	stack[0] = head;

	while (top != -1)
	{
		now = stack[top];
		if (visit[now])//����˵��ʿɷ���
		{
			visit[now] = 0;//���˴ʱ��Ϊ���ɷ���
			for (search = 0; search <= wordend; search++)//Ѱ��ÿһ����
			{
				if (cha[top + 1] == wordhe[search][0]&&visit[search])
				{
					cha[top + 2] = wordhe[search][1];
					stack[top + 1] = search;
					if (cha[top + 2] == 'm')
					{
						return 1;
					}
					top++;
				}
				else
				{
					if (cha[0] == 'b'&&cha[1] == 'm')//����һ��������b��ͷ��m��βʱ
					{
						return 1;
					}
				}
			}
		}
		else
		{
			top--;
			if (top != -1)
			{
				visit[stack[top]] = 1;
			}
		}
	}
	return 0;
}