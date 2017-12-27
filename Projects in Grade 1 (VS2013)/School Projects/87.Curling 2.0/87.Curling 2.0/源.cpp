#include "stdio.h"
#define N 120

void DFS(int x, int y, int step);
void xM(int x, int y, int s);
void xP(int x, int y, int s);
void yM(int x, int y, int s);
void yP(int x, int y, int s);

int board[N][N];//����  ���100*100
int boardx, boardy;//���صĳ���
int stepmin;//�������Сֵ

int main()
{
	int x, y;//�������������

	while (1)
	{
		for (x = 0; x < N; x++)//����������ȫ�����Ϊ9 ��ʾ�߽磨���ã�
		{
			for (y = 0; y < N; y++)
			{
				board[x][y] = 5;
			}
		}
		stepmin = 99999999;//����������

		scanf("%d%d", &boardy, &boardx);//����߽��

		if (boardx == 0 || boardy == 0)//������������������ʱ�� �˳�
		{
			break;
		}

		for (x = 1; x <= boardx; x++)//�ӣ�1,1����ʼ¼������ �Է����ж��Ƿ����
		{
			for (y = 1; y <= boardy; y++)
			{
				scanf("%d", &board[x][y]);
			}
		}

		for (x = 1; x <= boardx; x++)
		{
			for (y = 1; y <= boardy; y++)
			{
				if (board[x][y] == 2)//�ҵ�start��
				{
					board[x][y] = 0;//��start����Ϊ0
					DFS(x, y, 0);
				}
			}
		}

		if (stepmin == 99999999 || stepmin > 10)//���޷����� ����-1
		{
			printf("-1\n");
		}
		else
		{
			printf("%d\n", stepmin);
		}
	}
}


void DFS(int x, int y, int step)
{
	if (step <= 10)
	{
		step++;
		xM(x, y, step);
		xP(x, y, step);
		yM(x, y, step);
		yP(x, y, step);
	}
	else
	{
		return;
	}
}

void xM(int x, int y, int s)//x�Ḻ����
{
	if (board[x - 1][y] == 1)//���ƶ�ǰ�����ж� ����Ա���ʯͷ�����
	{
		return;
	}

	for (; board[x][y] == 0; x--);//��ĩ������ʱ��λ����ĩ����һ��λ�ã�

	if (board[x][y] == 5)//��ĩ֮���Ǳ߽�  �˳�
	{
		return;
	}
	if (board[x][y] == 1)//�������ʯͷ ��ʯͷ����  ��������һ��DFS
	{
		board[x][y] = 0;
		DFS(x + 1, y, s);//����DFS ������ĩ����һ���˻ص���ĩ��
		board[x][y] = 1;//�����λ�ԭ
	}
	if (board[x][y] == 3)//�������λ��Ϊ�յ�
	{
		if (s < stepmin)//�ɹ�ʱ��¼����
		{
			stepmin = s;
		}
		return;
	}
}

void xP(int x, int y, int s)//x��������
{
	if (board[x + 1][y] == 1)//���ƶ�ǰ�����ж� ����Ա���ʯͷ�����
	{
		return;
	}

	for (; board[x][y] == 0; x++);//��ĩ������ʱ��λ����ĩ����һ��λ�ã�

	if (board[x][y] == 5)//��ĩ֮���Ǳ߽�  �˳�
	{
		return;
	}
	if (board[x][y] == 1)//�������ʯͷ ��ʯͷ����  ��������һ��DFS
	{
		board[x][y] = 0;
		DFS(x - 1, y, s);//����DFS ������ĩ����һ���˻ص���ĩ��
		board[x][y] = 1;//�����λ�ԭ
	}
	if (board[x][y] == 3)//�������λ��Ϊ�յ�
	{
		if (s < stepmin)//�ɹ�ʱ��¼����
		{
			stepmin = s;
		}
		return;
	}
}

void yM(int x, int y, int s)//y�Ḻ����
{
	if (board[x][y - 1] == 1)//���ƶ�ǰ�����ж� ����Ա���ʯͷ�����
	{
		return;
	}

	for (; board[x][y] == 0; y--);//��ĩ������ʱ��λ����ĩ����һ��λ�ã�

	if (board[x][y] == 5)//��ĩ֮���Ǳ߽�  �˳�
	{
		return;
	}
	if (board[x][y] == 1)//�������ʯͷ ��ʯͷ����  ��������һ��DFS
	{
		board[x][y] = 0;
		DFS(x, y + 1, s);//����DFS ������ĩ����һ���˻ص���ĩ��
		board[x][y] = 1;//�����λ�ԭ
	}
	if (board[x][y] == 3)//�������λ��Ϊ�յ�
	{
		if (s < stepmin)//�ɹ�ʱ��¼����
		{
			stepmin = s;
		}
		return;
	}
}

void yP(int x, int y, int s)//y��������
{
	if (board[x][y + 1] == 1)//���ƶ�ǰ�����ж� ����Ա���ʯͷ�����
	{
		return;
	}

	for (; board[x][y] == 0; y++);//��ĩ������ʱ��λ����ĩ����һ��λ�ã�

	if (board[x][y] == 5)//��ĩ֮���Ǳ߽�  �˳�
	{
		return;
	}
	if (board[x][y] == 1)//�������ʯͷ ��ʯͷ����  ��������һ��DFS
	{
		board[x][y] = 0;
		DFS(x, y - 1, s);//����DFS ������ĩ����һ���˻ص���ĩ��
		board[x][y] = 1;//�����λ�ԭ
	}
	if (board[x][y] == 3)//�������λ��Ϊ�յ�
	{
		if (s < stepmin)//�ɹ�ʱ��¼����
		{
			stepmin = s;
		}
		return;
	}
}

