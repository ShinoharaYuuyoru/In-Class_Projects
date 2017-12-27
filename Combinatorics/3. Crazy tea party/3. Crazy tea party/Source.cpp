#include "iostream"

using namespace std;

int main()
{
	int N;
	int Nc;
	int X;

	cin >> N;
	for (Nc = 1; Nc <= N; Nc++)
	{
		cin >> X;
		cout << X*X / 4 - X / 2 << endl;
	}
}