#include "CPoint.h"
#include "CRectangle.h"

using namespace std;

int main()
{
	CRectangle Rectangle;

	Rectangle.Input();
	Rectangle.GetL();
	Rectangle.GetH();
	Rectangle.Perimeter();
	Rectangle.Area();

	Rectangle.CatchPoint();

	return 0;
}