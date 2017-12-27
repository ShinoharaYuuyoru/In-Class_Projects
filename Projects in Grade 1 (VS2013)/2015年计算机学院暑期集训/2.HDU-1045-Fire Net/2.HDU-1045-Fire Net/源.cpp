#include "stdio.h"

int CanSet(int y, int x);
void Sign(int y, int x);

char MAP[6][6];
int MathMAP[6][6];
bool BOOLMAP[6][6] = { false };
int Castle;
int REZ = 0;

int main()
{
	int Xc, Yc;
	int Queue[20][3];

	char temp;
	int Queuec = 0;//Queue count.
	int Queuecc;//Using for queuing.
	int Queueend = 1;
	int save0, save1, save2;

	for (;;)
	{
		scanf("%d", &Castle);

		if (Castle == 0)
		{
			return 0;
		}
		else
		{
			for (Yc = 0; Yc < 6; Yc++)//Reset.
			{
				for (Xc = 0; Xc < 6; Xc++)
				{
					MAP[Yc][Xc] = '\0';
					MathMAP[Yc][Xc] = 0;
					BOOLMAP[Yc][Xc] = false;
				}
			}
			for (Queuec = 0; Queuec < 20; Queuec++)
			{
				Queue[Queuec][0] = 0;
				Queue[Queuec][1] = 0;
				Queue[Queuec][2] = 0;
			}

			for (Yc = 1; Yc <= Castle; Yc++)
			{
				for (Xc = 1; Xc <= Castle; Xc++)
				{
					scanf("%c", &temp);
					if (temp == '\n')
					{
						Xc--;
						continue;
					}
					else
					{
						MAP[Yc][Xc] = temp;
					}
				}
			}
		}

		for (Yc = 1; Yc <= Castle; Yc++)//Sign.
		{
			for (Xc = 1; Xc <= Castle; Xc++)
			{
				MathMAP[Yc][Xc] = CanSet(Yc, Xc);
			}
		}

		Queuec = 0;

		for (Yc = 1; Yc <= Castle; Yc++)
		{
			for (Xc = 1; Xc <= Castle; Xc++)
			{
				if (MathMAP[Yc][Xc] == 0)
				{
					continue;
				}
				else
				{
					Queue[Queuec][0] = MathMAP[Yc][Xc];
					Queue[Queuec][1] = Yc;
					Queue[Queuec][2] = Xc;
					Queuec++;
				}
			}
		}

		Queue[Queuec][0] = 999;//Ending Sign.

		Queueend = 1;
		
		for (Queuec = 0; Queue[Queuec + 1][0] != 999 && Queue[Queuec][0] != 999; Queuec++)
		{
			for (Queuecc = 0; Queue[Queuecc + Queueend][0] != 999; Queuecc++)
			{
				if (Queue[Queuecc][0] > Queue[Queuecc + 1][0])
				{
					save0 = Queue[Queuecc + 1][0];
					save1 = Queue[Queuecc + 1][1];
					save2 = Queue[Queuecc + 1][2];

					Queue[Queuecc + 1][0] = Queue[Queuecc][0];
					Queue[Queuecc + 1][1] = Queue[Queuecc][1];
					Queue[Queuecc + 1][2] = Queue[Queuecc][2];

					Queue[Queuecc][0] = save0;
					Queue[Queuecc][1] = save1;
					Queue[Queuecc][2] = save2;
				}
			}
			Queueend++;
		}

		REZ = 0;

		for (Queuec = 0; Queue[Queuec][0] != 999; Queuec++)
		{
			Sign(Queue[Queuec][1], Queue[Queuec][2]);
		}

		printf("%d\n", REZ);
	}
}

int CanSet(int y, int x)
{
	int set;
	int yc, xc;

	if (MAP[y][x] == '.')
	{
		set = 1;
	}
	else
	{
		set = 0;
		return 0;
	}

	for (yc = y - 1; yc > 0; yc--)
	{
		if (MAP[yc][x] == '.')
		{
			set++;
		}
		if (MAP[yc][x] == 'X')
		{
			break;
		}
	}

	for (yc = y + 1; yc <= Castle; yc++)
	{
		if (MAP[yc][x] == '.')
		{
			set++;
		}
		if (MAP[yc][x] == 'X')
		{
			break;
		}
	}

	for (xc = x - 1; xc > 0; xc--)
	{
		if (MAP[y][xc] == '.')
		{
			set++;
		}
		if (MAP[y][xc] == 'X')
		{
			break;
		}
	}

	for (xc = x + 1; xc <= Castle; xc++)
	{
		if (MAP[y][xc] == '.')
		{
			set++;
		}
		if (MAP[y][xc] == 'X')
		{
			break;
		}
	}
	
	return set;
}

void Sign(int y, int x)
{
	int yc, xc;

	if (BOOLMAP[y][x] == true)
	{
		return;
	}
	else
	{
		BOOLMAP[y][x] = true;

		REZ++;

		for (yc = y - 1; yc > 0; yc--)
		{
			if (MAP[yc][x] == '.')
			{
				BOOLMAP[yc][x] = true;
			}
			if (MAP[yc][x] == 'X')
			{
				break;
			}
		}

		for (yc = y + 1; yc <= Castle; yc++)
		{
			if (MAP[yc][x] == '.')
			{
				BOOLMAP[yc][x] = true;
			}
			if (MAP[yc][x] == 'X')
			{
				break;
			}
		}

		for (xc = x - 1; xc > 0; xc--)
		{
			if (MAP[y][xc] == '.')
			{
				BOOLMAP[y][xc] = true;
			}
			if (MAP[y][xc] == 'X')
			{
				break;
			}
		}

		for (xc = x + 1; xc <= Castle; xc++)
		{
			if (MAP[y][xc] == '.')
			{
				BOOLMAP[y][xc] = true;
			}
			if (MAP[y][xc] == 'X')
			{
				break;
			}
		}
	}
}