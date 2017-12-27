//Copyright © PiaoQuanyu. All Rights Reserved.

#include "iostream"
#include "cmath"
using namespace std;

typedef class EQUATIONSOLVE
{
public:
	void InputParameter();
	void SolveAndOutput();
	EQUATIONSOLVE() 
	{
		A = 0;
		B = 0;
		C = 0;
		X = 0;
		X1 = 0;
		X2 = 0;
	}

private:
	int Flag;
	double A;
	double B;
	double C;
	double X;
	double R;//Real Number
	double X1;
	double X2;

}EquationSolve;

void EQUATIONSOLVE::InputParameter()
{
	cout << "Please input the parameters: A B C" << endl;
	cin >> A >> B >> C;

	return;
}
void EQUATIONSOLVE::SolveAndOutput()
{
	if (A == 0)//Has only one Real Root.
	{
		if (B == 0)//A and B = 0.
		{
			if (C == 0)//0 = 0.
			{
				cout << "0 = 0!" << endl;
			}
			else// C != 0.
			{
				cout << "Error! " << C << " != 0" << endl;
			}
		}
		else
		{
			X = (0.0 - C) / B;
			cout << "This Equation has only one Real Number Root. It is:" << endl;
			cout << "X = " << X << "." << endl;

			return;
		}
	}
	else
	{
		double Delta;

		Delta = B*B - 4 * A*C;

		if (Delta > 0)//Has two diffrent Real Roots.
		{
			X1 = ((0 - B) + sqrt(Delta)) / (2 * A);
			X2 = ((0 - B) - sqrt(Delta)) / (2 * A);

			cout << "This Equation has two diffrent Real Number Roots. They are:" << endl;
			cout << "X1 = " << X1 << "; " << endl;
			cout << "X2 = " << X2 << "." << endl;

			return;
		}
		else
		{
			if (Delta == 0)//Has two same Roots.
			{
				X1 = X2 = (0 - B) / (2 * A);
				
				cout << "This Equation has two same Real Number Roots. They are:" << endl;
				cout << "X1 = X2 = " << X1 << "." << endl;

				return;
			}
			else//Has two diffrent Imaginary Roots.
			{
				Delta = 0 - Delta;
				R = (0 - B) / (2 * A);

				cout << "This Equation has two diffrent Imaginary Roots. They are:" << endl;
				cout << "X1 = " << R << " + " << sqrt(Delta) / (2 * A) << "i; " << endl;
				cout << "X2 = " << R << " - " << sqrt(Delta) / (2 * A) << "i." << endl;

				return;
			}
		}
	}
}

int main()
{
	EquationSolve Equa;

	Equa.InputParameter();
	Equa.SolveAndOutput();

	return 0;
}