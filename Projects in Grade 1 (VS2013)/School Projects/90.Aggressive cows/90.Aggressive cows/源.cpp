#include "stdio.h"
#include "algorithm"
using namespace std;

bool YN(int mid);

const int maxn = 100002;
const int INF = 1000000000;
int N, C;//N:ţ��ĳ��� C:ţ�ĸ���
int loc[maxn];

int main()
{
	int left, right, mid;//�������ֵ�������

	scanf("%d%d", &N, &C);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &loc[i]);
	}

	sort(loc, loc + N);//��ţ��λ�ô�С��������

	left = 0;//��ʼ��
	right = INF;

	for (int i = 0; i < 100; i++)//�޶�����100��
	{
		mid = left + (right - left) / 2;

		if (YN(mid))
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
	}
	printf("%d\n", left);
}

bool YN(int mid)
{
	int i;
	int last = 0, cur;//��һͷţ  ����Ҫ�ŵ�ţ

	for (i = 1; i < C; i++)
	{
		cur = last + 1;//ÿ�ν�cur��λ��last��ţ�����һ��

		for (; (cur < N) && ((loc[cur] - loc[last]) < mid); cur++);//��ͼ�������е�ţ
		if (cur == N)//���ֻ�����˵�һͷţ�����һ��ţ�� ��˵��mid̫�� ��඼��left��mid֮�� ����false
		{
			return false;
		}
		else//�ѵ�iͷţ�ŵ���cur��ţ����
		{
			last = cur;
		}
	}
	return true;//�����ţȫ������ ��˵�������mid��right֮�� ����true
}