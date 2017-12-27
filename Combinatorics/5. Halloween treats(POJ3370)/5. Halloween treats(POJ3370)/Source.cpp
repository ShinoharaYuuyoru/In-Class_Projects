#include "stdio.h"
#include "string.h"

void Output(int x, int y);

int main()
{
	int In[100005];
	int Complement[100005];
	int c, n;
	int ncounter;
	int ComplementTemp;

	while ((scanf("%d%d", &c, &n)), c + n)
	{
		memset(Complement, 0, sizeof(Complement));

		for (ncounter = 1; ncounter <= n; ncounter++)
		{
			scanf("%d", &In[ncounter]);
		}

		for (ComplementTemp = 0, ncounter = 1; ncounter <= n; ncounter++)
		{
			
			ComplementTemp = (ComplementTemp + In[ncounter]) % c;
			if (ComplementTemp == 0)
			{
				Output(1, ncounter);

				break;
			}
			if (Complement[ComplementTemp])
			{
				Output(Complement[ComplementTemp] + 1, ncounter);

				break;
			}
			else
			{
				Complement[ComplementTemp] = ncounter;
			}
		}
	}
}

void Output(int x, int y)
{
	for (; x < y; x++)
	{
		printf("%d ", x);
	}
	printf("%d\n", x);

	return;
}