//#include "stdio.h"
//#define N 15000
//
//int heap;//果子的堆数 1 <= heap <= 10000
//int number[N];//每一堆果子的数量  1 <= number[] <= 20000
//int heapcnt;//堆数计数器
//int all = 0;//消耗总和
//int i, j, save, min;//选择排序用
//int z;//最终加和
//int a = 1;//进行第一次排序
//int limit;//数列中比此次加和还小的数
//int limitx;//在寻找limit的时候为了不干扰heapcnt而设置
//
//int main()
//{
//	/*输入信息*/
//	scanf("%d", &heap);
//	for (heapcnt = 0; heapcnt < heap; heapcnt++)
//	{
//		scanf("%d", &number[heapcnt]);
//	}
//
//	for (heapcnt = 0; heapcnt < heap; heapcnt++)
//	{
//		limit = heap;
//		if (a || (number[heapcnt]>number[heapcnt + 1] && heapcnt<heap - 2))
//		{
//			if (a == 0 && number[heapcnt]>number[heapcnt + 1])//寻找 limit
//			{
//				for (limitx = heapcnt; number[heapcnt] > number[limitx + 1] && ((limitx + 1) < heap); limitx++);
//				if (limitx + 1 == heap)
//				{
//					limit = heap;
//				}
//				else
//				{
//					limit = limitx + 1;
//				}
//			}
//			for (i = heapcnt; i < limit; i++)//排序
//			{
//				min = i;
//				for (j = i + 1; j < heap; j++)
//				{
//					if (number[min]>number[j])
//					{
//						min = j;
//					}
//				}
//				if (min != i)
//				{
//					save = number[min];
//					number[min] = number[i];
//					number[i] = save;
//				}
//			}
//			a = 0;//标记  第一次排序完毕
//		}
//		number[heapcnt + 1] = number[heapcnt] + number[heapcnt + 1];
//	}
//
//	for (z = 1; z < heap; z++)
//	{
//		all = all + number[z];
//	}
//	printf("%d\n", all);
//}
///*以上为Original 但错误 WA+TLE*/

/*以下为网络正确答案*/
#include<iostream>
#include<queue>
#include "stdio.h"
using namespace std;
priority_queue<int, vector<int>, greater<int> > q;

int main(){
	int n, x;
	scanf("%d", &n);
	for (; n--; q.push(x))
		scanf("%d", &x);

	for (x = 0; !q.empty(); q.push(n)){
		n = q.top();  q.pop();
		if (q.empty())break;
		n += q.top(); q.pop();
		x += n;
	}
	printf("%d", x);
	return 0;
}