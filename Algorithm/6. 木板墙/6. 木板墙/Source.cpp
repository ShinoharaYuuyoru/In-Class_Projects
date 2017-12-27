#include "iostream"
#include "stack"

using namespace std;

class Wood
{
private:
	int BANIS;//Bigger and not in stack.
	int Position;
	long long Length;
	
public:
	void Input(int P)
	{
		BANIS = 0;
		Position = P;
		cin >> Length;
	}
	int rBANIS()
	{
		return BANIS;
	}
	int rPosition()
	{
		return Position;
	}
	long long rLength()
	{
		return Length;
	}
	void cBANIS(int B)//Change BANIS.
	{
		BANIS = B;
	}
}Wall[100010];

stack <class Wood> Straight;
long long MAXSquare = 0;

void Reset();
long long GetMax(long long A, long long B);

int main()
{
	int N = 0;
	class Wood Temp;

	while (1)
	{
		Reset();

		cin >> N;
		if (N == 0)
		{
			break;
		}
		else
		{
			int Counter = 0;
			for (Counter = 0;Counter < N;Counter++)//Input All.
			{
				Wall[Counter].Input(Counter);
			}

			for (Counter = 0;Counter < N;Counter++)//Update BANIS and Check MAXSquare for first time.
			{
				while (Straight.empty() != true && Wall[Counter].rLength() < Straight.top().rLength())
				{
					Temp = Straight.top();
					Straight.pop();
					Wall[Counter].cBANIS(Wall[Counter].rBANIS() + Temp.rBANIS() + 1);

					MAXSquare = GetMax(MAXSquare, Temp.rLength()*(long long)(Counter - Temp.rPosition() + Temp.rBANIS()));
				}
				Straight.push(Wall[Counter]);
			}

			while (Straight.empty() != true)
			{
				Temp = Straight.top();
				Straight.pop();

				MAXSquare = GetMax(MAXSquare, Temp.rLength()*(long long)(N - Temp.rPosition() + Temp.rBANIS()));
			}

			cout << MAXSquare << endl;
		}
	}
}

void Reset()
{
	MAXSquare = -1;

	while (Straight.empty() != true)
	{
		Straight.pop();
	}
}

long long GetMax(long long A, long long B)
{
	if (A >= B)
	{
		return A;
	}
	else
	{
		return B;
	}
}