#include "iostream"

using namespace std;

template <class ARRAY>
class MyArray
{
private:
	int Size;
	ARRAY *ARPointer;

public:
	MyArray(int X)
	{
		Size = X;
		ARPointer = new ARRAY[Size + 1];
	}

	ARRAY& operator[](int n)
	{
		return ARPointer[n];
	}

	friend ostream & operator<<(ostream& output, MyArray& AR)
	{
		int i = 0;
		for (i = 0;i <= AR.Size;i++)
		{
			output << AR.ARPointer[i] << endl;
		}
		return output;
	}

	~MyArray()
	{
		delete[] ARPointer;
	}
};

int main()
{
	MyArray<int>	intArray(10);		// Here 10 is the number of intArray's elements.
	for (int i = 0; i <= 10; i++)
	{
		intArray[i] = i * i;
	}
	cout << intArray;				// Print every element in the intArray

	return 0;
}