#include "stdio.h"
int main()
{
	int s, f, fj;
	float sj, jj;
	if (scanf("%d%d", &s, &f));
	sj = 360 - (s * 30 + f*0.5);
	fj = 6 * f;
	jj = fj + sj;
	if (jj>180)
		jj = 360 - jj;
    if (jj < 0)
		jj = -jj;
    printf("At %d:%02d the angle is %.1f degrees.\n",s,f,jj);
}