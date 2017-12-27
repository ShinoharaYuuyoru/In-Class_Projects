#include "iostream"
using namespace std;

class Case
{
private:
	int n;
	int k;

public:
	Case()
	{
		cin >> n;
		cin >> k;
	}
	~Case()
	{

	}
};

int main()
{
	int m = 0;
	int mC = 0;

	cin >> m;

	for (mC = 1;mC <= m;mC++)
	{
		Case* Each;
		Each = new Case;

		delete Each;
	}

	return 0;
}