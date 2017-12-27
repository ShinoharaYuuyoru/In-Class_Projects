#include "stdio.h"
#define N 512

//void addwall(int x, int y);
//void DFS(int x, int y);
//
//char maze[N][N] = { { '\0' } };
//char mazecpy[N][N] = { { '\0' } };
//int n, m, k;/*n:����   m:����   k:��ӵ�ǽ��*/
//
//int main()
//{
//	int x = 0, y = 0;
//	int lastx, lasty;/*���ռ���*/
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
//			memcpy((char *)mazecpy, (char *)maze, sizeof(maze[0][0])*N*N);//��maze���鸴�Ƹ�mazecpy   ���½���mazecpy��Ϊ����
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
/*�ϱ�Ϊԭ�������*/
void DFS(int x, int y);

int m, n, k, kcount;//m������ n������ k����ӵ�ǽ��
char land[N][N] = { {'\0'} };//����
int landban[N][N] = { { 0 } };//��ǰ�

int main()
{
	int x, y;//�����յ���

	scanf("%d%d%d", &m, &n, &k);//��������ǽ��

	kcount = k;
	for (x = 0; x < m; x++)
	{
		scanf("%s", land[x]);
	}//�������

	for (x = 0; x < m; x++)
	{
		for (y = 0; y < n; y++)
		{
			DFS(x, y);
		}
	}

	for (x = 0; x < m; x++)//���
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