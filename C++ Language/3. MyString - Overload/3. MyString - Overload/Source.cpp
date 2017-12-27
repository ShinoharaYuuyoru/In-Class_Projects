#include "iostream"
using namespace std;

class MyString
{
private:
	char *STRING;

public:
	MyString(int L)
	{
		STRING = new char[L];
	}

	char& operator[](int n)
	{
		return STRING[n];
	}

	friend ostream & operator<<(ostream & Output,MyString & STR)
	{
		int P = 0;
		for (P = 0;STR.STRING[P] != '\0';P++)
		{
			Output << STR.STRING[P];
		}

		return Output;
	}
};

int main()
{
	MyString str(10);     // 10 is the length of str.
	char *S = "Welcome!";

	for (int i = 0; i < 10; i++)
	{
		str[i] = S[i];
	}
	cout << str << endl;

	return 0;
}