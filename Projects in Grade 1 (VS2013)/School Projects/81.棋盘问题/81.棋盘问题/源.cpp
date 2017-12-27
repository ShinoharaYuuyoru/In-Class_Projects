#include "stdio.h"
#include "string.h"
#define N 9

void DFS(int x, int kcount);

char chessboard[N][N] = { { '\0' } };//棋盘定义初始化
int n, k, sum = 0;//棋盘大小  放置个数  方案总和
int yes[N];

int main()
{
	int x, y;
	int defx, defy;//初始化赋值用
	int kcount = 0;//可以放置的计数器
	int set;
	
	while (1)
	{
		scanf("%d%d", &n, &k);

		if (n == -1 || k == -1)//退出判定
			break;

		for (defx = 0; defx < n; defx++)
		{
			for (defy = 0; defy < n; defy++)
			{
				chessboard[defx][defy] = '\0';//初始化赋值（必须）
			}
		}

		for (x = 0; x < n; x++)
		{
			scanf("%s", chessboard[x]);
		}//输入完毕

		sum = 0;//方案总数重置
		for (set = 0; set < N; set++)
		{
			yes[set] = 1;//禁用列表重置
		}

		for (x = 0; x < n;x++)
		{
			for (y = 0; y < n; y++)
			{
				if (chessboard[x][y] == '#')
				{
					yes[y] = 0;//标记为不可用列
					DFS(x + 1, 1);
				}
				yes[y] = 1;//恢复为可用列
			}
		}
		printf("%d\n", sum);
	}
}

void DFS(int x, int kcount)
{
	int y;
	int signx;

	if (kcount == k)
	{
		sum++;
		return;
	}
	if (x >= n)
	{
		return;
	}
	for (y = 0; y < n; y++)
	{
		if (chessboard[x][y] == '#'&&yes[y])
		{
			yes[y] = 0;
			DFS(x + 1, kcount + 1);
			yes[y] = 1;
		}
	}
	DFS(x + 1, kcount);
}