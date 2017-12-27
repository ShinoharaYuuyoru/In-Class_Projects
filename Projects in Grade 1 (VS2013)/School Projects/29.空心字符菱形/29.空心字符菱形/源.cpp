#include "stdio.h"
int main()
{
	char cha;
	int l,chac,chan,space1,space2,count;
	scanf("%c%d", &cha,&l);
	chac = (int)cha;
	chan = (int)cha;
	for (count = 1; count <= l; count++)
	{
		for (space1 = l-count; space1 >= 1; space1--)
			printf(" ");
		for (; chac <= chan + l;)
		{
			printf("%c", chac);
			if (count == 1)
			{
				printf("\n");
				chac++;
				break;
			}
			else
			{
				for (space2 = 1; space2 <= ((count - 1) * 2 - 1) && l >= 2; space2++)
					printf(" ");
				printf("%c\n", chac);
				chac++;
				break;
			}
		}
	}
	for (count = count - l, chac = chan + l - 2; count <= l - 1; count++)
	{
		for (space1 = 1; space1 <=count ; space1++)
			printf(" ");
		for (; chac >= l;)
		{
			printf("%c", chac);
			if (count == l-1)
			{
				printf("\n");
				chac--;
				break;
			}
			else
			{
				for (space2 = 1; space2 <= ((l-count-1)*2-1) && l >= 2; space2++)
					printf(" ");
				printf("%c\n", chac);
				chac--;
				break;
			}
		}
	}
}