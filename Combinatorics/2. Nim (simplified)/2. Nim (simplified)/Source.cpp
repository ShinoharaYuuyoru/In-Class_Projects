#include "iostream"

using namespace std;

int N;
int X;

int Solve(int X);

int main()
{
	cin >> N;
	int Nc;
	for (Nc = 1;Nc <= N;Nc++)
	{
		cin >> X;

		cout << Solve(X) << endl;
	}
}

int Solve(int X)
{
	if (X % 3 == 0)
	{
		return 2;
	}
	if (X % 3 == 1)
	{
		return 0;
	}
	if (X % 3 == 2)
	{
		return 1;
	}
}