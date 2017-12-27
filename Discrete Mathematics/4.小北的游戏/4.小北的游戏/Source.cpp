#include "stdio.h"
#include "string.h"

int MAP[2000][2000];
int DEGREE[2000];
int SoldierNum = 0;
int AllPoint = 0;
int PNCounter = 0;
int PointSign = 0;
int AllRoad = 0;

void Delete();

int main()
{
	while (scanf("%d", &AllPoint) != EOF)
	{
		/*Reset*/
		SoldierNum = 0;
		PNCounter = 0;
		PointSign = 0;
		AllRoad = 0;
		/*Reset*/

		for (PNCounter = 0;PNCounter < AllPoint;PNCounter++)
		{
			scanf("%d:(%d)", &PointSign, &AllRoad);
			if (AllRoad > 0)
			{
				int ARCounter = 0;
				int RoadTo = 0;
				for (ARCounter = 0;ARCounter < AllRoad;ARCounter++)
				{
					scanf("%d", &RoadTo);

					MAP[PointSign][RoadTo] = 1;
					DEGREE[PointSign]++;
					MAP[RoadTo][PointSign] = 1;
					DEGREE[RoadTo]++;
				}
			}
			else
			{
				continue;
			}
		}

		Delete();

		printf("%d\n", SoldierNum);
	}
}

void Delete()
{
	int DeleteSearch = 0;

	for (DeleteSearch = 0;DeleteSearch < AllPoint;DeleteSearch++)
	{
		if (DEGREE[DeleteSearch] == 1)
		{
			int Hashidate = 0;//Delete the road between the POINT and Father
			for (Hashidate = 0;Hashidate < AllPoint;Hashidate++)
			{
				if (MAP[DeleteSearch][Hashidate] == 1)
				{
					MAP[DeleteSearch][Hashidate] = 0;
					DEGREE[DeleteSearch]--;
					MAP[Hashidate][DeleteSearch] = 0;
					DEGREE[Hashidate]--;
					
					int Chikuma = 0;//Delete the road between Father and their children
					for (Chikuma = 0;Chikuma < AllPoint;Chikuma++)
					{
						if (MAP[Hashidate][Chikuma] == 1)
						{
							MAP[Hashidate][Chikuma] = 0;
							DEGREE[Hashidate]--;
							MAP[Chikuma][Hashidate] = 0;
							DEGREE[Chikuma]--;
						}
					}
				}
			}

			SoldierNum++;
			DeleteSearch = -1;
		}
	}

	return;
}