#include "stdio.h"
#define N 101

void DFS(int x, int y);

int l, j/*限定行列*/;
char land[N][N] = { 0 }/*土地,其中*表示无油，@表示有油*/;

int main()
{
	int x, y = 1/*行列计数器*/;
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
						DFS(x, y);//判断此处有没有石油
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