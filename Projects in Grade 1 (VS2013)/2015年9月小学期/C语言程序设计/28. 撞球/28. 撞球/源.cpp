#include "stdio.h"
#include "math.h"

int main()
{
	double X, Y;
	double X0, Y0;
	double X1, Y1;
	double ANS;
	char Order[1005];
	int OrderC;

	scanf("%lf%lf", &X, &Y);
	scanf("%lf%lf", &X0, &Y0);
	scanf("%lf%lf", &X1, &Y1);
	getchar();
	fgets(Order, 1005, stdin);

	for (OrderC = 0;Order[OrderC] != '\0';OrderC++)
	{
		if (Order[OrderC] == 'F')
		{
			Y0 = 0 - Y0;
		}
		if (Order[OrderC] == 'B')
		{
			Y0 = Y - Y0 + Y;
		}
		if (Order[OrderC] == 'L')
		{
			X0 = 0 - X0;
		}
		if (Order[OrderC] == 'R')
		{
			X0 = X - X0 + X;
		}
	}

	ANS = sqrt(((X1 - X0)*(X1 - X0) + (Y1 - Y0)*(Y1 - Y0)));
	printf("%.4lf\n", ANS);
}