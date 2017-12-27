#include "stdio.h"

char List[1000];
int ListC = 1;
int NodesNumber[1000] = { 0 };
int MaxDegree = 0;
int NodesNumberPrint = 0;

int SpaceC = 0;

void BuildTree();

int main()
{
	scanf("%s", List);

	BuildTree();

	printf("Degree of tree: %d\n", MaxDegree);
	for (;NodesNumberPrint <= MaxDegree;NodesNumberPrint++)
	{
		printf("Number of nodes of degree %d: %d\n", NodesNumberPrint, NodesNumber[NodesNumberPrint]);
	}

	return 0;
}

void BuildTree()
{
	int Degree = 0;

	for (;List[ListC] != '\0';ListC++)
	{
		if (List[ListC] == '(')
		{
			Degree++;
			ListC++;
			SpaceC++;
			BuildTree();
		}
		if (List[ListC] == ',')
		{
			continue;
		}
		if (List[ListC] == ')')
		{
			if (List[ListC - 1] == '(')
			{
				ListC++;
				SpaceC--;

				if (Degree > MaxDegree)
				{
					MaxDegree = Degree;
				}

				return;
			}
			else
			{
				ListC++;
				SpaceC--;
				break;
			}
		}

		int PrintSpace = 1;
		for (;PrintSpace <= SpaceC;PrintSpace++)
		{
			printf("    ");
		}
		printf("%c\n", List[ListC]);
	}

	NodesNumber[Degree]++;

	if (Degree > MaxDegree)
	{
		MaxDegree = Degree;
	}

	return;
}