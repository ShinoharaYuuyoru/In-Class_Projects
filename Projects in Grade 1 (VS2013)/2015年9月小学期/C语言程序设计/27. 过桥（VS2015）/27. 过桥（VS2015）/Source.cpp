#include "stdio.h"
#include "string.h"

struct Q
{
	int LeftSheep;
	int LeftWolf;
	int RightSheep;
	int RightWolf;
	int Step;
}Queue[40005];
int QueueFront;
int QueueRear;
int Visit[2][201][201];/*左右，羊，狼*/

int G;
int x, y, n;
int ncount;
int LorR;
int BringSheep;
int BringWolf;

int main()
{
	scanf("%d", &G);

	while (G >= 1)
	{
		scanf("%d%d%d", &x, &y, &n);
		/*如果没有羊*/
		if (x == 0)
		{
			if (y > n)
			{
				printf("%d\n", (y / n) * 2 + 1);
				G--;
				continue;
			}
			else
			{
				printf("1\n");
				G--;
				continue;
			}
		}
		/*END*/

		/*Reset*/
		for (QueueFront = 0;QueueFront < 40005;QueueFront++)
		{
			Queue[QueueFront].LeftSheep = 0;
			Queue[QueueFront].LeftWolf = 0;
			Queue[QueueFront].RightSheep = 0;
			Queue[QueueFront].RightWolf = 0;
			Queue[QueueFront].Step = 0;
		}
		memset(Visit, 0, sizeof(int) * 2 * 201 * 201);

		Queue[0].LeftSheep = x;
		Queue[0].LeftWolf = y;
		Queue[0].Step = 0;
		QueueFront = 0;
		QueueRear = 1;
		Visit[0][x][y] = 1;
		/*Reset End*/

		for (;QueueFront <= QueueRear;QueueFront++)
		{
			if (QueueFront == QueueRear)
			{
				printf("-1\n");
				break;
			}
			else
			{
				if (Queue[QueueFront].LeftSheep == 0 && Queue[QueueFront].LeftWolf == 0)
				{
					printf("%d\n", Queue[QueueFront].Step);
					break;
				}

				LorR = Queue[QueueFront].Step % 2;
				if (LorR == 0)/*如果在原地*/
				{
					for (BringSheep = 0;BringSheep <= n&&BringSheep <= Queue[QueueFront].LeftSheep;BringSheep++)
					{
						for (BringWolf = 0;BringWolf <= n&&BringWolf <= Queue[QueueFront].LeftWolf;BringWolf++)
						{
							if (BringSheep == 0 && BringWolf == 0)
							{
								continue;
							}
							if (BringSheep < BringWolf)
							{
								if (BringSheep > 0)
								{
									break;
								}
							}
							if (BringSheep + BringWolf > n)
							{
								break;
							}

							if (Queue[QueueFront].LeftSheep - BringSheep >= Queue[QueueFront].LeftWolf - BringWolf)
							{
								if (Queue[QueueFront].RightSheep + BringSheep >= Queue[QueueFront].RightWolf + BringWolf)
								{
									if (Visit[1][Queue[QueueFront].RightSheep + BringSheep][Queue[QueueFront].RightWolf + BringWolf] == 0)
									{
										Queue[QueueRear].LeftSheep = Queue[QueueFront].LeftSheep - BringSheep;
										Queue[QueueRear].LeftWolf = Queue[QueueFront].LeftWolf - BringWolf;
										Queue[QueueRear].RightSheep = Queue[QueueFront].RightSheep + BringSheep;
										Queue[QueueRear].RightWolf = Queue[QueueFront].RightWolf + BringWolf;
										Queue[QueueRear].Step = Queue[QueueFront].Step + 1;
										QueueRear++;
										Visit[1][Queue[QueueFront].RightSheep + BringSheep][Queue[QueueFront].RightWolf + BringWolf] = 1;
									}
									else
									{
										continue;
									}
								}
								else
								{
									if (Queue[QueueFront].RightSheep + BringSheep == 0)
									{
										if (Visit[1][Queue[QueueFront].RightSheep + BringSheep][Queue[QueueFront].RightWolf + BringWolf] == 0)
										{
											Queue[QueueRear].LeftSheep = Queue[QueueFront].LeftSheep - BringSheep;
											Queue[QueueRear].LeftWolf = Queue[QueueFront].LeftWolf - BringWolf;
											Queue[QueueRear].RightSheep = Queue[QueueFront].RightSheep + BringSheep;
											Queue[QueueRear].RightWolf = Queue[QueueFront].RightWolf + BringWolf;
											Queue[QueueRear].Step = Queue[QueueFront].Step + 1;
											QueueRear++;
											Visit[1][Queue[QueueFront].RightSheep + BringSheep][Queue[QueueFront].RightWolf + BringWolf] = 1;
										}
										else
										{
											continue;
										}
									}
									else
									{
										continue;
									}
								}
							}
							else
							{
								if (Queue[QueueFront].LeftSheep - BringSheep == 0)
								{
									if (Queue[QueueFront].RightSheep + BringSheep >= Queue[QueueFront].RightWolf + BringWolf)
									{
										if (Visit[1][Queue[QueueFront].RightSheep + BringSheep][Queue[QueueFront].RightWolf + BringWolf] == 0)
										{
											Queue[QueueRear].LeftSheep = Queue[QueueFront].LeftSheep - BringSheep;
											Queue[QueueRear].LeftWolf = Queue[QueueFront].LeftWolf - BringWolf;
											Queue[QueueRear].RightSheep = Queue[QueueFront].RightSheep + BringSheep;
											Queue[QueueRear].RightWolf = Queue[QueueFront].RightWolf + BringWolf;
											Queue[QueueRear].Step = Queue[QueueFront].Step + 1;
											QueueRear++;
											Visit[1][Queue[QueueFront].RightSheep + BringSheep][Queue[QueueFront].RightWolf + BringWolf] = 1;
										}
										else
										{
											continue;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
						}
					}
				}
				else/*如果在对岸*/
				{
					for (BringSheep = 0;BringSheep <= n&&BringSheep <= Queue[QueueFront].RightSheep;BringSheep++)
					{
						for (BringWolf = 0;BringWolf <= n&&BringWolf <= Queue[QueueFront].RightWolf;BringWolf++)
						{
							if (BringSheep == 0 && BringWolf == 0)
							{
								continue;
							}
							if (BringSheep < BringWolf)
							{
								if (BringSheep > 0)
								{
									break;
								}
							}
							if (BringSheep + BringWolf > n)
							{
								break;
							}

							if (Queue[QueueFront].RightSheep - BringSheep >= Queue[QueueFront].RightWolf - BringWolf)
							{
								if (Queue[QueueFront].LeftSheep + BringSheep >= Queue[QueueFront].LeftWolf + BringWolf)
								{
									if (Visit[0][Queue[QueueFront].LeftSheep + BringSheep][Queue[QueueFront].LeftWolf + BringWolf] == 0)
									{
										Queue[QueueRear].LeftSheep = Queue[QueueFront].LeftSheep + BringSheep;
										Queue[QueueRear].LeftWolf = Queue[QueueFront].LeftWolf + BringWolf;
										Queue[QueueRear].RightSheep = Queue[QueueFront].RightSheep - BringSheep;
										Queue[QueueRear].RightWolf = Queue[QueueFront].RightWolf - BringWolf;
										Queue[QueueRear].Step = Queue[QueueFront].Step + 1;
										QueueRear++;
										Visit[0][Queue[QueueFront].LeftSheep + BringSheep][Queue[QueueFront].LeftWolf + BringWolf] = 1;
									}
									else
									{
										continue;
									}
								}
								else
								{
									if (Queue[QueueFront].LeftSheep + BringSheep == 0)
									{
										if (Visit[0][Queue[QueueFront].LeftSheep + BringSheep][Queue[QueueFront].LeftWolf + BringWolf] == 0)
										{
											Queue[QueueRear].LeftSheep = Queue[QueueFront].LeftSheep + BringSheep;
											Queue[QueueRear].LeftWolf = Queue[QueueFront].LeftWolf + BringWolf;
											Queue[QueueRear].RightSheep = Queue[QueueFront].RightSheep - BringSheep;
											Queue[QueueRear].RightWolf = Queue[QueueFront].RightWolf - BringWolf;
											Queue[QueueRear].Step = Queue[QueueFront].Step + 1;
											QueueRear++;
											Visit[0][Queue[QueueFront].LeftSheep + BringSheep][Queue[QueueFront].LeftWolf + BringWolf] = 1;
										}
										else
										{
											continue;
										}
									}
									else
									{
										continue;
									}
								}
							}
							else
							{
								if (Queue[QueueFront].RightSheep - BringSheep == 0)
								{
									if (Queue[QueueFront].LeftSheep + BringSheep >= Queue[QueueFront].LeftWolf + BringWolf)
									{
										if (Visit[0][Queue[QueueFront].LeftSheep + BringSheep][Queue[QueueFront].LeftWolf + BringWolf] == 0)
										{
											Queue[QueueRear].LeftSheep = Queue[QueueFront].LeftSheep + BringSheep;
											Queue[QueueRear].LeftWolf = Queue[QueueFront].LeftWolf + BringWolf;
											Queue[QueueRear].RightSheep = Queue[QueueFront].RightSheep - BringSheep;
											Queue[QueueRear].RightWolf = Queue[QueueFront].RightWolf - BringWolf;
											Queue[QueueRear].Step = Queue[QueueFront].Step + 1;
											QueueRear++;
											Visit[0][Queue[QueueFront].LeftSheep + BringSheep][Queue[QueueFront].LeftWolf + BringWolf] = 1;
										}
										else
										{
											continue;
										}
									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}
						}
					}
				}
			}
		}

		G--;
	}
}