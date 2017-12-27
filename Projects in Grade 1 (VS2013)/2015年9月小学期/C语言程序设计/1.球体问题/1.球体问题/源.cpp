#include "stdio.h"
#include "math.h"
#define pi 2*acos(0.0)

double Acreage(double r1, double r2, double h);
double Volume(double r1, double r2, double h);

int main()
{
	int N;/*组数*/
	double R1, R2, d;
	double w;
	double s;
	double density;

	double Sans, Vans;

	scanf("%d", &N);

	while (N >= 1)
	{
		double H;/*球缺球冠高度*/

		scanf("%lf%lf%lf%lf%lf", &R1, &R2, &d, &w, &s);

		H = (R1 + R2 - d) / 2.0;
		Sans = Acreage(R1, R2, H);
		Vans = Volume(R1, R2, H);

		density = w / Vans;

		if (density > s)
		{
			printf("%.4lf %.4lf\n", Vans, Sans);
			printf("The Paired-Sphere Sinks.\n");
		}
		else
		{
			if (density < s)
			{
				printf("%.4lf %.4lf\n", Vans, Sans);
				printf("The Paired-Sphere Floats.\n");
			}
			else
			{
				printf("%.4lf %.4lf\n", Vans, Sans);
				printf("For Freedom!\n");
			}
		}

		N--;
	}
}

double Acreage(double r1, double r2, double h)
{
	double SR1, SR2;
	double Crown1, Crown2;/*球冠面积*/
	
	SR1 = 4*pi*r1*r1;
	SR2 = 4*pi*r2*r2;

	Crown1 = 2 * pi*r1*h;
	Crown2 = 2 * pi*r2*h;

	return SR1 - Crown1 + SR2 - Crown2;
}

double Volume(double r1, double r2, double h)
{
	double VR1, VR2;
	double V1, V2;/*球缺体积*/

	VR1 = (4.0 / 3.0)*pi*r1*r1*r1;
	VR2 = (4.0 / 3.0)*pi*r2*r2*r2;

	V1 = (pi / 3.0)*(3.0*r1 - h)*h*h;
	V2 = (pi / 3.0)*(3.0*r2 - h)*h*h;

	return VR1 - V1 + VR2 - V2;
}