#include "iostream"

using namespace std;

int main()
{
	int CaseCounter;
	int p, e, i, d;
	int ANS;

	for (CaseCounter = 1;; CaseCounter++)
	{
		cin >> p >> e >> i >> d;
		if (p == -1 && e == -1 && i == -1 && d == -1)
		{
			break;
		}
		else
		{
			ANS = (5544 * p + 14421 * e + 1288 * i - d + 21252) % 21252;
			if (ANS == 0)
			{
				ANS = 21252;
			}

			cout << "Case " << CaseCounter << ": the next triple peak occurs in "<<ANS<<" days." << endl;
		}
	}
}