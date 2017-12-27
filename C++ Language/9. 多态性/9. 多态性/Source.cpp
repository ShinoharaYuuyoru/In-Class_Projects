#include "iostream"

using namespace std;

class Vehicle
{
public:
	virtual double Fee() = 0;
};

class Car :public Vehicle
{
private:
	double Distance;
	double Weight;

public:
	double Fee()
	{
		cout << "Please input Car's running Distance and Weight." << endl;
		cin >> Distance;
		cin >> Weight;

		return Distance*1.2 + Weight*1.1;
	}
};

class Ship :public Vehicle
{
private:
	double Distance;
	double Weight;

public:
	double Fee()
	{
		cout << "Please input Ship's running Distance and Weight." << endl;
		cin >> Distance;
		cin >> Weight;

		return Distance*1.05 + Weight*0.9;
	}
};

class Plane :public Vehicle
{
private:
	double Distance;
	double Weight;

public:
	double Fee()
	{
		cout << "Please input Plane's running Distance and Weight." << endl;
		cin >> Distance;
		cin >> Weight;

		return Distance*1.15 + Weight*1.05;
	}
};

int main()
{
	Vehicle *BaseVehicle;
	Car Car1;
	Ship Ship1;
	Plane Plane1;

	BaseVehicle = &Car1;
	cout << "The Car's Fee is:";
	cout << BaseVehicle->Fee() << endl;
	BaseVehicle = &Ship1;
	cout << "The Ship's Fee is:";
	cout << BaseVehicle->Fee() << endl;
	BaseVehicle = &Plane1;
	cout << "The Plane's Fee is:";
	cout << BaseVehicle->Fee() << endl;

	return 0;
}