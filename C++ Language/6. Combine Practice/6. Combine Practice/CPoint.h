#include "iostream"

using namespace std;

class CPoint 
{
private:
	double X;
	double Y;

public:
	void InputXY()
	{
		cout << "Please input X and Y." << endl;
		cin >> X >> Y;

		return;
	}
	void GetX()
	{
		cout << "X = " << X << endl;

		return;
	}
	void GetY()
	{
		cout << "Y = " << Y << endl;

		return;
	}
	friend ostream & operator<<(ostream & Output, CPoint & P);
};

ostream & operator<<(ostream & Output, CPoint &P)
{
	Output << "X = " << P.X << endl;
	Output << "Y = " << P.Y << endl;

	return Output;
}