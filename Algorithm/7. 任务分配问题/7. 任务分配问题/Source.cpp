#include "iostream"

using namespace std;

class Work
{
private:
	int N;
	int WandT[12][12];	//Work and Time;
	int Min[12];
	int Sign[12];
	int MinTime;

public:
	Work()
	{
		cin >> N;
		MinTime = 999999999;

		int Ex;
		int Ey;
		for (Ex = 0;Ex < N;Ex++)	//Insert.
		{
			Min[Ex] = 999999999;
			Sign[Ex] = 0;
			for (Ey = 0; Ey < N;Ey++)
			{
				cin >> WandT[Ex][Ey];
			}
		}

		for (Ex = 0;Ex < N;Ex++)	//Get Min in every column.
		{
			for (Ey = 0;Ey < N;Ey++)
			{
				if (WandT[Ex][Ey] < Min[Ey])
				{
					Min[Ey] = WandT[Ex][Ey];
				}
			}
		}
	}
	void DFSandCUT(int Mem, int Sum);	//Use DFS and Cut.
	void Output()
	{
		cout << MinTime << endl;

		return;
	}
};

void Work::DFSandCUT(int Col, int Sum)
{
	if (Col == N)
	{
		if (Sum < MinTime)
		{
			MinTime = Sum;
		}
	}
	else
	{
		int Ey = 0;
		for (Ey = 0;Ey < N;Ey++)
		{
			if (WandT[Col][Ey] + Sum < MinTime)
			{
				if (Sign[Ey] != 1)
				{
					int CutSum = Sum + WandT[Col][Ey];
					int CutAddCounter = 0;
					for (CutAddCounter = 0;CutAddCounter < N;CutAddCounter++)	//Add for Cut.
					{
						if (Sign[CutAddCounter] != 1 && CutAddCounter != Ey)
						{
							CutSum = CutSum + Min[CutAddCounter];
						}
					}

					if (CutSum < MinTime)	//Cut and DFS.
					{
						Sign[Ey] = 1;
						DFSandCUT(Col + 1, Sum + WandT[Col][Ey]);
						Sign[Ey] = 0;
					}
				}
			}
		}
	}

	return;
}

int main()
{
	class Work W;
	W.DFSandCUT(0, 0);
	W.Output();

	return 0;
}