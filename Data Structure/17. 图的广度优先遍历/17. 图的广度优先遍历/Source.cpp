#include "stdio.h"
#include "string.h"

int List[1000][1000];
int ListX = 0, ListY = 0;
char Node[1000];
int NodeC = 0;
char Input;
int NodeSign[100] = { 0 };

void PrintADJList();
void BFS(int Start);

int main()
{
	memset(List, 0, sizeof(List));

	while (1)
	{
		scanf("%c\n", &Input);

		if (Input == '*')
		{
			Node[NodeC] = '\0';
			break;
		}
		else
		{
			Node[NodeC] = Input;
		}

		NodeC++;
	}
	while (1)
	{
		scanf("%d,%d", &ListX, &ListY);

		if (ListX == -1 && ListY == -1)
		{
			break;
		}
		else
		{
			List[ListX][ListY] = 1;
			List[ListY][ListX] = 1;
		}
	}

	PrintADJList();

	printf("the Breadth-First-Seacrh list:");
	BFS(0);

	int LastSearch = 0;
	for (LastSearch = 0;LastSearch < NodeC;LastSearch++)
	{
		if (NodeSign[LastSearch] == 0)
		{
			BFS(LastSearch);
		}
	}
	printf("\n");

	return 0;
}

void PrintADJList()
{
	int MainScan = 0;
	int TrueScan = NodeC - 1;

	printf("the ALGraph is\n");

	for (MainScan = 0;MainScan < NodeC;MainScan++)
	{
		printf("%c", Node[MainScan]);

		for (TrueScan = NodeC - 1;TrueScan >= 0;TrueScan--)
		{
			if (List[MainScan][TrueScan] == 1)
			{
				printf(" %d", TrueScan);
			}
		}

		printf("\n");
	}

	return;
}

void BFS(int Start)
{
	int TrueNodeScan = 0;
	int NodeQueue[1000] = { 0 };
	int Front = 0, Rear = 1;

	NodeQueue[Front] = Start;

	for (Front = 0, Rear = 1;Front < Rear;Front++)
	{
		NodeSign[NodeQueue[Front]] = 1;

		for (TrueNodeScan = NodeC - 1;TrueNodeScan >= 0;TrueNodeScan--)
		{
			if (List[TrueNodeScan][NodeQueue[Front]] == 1)
			{
				if (NodeSign[TrueNodeScan] == 0)
				{
					NodeQueue[Rear] = TrueNodeScan;
					Rear++;

					NodeSign[TrueNodeScan] = 1;
				}
			}
		}

		printf("%c", Node[NodeQueue[Front]]);
	}

	return;
}