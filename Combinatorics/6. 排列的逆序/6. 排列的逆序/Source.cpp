#include "iostream"
using namespace std;

class Case
{
private:
	int n;
	int k;
	int kCopy;
	int Kari[16];
	int Honmono[16];
	bool HonmonoSign[16];

public:
	Case()
	{
		cin >> n;
		cin >> k;
		kCopy = k - 1;
		
		int Reset = 0;
		for (Reset = 0;Reset < 16;Reset++)
		{
			Kari[Reset] = 0;
			Honmono[Reset] = 0;
			HonmonoSign[Reset] = false;
		}
	}
	void Do();
	int SetKari(int X);
	void SetHonmono();
	~Case()
	{
		int Out = 0;
		for (Out = 1;Out < n;Out++)
		{
			cout << Honmono[Out] << ' ';
		}
		cout << Honmono[Out] << endl;
	}
};
void Case::Do()
{
	int P = 0;
	for (P = 1;P <= n;P++)
	{
		Kari[P] = SetKari(P);
	}
	
	SetHonmono();
}
int Case::SetKari(int X)
{
	if (X == n)
	{
		return 0;
	}
	else
	{
		int Num = n - X;
		int Division = 0;
		int AfterDiv = 0;

		for (Division = 1;Num >= 1;Num--)
		{
			Division = Division*Num;
		}

		AfterDiv = kCopy / Division;
		kCopy = kCopy%Division;
		
		return AfterDiv;
	}
}
void Case::SetHonmono()
{
	int SetNum = 0;
	int Counter = 0;
	int Position = 0;

	for (SetNum = 1;SetNum <= n;SetNum++)
	{
		for (Counter=0,Position = 1;Counter <= Kari[SetNum];Position++)
		{
			if (HonmonoSign[Position] == false)
			{
				Counter++;
			}
			else
			{
				continue;
			}
		}
		Position--;
		Honmono[Position] = SetNum;
		HonmonoSign[Position] = true;
	}

	return;
}

int main()
{
	int m = 0;
	int mC = 0;

	cin >> m;

	for (mC = 1;mC <= m;mC++)
	{
		Case* Each;
		Each = new Case;

		Each->Do();

		delete Each;
	}

	return 0;
}