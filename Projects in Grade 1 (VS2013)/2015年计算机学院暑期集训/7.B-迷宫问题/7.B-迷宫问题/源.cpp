#include "stdio.h"
#include "stack"
#include "queue"

int Maze[5][5] = { 0 };

int main()
{
	int y, x;

	for (y = 0; y < 5; y++)
	{
		for (x = 0; x < 5; x++)
		{
			scanf("%d", &Maze[y][x]);
		}
	}


}

