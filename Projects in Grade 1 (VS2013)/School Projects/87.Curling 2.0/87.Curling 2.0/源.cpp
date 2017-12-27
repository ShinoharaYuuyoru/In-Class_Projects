#include "stdio.h"
#define N 120

void DFS(int x, int y, int step);
void xM(int x, int y, int s);
void xP(int x, int y, int s);
void yM(int x, int y, int s);
void yP(int x, int y, int s);

int board[N][N];//场地  最大100*100
int boardx, boardy;//场地的长宽
int stepmin;//步骤的最小值

int main()
{
	int x, y;//场地输入计数器

	while (1)
	{
		for (x = 0; x < N; x++)//将整个区域全部标记为9 表示边界（重置）
		{
			for (y = 0; y < N; y++)
			{
				board[x][y] = 5;
			}
		}
		stepmin = 99999999;//步骤数重置

		scanf("%d%d", &boardy, &boardx);//输入边界宽长

		if (boardx == 0 || boardy == 0)//当输入里边有两个零的时候 退出
		{
			break;
		}

		for (x = 1; x <= boardx; x++)//从（1,1）开始录入棋盘 以方便判断是否出界
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
				if (board[x][y] == 2)//找到start点
				{
					board[x][y] = 0;//将start点标记为0
					DFS(x, y, 0);
				}
			}
		}

		if (stepmin == 99999999 || stepmin > 10)//若无法到达 则打出-1
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

void xM(int x, int y, int s)//x轴负方向
{
	if (board[x - 1][y] == 1)//在移动前进行判断 如果旁边有石头则回退
	{
		return;
	}

	for (; board[x][y] == 0; x--);//最末处理（此时定位于最末的下一个位置）

	if (board[x][y] == 5)//最末之后是边界  退出
	{
		return;
	}
	if (board[x][y] == 1)//如果碰到石头 则将石头击碎  并进入下一个DFS
	{
		board[x][y] = 0;
		DFS(x + 1, y, s);//进入DFS （从最末的下一个退回到最末）
		board[x][y] = 1;//将地形还原
	}
	if (board[x][y] == 3)//如果所在位置为终点
	{
		if (s < stepmin)//成功时记录步数
		{
			stepmin = s;
		}
		return;
	}
}

void xP(int x, int y, int s)//x轴正方向
{
	if (board[x + 1][y] == 1)//在移动前进行判断 如果旁边有石头则回退
	{
		return;
	}

	for (; board[x][y] == 0; x++);//最末处理（此时定位于最末的下一个位置）

	if (board[x][y] == 5)//最末之后是边界  退出
	{
		return;
	}
	if (board[x][y] == 1)//如果碰到石头 则将石头击碎  并进入下一个DFS
	{
		board[x][y] = 0;
		DFS(x - 1, y, s);//进入DFS （从最末的下一个退回到最末）
		board[x][y] = 1;//将地形还原
	}
	if (board[x][y] == 3)//如果所在位置为终点
	{
		if (s < stepmin)//成功时记录步数
		{
			stepmin = s;
		}
		return;
	}
}

void yM(int x, int y, int s)//y轴负方向
{
	if (board[x][y - 1] == 1)//在移动前进行判断 如果旁边有石头则回退
	{
		return;
	}

	for (; board[x][y] == 0; y--);//最末处理（此时定位于最末的下一个位置）

	if (board[x][y] == 5)//最末之后是边界  退出
	{
		return;
	}
	if (board[x][y] == 1)//如果碰到石头 则将石头击碎  并进入下一个DFS
	{
		board[x][y] = 0;
		DFS(x, y + 1, s);//进入DFS （从最末的下一个退回到最末）
		board[x][y] = 1;//将地形还原
	}
	if (board[x][y] == 3)//如果所在位置为终点
	{
		if (s < stepmin)//成功时记录步数
		{
			stepmin = s;
		}
		return;
	}
}

void yP(int x, int y, int s)//y轴正方向
{
	if (board[x][y + 1] == 1)//在移动前进行判断 如果旁边有石头则回退
	{
		return;
	}

	for (; board[x][y] == 0; y++);//最末处理（此时定位于最末的下一个位置）

	if (board[x][y] == 5)//最末之后是边界  退出
	{
		return;
	}
	if (board[x][y] == 1)//如果碰到石头 则将石头击碎  并进入下一个DFS
	{
		board[x][y] = 0;
		DFS(x, y - 1, s);//进入DFS （从最末的下一个退回到最末）
		board[x][y] = 1;//将地形还原
	}
	if (board[x][y] == 3)//如果所在位置为终点
	{
		if (s < stepmin)//成功时记录步数
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