//#include "stdio.h"
//#define N 15000
//
//int heap;//���ӵĶ��� 1 <= heap <= 10000
//int number[N];//ÿһ�ѹ��ӵ�����  1 <= number[] <= 20000
//int heapcnt;//����������
//int all = 0;//�����ܺ�
//int i, j, save, min;//ѡ��������
//int z;//���ռӺ�
//int a = 1;//���е�һ������
//int limit;//�����бȴ˴μӺͻ�С����
//int limitx;//��Ѱ��limit��ʱ��Ϊ�˲�����heapcnt������
//
//int main()
//{
//	/*������Ϣ*/
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
//			if (a == 0 && number[heapcnt]>number[heapcnt + 1])//Ѱ�� limit
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
//			for (i = heapcnt; i < limit; i++)//����
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
//			a = 0;//���  ��һ���������
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
///*����ΪOriginal ������ WA+TLE*/

/*����Ϊ������ȷ��*/
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