//#include<iostream>  
//#include<cstring>  
//using namespace std;
//const int Arsize = 5000;
//const int HashTable = 1123;
//struct Node{
//	int x, y;
//	int Maps[22][22];
//	int dist;
//};
//Node location[Arsize];
//int endx, endy, have_find, width, height;
//int head[HashTable], Next[Arsize];
//int Hash(int rear){
//	int i, j, v;
//	for (i = 1, v = 0; i <= width; i++){
//		for (j = 1; j <= height; j++){
//			v = (v << 1) + location[rear].Maps[i][j];
//		}
//	}
//	return v%HashTable;
//}
//int try_to_insert(int rear){
//	int h = Hash(rear);
//	int u = head[h];
//	while (u){
//		if (memcmp(location[u].Maps, location[rear].Maps, sizeof(location[rear].Maps)) == 0 && location[u].x == location[rear].x&&location[u].y == location[rear].y)
//			return 0;
//		u = Next[u];
//	}
//	Next[rear] = head[h];
//	head[h] = rear;
//	return 1;
//}
//
//
//int bfs(void){
//	int front, rear, i, move, move_ok, nowx, nowy;
//	front = 1;
//	rear = 2;
//	while (front<rear){
//		Node & now = location[front];
//		if (location[front].dist>10){
//			return 0;
//		}
//		if (location[front].x == endx&&location[front].y == endy){
//			have_find = 1;
//			return front;
//		}
//		for (i = 1; i <= 4; i++){
//			nowx = now.x;
//			nowy = now.y;
//			move_ok = 0;
//			if (i == 1){
//				if (now.Maps[nowx - 1][nowy] == 1)
//					continue;
//				for (move = nowx - 1; move>0; move--){
//					if (now.Maps[move][nowy] == 1 || now.Maps[move][nowy] == 3){
//						move_ok = 1;
//						break;
//					}
//				}
//				if (move_ok){
//					memcpy(location[rear].Maps, now.Maps, sizeof(now.Maps));
//					location[rear].Maps[move][nowy] = 0;
//					location[rear].dist = now.dist + 1;
//					location[rear].y = nowy;
//					if (now.Maps[move][nowy] == 3)
//						location[rear].x = move;
//					else
//						location[rear].x = move + 1;
//					if (try_to_insert(rear))
//						rear++;
//				}
//			}
//			else if (i == 2){
//				if (now.Maps[nowx + 1][nowy] == 1)
//					continue;
//				for (move = nowx + 1; move <= height; move++){
//					if (now.Maps[move][nowy] == 1 || now.Maps[move][nowy] == 3){
//						move_ok = 1;
//						break;
//					}
//				}
//				if (move_ok){
//					memcpy(location[rear].Maps, now.Maps, sizeof(now.Maps));
//					location[rear].Maps[move][nowy] = 0;
//					location[rear].dist = now.dist + 1;
//					location[rear].y = nowy;
//					if (now.Maps[move][nowy] == 3)
//						location[rear].x = move;
//					else
//						location[rear].x = move - 1;
//					if (try_to_insert(rear))
//						rear++;
//				}
//			}
//			else if (i == 3){
//				if (now.Maps[nowx][nowy - 1] == 1)
//					continue;
//				for (move = nowy - 1; move>0; move--){
//					if (now.Maps[nowx][move] == 1 || now.Maps[nowx][move] == 3){
//						move_ok = 1;
//						break;
//					}
//				}
//				if (move_ok){
//					memcpy(location[rear].Maps, now.Maps, sizeof(now.Maps));
//					location[rear].Maps[nowx][move] = 0;
//					location[rear].dist = now.dist + 1;
//					location[rear].x = nowx;
//					if (now.Maps[nowx][move] == 3)
//						location[rear].y = move;
//					else
//						location[rear].y = move + 1;
//					if (try_to_insert(rear))
//						rear++;
//				}
//			}
//			else{
//				if (now.Maps[nowx][nowy + 1] == 1)
//					continue;
//				for (move = nowy + 1; move <= width; move++){
//					if (now.Maps[nowx][move] == 1 || now.Maps[nowx][move] == 3){
//						move_ok = 1;
//						break;
//					}
//				}
//				if (move_ok){
//					memcpy(location[rear].Maps, now.Maps, sizeof(now.Maps));
//					location[rear].Maps[nowx][move] = 0;
//					location[rear].dist = now.dist + 1;
//					location[rear].x = nowx;
//					if (now.Maps[nowx][move] == 3)
//						location[rear].y = move;
//					else
//						location[rear].y = move - 1;
//					if (try_to_insert(rear))
//						rear++;
//				}
//			}
//		}
//		front++;
//	}
//	return 0;
//}
//int main()
//{
//	int i, j, front;
//	while (cin >> width >> height){
//		if (!height&&!width)
//			break;
//		memset(location, 0, sizeof(location));
//		memset(head, 0, sizeof(head));
//		have_find = 0;
//		for (i = 1; i <= height; i++){
//			for (j = 1; j <= width; j++){
//				cin >> location[1].Maps[i][j];
//				if (location[1].Maps[i][j] == 2){
//					location[1].x = i;
//					location[1].y = j;
//				}
//				if (location[1].Maps[i][j] == 3){
//					endx = i;
//					endy = j;
//				}
//			}
//		}
//		location[1].dist = 0;
//		front = bfs();
//		if (!have_find)
//			cout << "-1\n";
//		else{
//			cout << location[front].dist << endl;
//		}
//	}
//	return 0;
//}