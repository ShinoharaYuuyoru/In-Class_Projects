#include "stdio.h"
#define N 10000

int DFS(int head);

bool visit[N];//单词访问
char word[N][N], wordhe[N][2];//单词列表&提取头尾
char cha[30000];//确定每一层需要传递的字母
int wordend;//单词列表的末尾
int stack[N];//栈

int main()
{
	int wordin;//单词输入计数器
	int head, end;//一个单词的第一个字母和最后一个字母  其中head直接用于单词个数的计数器

	while (scanf("%s", word[0]) != EOF)
	{
		for (wordin = 1;; wordin++)
		{
			gets(word[wordin]);//输入单词列表
			if (word[wordin][0] == '0')
			{
				break;
			}
		}

		for (wordin = 0; word[wordin][0] != '0'; wordin++)//将每个单词的头和尾提取到wordhe
		{
			wordhe[wordin][0] = word[wordin][0];//将每个单词的头提取

			for (end = 0; word[wordin][end] != '\0'; end++);//将end定位到第一个'\0'
			end--;//定位到单词的尾

			wordhe[wordin][1] = word[wordin][end];//提取单词尾部

			visit[wordin] = 1;//初始化访问  标记为可访问
		}
		wordend = wordin - 1;//确定单词列表末尾(比实际单词数少1 因为从0计数)

		/*以下均用wordhe进行操作*/
		for (head = 0; head <= wordend; head++)
		{
			for (int visx = 0; visx < wordend; visx++)//重置访问
			{
				visit[visx] = 1;
			}

			if (wordhe[head][0] == 'b')//如果是以b开头的单词
			{
				cha[0] = 'b';
				cha[1] = wordhe[head][1];
				if (DFS(head) == 1)
				{
					printf("Yes.\n");
					goto k;//成功 结束此组  跳出
				}
			}
		}
		printf("No.\n");
	k:;
	}
}

int DFS(int head)
{
	int top = 0;//定位到最上层
	int now = head;//某一层的单词标记
	int search;//寻找边

	stack[0] = head;

	while (top != -1)
	{
		now = stack[top];
		if (visit[now])//如果此单词可访问
		{
			visit[now] = 0;//将此词标记为不可访问
			for (search = 0; search <= wordend; search++)//寻找每一条边
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
					if (cha[0] == 'b'&&cha[1] == 'm')//当第一个单词以b开头以m结尾时
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