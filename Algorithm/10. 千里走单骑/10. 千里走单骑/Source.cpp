#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

int T;
int N;
int A[1024][1024];
int visited[1024];
double P[1024];
double Pmax;
class InQ
{
public:
	int n;
	double Pnow;

	InQ(int _n = 0, double _p = 0) :n(_n), Pnow(_p)	//Reset.
	{
		if (n > N || n < 0) while (1);	//Error. Great!
		if (Pnow < 0 || Pnow > 1) while (1);
	}

	bool operator< (const InQ m) const
	{
		return (this->Pnow < m.Pnow);
	}
};

void Input();
void Reset();

int main()
{
	scanf("%d", &T);

	int Tc;
	for (Tc = 1; Tc <= T; Tc++)
	{
		Input();
		priority_queue<InQ> Q;
		InQ begin(1, 1);
		Q.push(begin);
		A[1][1] = 0;	//Set source point unvisitable.

		while (!Q.empty())	//BFS
		{
			if (A[1][N] == 1)	//Easy to get Endpoint.
			{
				Pmax = 1;
				break;
			}

			const InQ cur = Q.top();
			if (cur.n == N || cur.Pnow < 0.0001)	//Break.
			{
				Pmax = cur.Pnow;
				break;
			}
			Q.pop();

			int k = 0;	//Not get end yet.
			for (k = 1; k <= N; k++)
			{
				if (A[cur.n][k] == 1 && visited[k] == 0)
				{
					visited[k] = 1;
					InQ temp(k, cur.Pnow*P[k]);
					if (temp.Pnow >= 0.0001)
					{
						Q.push(temp);
					}
				}
			}
		}

		if (Pmax < 0.0001) 
		{
			printf("Case %d: Cannot reach!\n", Tc); 
		}
		else
		{
			printf("Case %d: %.4lf\n", Tc, Pmax);
		}
	}
}

void Input()
{
	Reset();
	scanf("%d", &N);
	int Ncx = 0;
	int Ncy = 0;
	for (Ncx = 1; Ncx <= N; Ncx++)
	{
		for (Ncy = 1; Ncy <= N; Ncy++)
		{
			scanf("%d", &A[Ncx][Ncy]);
		}
		visited[Ncx] = 0;
	}
	for (Ncx = 1; Ncx <= N; Ncx++)
	{
		A[Ncx][Ncx] = 0;
	}
	for (Ncx = 2; Ncx <= N - 1; Ncx++)
	{
		scanf("%lf", &P[Ncx]);
	}
	P[1] = P[N] = 1;

	return;
}

void Reset()
{
	N = 0;
	memset(A, 0, sizeof(A));
	memset(P, 0, sizeof(P));
	Pmax = 0;

	return;
}