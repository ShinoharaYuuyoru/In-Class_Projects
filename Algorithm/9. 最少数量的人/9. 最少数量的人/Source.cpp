//#include <stdio.h>
//#include <stdlib.h>
//
//char record[500];
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	char clear = getchar();
//	for (int count = 0; count < n; count++)
//	{
//		//int cnt_plus = 0;
//		//int cnt_minus = 0;
//		//int len = 0;
//		//char sign = '0';
//		int in = 0;
//		int out = 0;
//
//		int diff = 0;
//
//		while (1)
//		{
//			//record[len] = getchar();
//			char input = getchar();
//			if (input != '\n')
//			{
//				//if (len == 0) // initialize sign
//				//{
//				//	sign = record[0];
//				//	diff++;
//				//}
//				//if (record[len] == '-') cnt_minus++; // modify sign
//				//else cnt_plus++;
//				//if (cnt_plus - cnt_minus > 1) sign = '+';
//				//else if (cnt_minus - cnt_plus > 1) sign = '-';
//				//if (len > 0 && record[len] == record[len - 1] && record[len] == sign)
//				//{
//				//	diff++;
//				//}
//				//len++;
//				if (input == '+') // +
//				{
//					if (out > 0) out--;
//					in++;
//				}
//				else  // -
//				{
//					if (in > 0) in--;
//					out++;
//				}
//			}
//			else break;
//		}
//
//		// ------ //
//
//		printf("%d\n", in + out);
//	}
//
//	return 0;
//}

#include "iostream"
using namespace std;

int main()
{
	int N;
	cin >> N;
	getchar();
	int Nc;
	char T;
	int In = 0;
	int Out = 0;

	for (Nc = 1; Nc <= N; Nc++)
	{
		In = 0;
		Out = 0;

		while (1)
		{
			T = getchar();
			if (T == '\n')
			{
				break;
			}
			else
			{
				if (T == '+')
				{
					In++;
					if (Out > 0)
					{
						Out--;
					}
				}
				else
				{
					Out++;
					if (In > 0)
					{
						In--;
					}
				}
			}
		}

		cout << In + Out << endl;
	}
}