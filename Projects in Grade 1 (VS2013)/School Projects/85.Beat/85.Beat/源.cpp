#include "stdio.h"
#define N 20

void DFS(int i, int j, int sum);

int num;//组数
int T[N][N];//Problems
int i, j;//T的横纵
int summax = 1;//可解决总问题数
bool sign[N];//标记

int main()
{
	while (scanf("%d", &num) != EOF)
	{
		for (i = 0; i < num; i++)//T清零
		{
			for (j = 0; j < num; j++)
			{
				T[i][j] = 0;
			}
		}

		for (i = 0; i < num; i++)//输入数据
		{
			for (j = 0; j < num; j++)
			{
				scanf("%d", &T[i][j]);
			}
		}

		summax = 1;//重置每一组数据的max

		for (j = 1; j < num; j++)//第0个问题做完后
		{
			for (i = 0; i < num; i++)//所有问题标记为可访问的
			{
				sign[i] = 1;
			}
			sign[0] = 0;//第0个问题标记为不可访问
			sign[j] = 0;//第j个问题标记为不可访问

			DFS(0, j, 1);
		}
		printf("%d\n", summax+1);
	}
}

void DFS(int i,int j,int s)
{
	int search;//寻找第j行的每一个元素
	s++;

	for (search = 0; search < num; search++)
	{
		if (T[j][search] >= T[i][j] && sign[search])
		{
			sign[search] = 0;
			DFS(j, search, s);
			if (s>summax)
			{
				summax = s;
			}
			sign[search] = 1;
		}
	}
	return;
}


//#include<iostream>  
//#include<cstdio>  
//#include<cstdlib>  
//#include<cstring>  
//#include<string>  
//#include<queue>  
//#include<algorithm>  
//#include<map>  
//#include<iomanip>  
//#define INF 99999999  
//using namespace std;
//
//const int MAX = 15 + 10;
//int s[MAX][MAX], sum, n;
//bool mark[MAX];
//
//void dfs(int id, int num, int sorce){
//	for (int i = 0; i<n; ++i){
//		if (mark[i] || s[id][i]<sorce)continue;
//		mark[i] = true;
//		dfs(i, num + 1, s[id][i]);
//		mark[i] = false;
//	}
//	sum = max(sum, num);
//}
//
//int main(){
//	while (cin >> n){
//		for (int i = 0; i<n; ++i){
//			for (int j = 0; j<n; ++j)cin >> s[i][j];
//		}
//		memset(mark, false, sizeof mark);
//		sum = 0;
//		mark[0] = true;
//		dfs(0, 1, 0);
//		cout << sum << endl;
//	}
//	return 0;
//}