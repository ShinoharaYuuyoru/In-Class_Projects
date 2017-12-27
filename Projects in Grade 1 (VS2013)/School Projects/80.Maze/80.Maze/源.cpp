#include "stdio.h"
#define N 512

//void addwall(int x, int y);
//void DFS(int x, int y);
//
//char maze[N][N] = { { '\0' } };
//char mazecpy[N][N] = { { '\0' } };
//int n, m, k;/*n:行数   m:列数   k:添加的墙数*/
//
//int main()
//{
//	int x = 0, y = 0;
//	int lastx, lasty;/*最终检索*/
//
//	scanf("%d%d%d", &n, &m, &k);
//	for (x = 0; x < n; x++)
//	{
//		scanf("%s", maze[x]);
//	}
//	for (x = 0; x < n; x++)
//	{
//		for (y = 0; y < m; y++)
//		{
//			memcpy((char *)mazecpy, (char *)maze, sizeof(maze[0][0])*N*N);//将maze数组复制给mazecpy   以下将以mazecpy作为操作
//			if (mazecpy[x][y] == '.')
//			{
//				addwall(x, y);
//				DFS(x, y);
//				for (lastx = 0; lastx < n; lastx++)
//				{
//					for (lasty = 0; lasty < m; lasty++)
//					{
//						if (mazecpy[lastx][lasty] == '.')
//							return 0;
//						else
//						{
//							for (lastx = 0; lastx < n; lastx++)
//							{
//								printf("%s\n", mazecpy[lastx]);
//							}
//							exit(0);
//						}
//					}
//				}
//			}
//			else
//			{
//				continue;
//			}
//		}
//	}
//}
//
//
//void addwall(int x, int y)
//{
//	int kcount=k,xsave=x;
//	
//	for (; x < n; x++)
//	{
//		if (x>xsave)
//			y = 0;
//		for (; y < m; y++)
//		{
//			if (mazecpy[x][y] == '.'&&kcount!=0)
//			{
//				mazecpy[x][y] = 'X';
//				kcount--;
//			}
//		}
//	}
//}
//
//
//void DFS(int x, int y)
//{
//	if (mazecpy[x][y] != '.' || x > n || y > m || x < 0 || y < 0)
//		return;
//	else
//	{
//		mazecpy[x][y] = '!';
//		DFS(x-1,y);
//		DFS(x,y-1);
//		DFS(x,y+1);
//		DFS(x+1,y);
//	}
//}
/*上边为原创错误答案*/
void DFS(int x, int y);

int m, n, k, kcount;//m：行数 n：列数 k：添加的墙数
char land[N][N] = { {'\0'} };//土地
int landban[N][N] = { { 0 } };//标记板

int main()
{
	int x, y;//搜索空地用

	scanf("%d%d%d", &m, &n, &k);//输入行列墙数

	kcount = k;
	for (x = 0; x < m; x++)
	{
		scanf("%s", land[x]);
	}//输入完毕

	for (x = 0; x < m; x++)
	{
		for (y = 0; y < n; y++)
		{
			DFS(x, y);
		}
	}

	for (x = 0; x < m; x++)//输出
	{
		printf("%s\n", land[x]);
	}

}

void DFS(int x, int y)
{
	if (x>m || x<0 || y>n || y < 0)
		return;
	if (landban[x][y] == 1 || land[x][y] != '.')
		return;
	landban[x][y] = 1;

	DFS(x - 1, y);
	DFS(x + 1, y);
	DFS(x, y + 1);
	DFS(x, y - 1);

	if (kcount > 0)
	{
		land[x][y] = 'X';
		kcount--;
	}
}