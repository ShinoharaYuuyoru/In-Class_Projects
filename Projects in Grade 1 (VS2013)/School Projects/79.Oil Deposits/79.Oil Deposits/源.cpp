#include "stdio.h"
#define N 101

void DFS(int x, int y);

int l, j/*�޶�����*/;
char land[N][N] = { 0 }/*����,����*��ʾ���ͣ�@��ʾ����*/;

int main()
{
	int x, y = 1/*���м�����*/;
	int sum = 0;

	while (1)
	{
		scanf("%d%d", &l, &j);
		if (l == 0 || j == 0)
			break;
		else
		{
			sum = 0;
			for (x = 1; x <= l; x++)
			{
				scanf("%s", land[x]);
			}
			for (x = 1; x <= l; x++)
			{
				for (y = 0; y < j; y++)
				{
					if (land[x][y] == '@')
					{
						DFS(x, y);//�жϴ˴���û��ʯ��
						sum++;
					}
				}
			}
		}
		printf("%d\n", sum);
	}
}

void DFS(int x, int y)
{
	if (land[x][y] != '@' || x<1 || y<0 || x>l || y>=j)
	{
		return;
	}
	else
	{
		land[x][y] = '#';
		DFS(x-1,y-1);
		DFS(x-1,y);
		DFS(x-1,y+1);
		DFS(x,y-1);
		DFS(x,y+1);
		DFS(x+1,y-1);
		DFS(x+1,y);
		DFS(x+1,y+1);
	}
}