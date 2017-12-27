#include "iostream"
#include "string"

using namespace std;

class Employee
{
private:
	string Name;
	double Salary;

public:
	Employee()
	{
		Name[0] = '\0';
		double Salary = 0;
	}
	void SetName(string N)
	{
		Name = N;
	}
	void SetSalary(double S)
	{
		Salary = S;
	}
	string GetName()
	{
		return Name;
	}
	double GetSalary()
	{
		return Salary;
	}
};

class Technician :protected Employee
{
private:
	Employee Tech;
	double Time;
	double TimeSalary;

public:
	void SetTechName()
	{
		cout << "Please input the technician's name." << endl;
		string N;
		cin >> N;
		Tech.SetName(N);
	}
	void Pay()
	{
		cout << "Please input the working hours." << endl;
		cin >> Time;
		TimeSalary = 100 * Time;
		Tech.SetSalary(TimeSalary);
	}
	void Print()
	{
		cout << "Technician: " << Tech.GetName() << ", gets 100$ * " << Time << "hour(s) = " << Tech.GetSalary() << "$." << endl;
	}
};

class Manager :virtual protected Employee
{
private:
	Employee Mana;
	double UnchangeSalary = 7000;

public:
	void SetManaName()
	{
		cout << "Please input the Manager's name." << endl;
		string N;
		cin >> N;
		Mana.SetName(N);
	}
	void Pay()
	{
		Mana.SetSalary(UnchangeSalary);
	}
	void Print()
	{
		cout << "Manager: " << Mana.GetName() << ", gets " << Mana.GetSalary() << "$." << endl;
	}
};

class Salesman :virtual protected Employee
{
private:
	Employee Sales;
	double SalePoint;
	double SaleSalary;

public:
	void SetSalesName()
	{
		cout << "Please input the Salesman's name." << endl;
		string N;
		cin >> N;
		Sales.SetName(N);
	}
	void Pay()
	{
		cout << "Please input the salePoint." << endl;
		cin >> SalePoint;
		SaleSalary = 0.05 * SalePoint;
		Sales.SetSalary(SaleSalary);
	}
	void Print()
	{
		cout << "Salesman: " << Sales.GetName() << ", gets 0.05 * " << SalePoint << "point(s) = " << Sales.GetSalary() << "$." << endl;
	}
};

class SalesManager :private Manager, private Salesman
{
private:
	Employee SalesMana;
	double GroupSalePoint;
	double GroupSaleSalary;

public:
	void SetSalesManaName()
	{
		cout << "Please input the SalesManager's name." << endl;
		string N;
		cin >> N;
		SalesMana.SetName(N);
	}
	void Pay()
	{
		cout << "Please input the GroupSalePoint." << endl;
		cin >> GroupSalePoint;
		GroupSaleSalary = 0.005 * GroupSalePoint;
		SalesMana.SetSalary(4000 + GroupSaleSalary);
	}
	void Print()
	{
		cout << "SalesManager: " << SalesMana.GetName() << ", gets 4000 + (0.005 * " << GroupSalePoint << "point(s)) = " << SalesMana.GetSalary() << "$." << endl;
	}
};

int main()
{
	cout << "Please input NUMBER to get start or exit." << endl;
	cout << "1. Technician." << endl;
	cout << "2. Manager." << endl;
	cout << "3. Salesman." << endl;
	cout << "4. SalesManager." << endl;
	cout << "0. Exit." << endl;

	while (1)
	{
		char Temp = '0';
		cin >> Temp;

		if (Temp != '0' && Temp != '1' && Temp != '2' && Temp != '3' && Temp != '4')
		{
			cout << "Error! Please input again!" << endl;

			continue;
		}
		if (Temp == '0')
		{
			cout << "Thanks for using!" << endl;
			break;
		}
		else
		{
			if (Temp == '1')
			{
				Technician *T = new Technician;
				T->SetTechName();
				T->Pay();
				T->Print();
				delete T;
			}
			if (Temp == '2')
			{
				Manager *M = new Manager;
				M->SetManaName();
				M->Pay();
				M->Print();
				delete M;
			}
			if (Temp == '3')
			{
				Salesman *S = new Salesman;
				S->SetSalesName();
				S->Pay();
				S->Print();
				delete S;
			}
			if (Temp == '4')
			{
				SalesManager *SM = new SalesManager;
				SM->SetSalesManaName();
				SM->Pay();
				SM->Print();
				delete SM;
			}

			cout << endl;
			cout << "Please input next one number or input 0 to exit." << endl;
		}
	}
}