#include "stdio.h"
#include "string.h"
#define N 9

void DFS(int x, int kcount);

char chessboard[N][N] = { { '\0' } };//���̶����ʼ��
int n, k, sum = 0;//���̴�С  ���ø���  �����ܺ�
int yes[N];

int main()
{
	int x, y;
	int defx, defy;//��ʼ����ֵ��
	int kcount = 0;//���Է��õļ�����
	int set;
	
	while (1)
	{
		scanf("%d%d", &n, &k);

		if (n == -1 || k == -1)//�˳��ж�
			break;

		for (defx = 0; defx < n; defx++)
		{
			for (defy = 0; defy < n; defy++)
			{
				chessboard[defx][defy] = '\0';//��ʼ����ֵ�����룩
			}
		}

		for (x = 0; x < n; x++)
		{
			scanf("%s", chessboard[x]);
		}//�������

		sum = 0;//������������
		for (set = 0; set < N; set++)
		{
			yes[set] = 1;//�����б�����
		}

		for (x = 0; x < n;x++)
		{
			for (y = 0; y < n; y++)
			{
				if (chessboard[x][y] == '#')
				{
					yes[y] = 0;//���Ϊ��������
					DFS(x + 1, 1);
				}
				yes[y] = 1;//�ָ�Ϊ������
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