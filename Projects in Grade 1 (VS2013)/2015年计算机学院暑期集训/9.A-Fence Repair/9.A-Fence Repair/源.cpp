#include "iostream"
#include "stdio.h"
#include "queue"
#include "functional"

using namespace std;

int main()
{
	priority_queue<int, vector<int>, greater<int> > q;

	int N;
	__int64 line[20005];
	
	__int64 ans = 0;
	__int64 temp;

	scanf("%d", &N);

	for (int Nc = 0; Nc < N; Nc++)
	{
		scanf("%I64d", &line[Nc]);

		q.push(line[Nc]);
	}

	if (N == 1)//只有一个元素
	{
		printf("%I64d", line[0]);
		return 0;
	}

	int min1, min2;//记录堆中最小的两个元素
	for (;;)
	{
		min1 = q.top();
		q.pop();
		min2 = q.top();
		q.pop();

		temp = min1 + min2;
		ans = ans + temp;

		if (q.empty() == 1)
		{
			break;
		}
		q.push(temp);
	}
	printf("%I64d\n", ans);
	return 0;
}