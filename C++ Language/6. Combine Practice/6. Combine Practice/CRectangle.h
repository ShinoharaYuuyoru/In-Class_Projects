#include "iostream"

using namespace std;

class CRectangle
{
private:
	double L;
	double H;
	CPoint P;

public:
	void CatchPoint()
	{
		P.InputXY();
		P.GetX();
		P.GetY();
		cout << P;
	}
	void Input()
	{
		cout << "Please input L and H." << endl;
		cin >> L >> H;
	}
	void GetL()
	{
		cout << "L = " << L << endl;
	}
	void GetH()
	{
		cout << "H = " << H << endl;
	}
	void Perimeter()
	{
		cout << "C = " << 2 * (L + H) << endl;
	}
	void Area()
	{
		cout << "S = " << L*H << endl;
	}
};