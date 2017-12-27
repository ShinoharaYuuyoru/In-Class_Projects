#include "stdio.h"
#include "stdlib.h"

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef int LONG;

/*#pragma pack(1) 下次再用用玩玩*/
BYTE bfType[2];
typedef struct tagHEAD
{
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
	DWORD bfEND;

	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCout;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXpelsPerMeter;
	LONG biYpelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}HEAD;

typedef struct tagCOLOR
{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
}COLOR;

struct Q
{
	short x, y;
}queue[63000];


FILE* BMP = NULL;
HEAD NEW;
COLOR NEWCOLOR[260][260];

void opI();
void opG();
void opC();
void opL();
void opV();
void opH();
void opK();
void opF();
void opS();
void opFBFS(int X, int Y, int C);

int main()
{
	char First;/*用于确定操作*/

	while (1)
	{
		scanf("%c", &First);
		if (First == '\n')
		{
			continue;
		}
		if (First == 'I')
		{
			/*Reset Head*/
			bfType[0] = 'B';
			bfType[1] = 'M';
			NEW.bfSize = 0x00;
			NEW.bfReserved1 = 0x00;
			NEW.bfReserved2 = 0x00;
			NEW.bfOffBits = 0x36;
			NEW.bfEND = 0x28;

			NEW.biWidth = 0x00;
			NEW.biHeight = 0x00;
			NEW.biPlanes = 0x1;
			NEW.biBitCout = 0x18;
			NEW.biCompression; 0x00;
			NEW.biSizeImage = 0x00;
			NEW.biXpelsPerMeter = 0x0B13;
			NEW.biYpelsPerMeter = 0x0B13;
			NEW.biClrUsed = 0x00;
			NEW.biClrImportant = 0x00;
			/*Reset Head End*/

			getchar();/*Delete Space*/
			opI();
		}
		if (First == 'G')
		{
			getchar();
			opG();
		}
		if (First == 'C')
		{
			getchar();
			opC();
		}
		if (First == 'L')
		{
			getchar();
			opL();
		}
		if (First == 'V')
		{
			getchar();
			opV();
		}
		if (First == 'H')
		{
			getchar();
			opH();
		}
		if (First == 'K')
		{
			getchar();
			opK();
		}
		if (First == 'F')
		{
			getchar();
			opF();
		}
		if (First == 'S')
		{
			getchar();
			opS();
		}
		if (First == 'X')
		{
			return 0;
		}
	}
}

void opI()
{
	scanf("%d", &NEW.biWidth);
	scanf("%d", &NEW.biHeight);

	int Wcount, Hcount;

	for (Hcount = 0; Hcount < NEW.biHeight; Hcount++)
	{
		for (Wcount = 0; Wcount < NEW.biWidth; Wcount++)
		{
			NEWCOLOR[Hcount][Wcount].rgbBlue = 0xFF;
			NEWCOLOR[Hcount][Wcount].rgbGreen = 0xFF;
			NEWCOLOR[Hcount][Wcount].rgbRed = 0xFF;
		}
	}
}
void opG()
{
	int x, y;
	scanf("%d%d", &x, &y);
	x--;
	y--;
	int col;/*int Color*/
	scanf("%x", &col);

	NEWCOLOR[y][x].rgbBlue = col & 0xFF;
	NEWCOLOR[y][x].rgbGreen = (col >> 8) & 0xFF;
	NEWCOLOR[y][x].rgbRed = (col >> 16) & 0xFF;
}
void opC()
{
	int Wcount, Hcount;

	for (Hcount = 0; Hcount < NEW.biHeight; Hcount++)
	{
		for (Wcount = 0; Wcount < NEW.biWidth; Wcount++)
		{
			NEWCOLOR[Hcount][Wcount].rgbBlue = 0xFF;
			NEWCOLOR[Hcount][Wcount].rgbGreen = 0xFF;
			NEWCOLOR[Hcount][Wcount].rgbRed = 0xFF;
		}
	}
}
void opL()
{
	int x, y;
	scanf("%d%d", &x, &y);
	x--;
	y--;
	int col;/*int Color*/
	scanf("%x", &col);

	NEWCOLOR[y][x].rgbBlue = col & 0xFF;
	NEWCOLOR[y][x].rgbGreen = (col >> 8) & 0xFF;
	NEWCOLOR[y][x].rgbRed = (col >> 16) & 0xFF;
}
void opV()
{
	int x;
	int y1, y2;
	int ycount;
	int col;

	scanf("%d%d%d%x", &x, &y1, &y2, &col);
	x--;
	y1--;
	y2--;

	for (ycount = y1; ycount <= y2; ycount++)
	{
		NEWCOLOR[ycount][x].rgbBlue = col & 0xFF;
		NEWCOLOR[ycount][x].rgbGreen = (col >> 8) & 0xFF;
		NEWCOLOR[ycount][x].rgbRed = (col >> 16) & 0xFF;
	}
}
void opH()
{
	int x1, x2;
	int y;
	int xcount;
	int col;

	scanf("%d%d%d%x", &x1, &x2, &y, &col);
	x1--;
	x2--;
	y--;

	for (xcount = x1; xcount <= x2; xcount++)
	{
		NEWCOLOR[y][xcount].rgbBlue = col & 0xFF;
		NEWCOLOR[y][xcount].rgbGreen = (col >> 8) & 0xFF;
		NEWCOLOR[y][xcount].rgbRed = (col >> 16) & 0xFF;
	}
}
void opK()
{
	int x1, x2;
	int y1, y2;
	int xcount, ycount;
	int col;

	scanf("%d%d%d%d%x", &x1, &y1, &x2, &y2, &col);
	x1--;
	y1--;
	x2--;
	y2--;

	if (y1 <= y2)
	{
		if (x1 <= x2)/*左上角到右下角*/
		{
			for (ycount = y1; ycount <= y2; ycount++)
			{
				for (xcount = x1; xcount <= x2; xcount++)
				{
					NEWCOLOR[ycount][xcount].rgbBlue = col & 0xFF;
					NEWCOLOR[ycount][xcount].rgbGreen = (col >> 8) & 0xFF;
					NEWCOLOR[ycount][xcount].rgbRed = (col >> 16) & 0xFF;
				}
			}
		}
		else/*右上角到右下角*/
		{
			for (ycount = y1; ycount <= y2; ycount++)
			{
				for (xcount = x2; xcount <= x1; xcount++)
				{
					NEWCOLOR[ycount][xcount].rgbBlue = col & 0xFF;
					NEWCOLOR[ycount][xcount].rgbGreen = (col >> 8) & 0xFF;
					NEWCOLOR[ycount][xcount].rgbRed = (col >> 16) & 0xFF;
				}
			}
		}
	}
	else
	{
		if (x1 <= x2)/*左下角到右上角*/
		{
			for (ycount = y2; ycount <= y1; ycount++)
			{
				for (xcount = x1; xcount <= x2; xcount++)
				{
					NEWCOLOR[ycount][xcount].rgbBlue = col & 0xFF;
					NEWCOLOR[ycount][xcount].rgbGreen = (col >> 8) & 0xFF;
					NEWCOLOR[ycount][xcount].rgbRed = (col >> 16) & 0xFF;
				}
			}
		}
		else/*右下角到左上角*/
		{
			for (ycount = y2; ycount <= y1; ycount++)
			{
				for (xcount = x2; xcount <= x1; xcount++)
				{
					NEWCOLOR[ycount][xcount].rgbBlue = col & 0xFF;
					NEWCOLOR[ycount][xcount].rgbGreen = (col >> 8) & 0xFF;
					NEWCOLOR[ycount][xcount].rgbRed = (col >> 16) & 0xFF;
				}
			}
		}
	}
}
void opF()
{
	int x;
	int y;
	int col;
	scanf("%d%d%x", &x, &y, &col);
	x--;
	y--;

	opFBFS(x, y, col);
}
void opS()
{
	int Wcount, Hcount;
	char NAME[20];
	scanf("%s", NAME);

	if ((NEW.biWidth * 3) % 4 == 0)
	{
		NEW.biSizeImage = (NEW.biWidth*NEW.biHeight) * 3;
		NEW.bfSize = NEW.biSizeImage + 54;
	}
	else
	{
		NEW.biSizeImage = (NEW.biWidth*NEW.biHeight) * 3 + (4 - ((NEW.biWidth * 3) % 4))*NEW.biHeight;
		NEW.bfSize = NEW.biSizeImage + 54;
	}

	BMP = fopen(NAME, "wb");
	fwrite(bfType, sizeof(bfType), 1, BMP);
	fwrite(&NEW, sizeof(NEW), 1, BMP);

	for (Hcount = NEW.biHeight - 1; Hcount >= 0; Hcount--)
	{
		for (Wcount = 0; Wcount<NEW.biWidth; Wcount++)
		{
			fwrite(&NEWCOLOR[Hcount][Wcount], sizeof(NEWCOLOR[Hcount][Wcount]), 1, BMP);
		}

		if ((NEW.biWidth * 3) % 4 != 0)
		{
			int Reserve0 = 4 - ((NEW.biWidth * 3) % 4);
			int Rec;
			BYTE ZERO = 0x00;

			for (Rec = 1; Rec <= Reserve0; Rec++)
			{
				fwrite(&ZERO, sizeof(BYTE), 1, BMP);
			}
		}
	}

	fclose(BMP);
}
void opFBFS(int X,int Y,int C)
{
	int queueFront = 0;
	int queueRear = 0;

	int OriBlue, OriGreen, OriRed;

	OriBlue = NEWCOLOR[Y][X].rgbBlue;
	OriGreen = NEWCOLOR[Y][X].rgbGreen;
	OriRed = NEWCOLOR[Y][X].rgbRed;

	queue[queueRear].x = X;
	queue[queueRear].y = Y;
	queueRear++;

	for (; queueFront < queueRear; queueFront++)
	{
		if (queue[queueFront].x + 1 < NEW.biWidth)
		{
			if (NEWCOLOR[queue[queueFront].y][queue[queueFront].x + 1].rgbBlue == OriBlue&&NEWCOLOR[queue[queueFront].y][queue[queueFront].x + 1].rgbGreen == OriGreen&&NEWCOLOR[queue[queueFront].y][queue[queueFront].x + 1].rgbRed == OriRed)
			{
				queue[queueRear].x = queue[queueFront].x + 1;
				queue[queueRear].y = queue[queueFront].y;
				queueRear++;
			}
		}
		if (queue[queueFront].x - 1 >= 0)
		{
			if (NEWCOLOR[queue[queueFront].y][queue[queueFront].x - 1].rgbBlue == OriBlue&&NEWCOLOR[queue[queueFront].y][queue[queueFront].x - 1].rgbGreen == OriGreen&&NEWCOLOR[queue[queueFront].y][queue[queueFront].x - 1].rgbRed == OriRed)
			{
				queue[queueRear].x = queue[queueFront].x - 1;
				queue[queueRear].y = queue[queueFront].y;
				queueRear++;
			}
		}
		if (queue[queueFront].y + 1 < NEW.biHeight)
		{
			if (NEWCOLOR[queue[queueFront].y + 1][queue[queueFront].x].rgbBlue == OriBlue&&NEWCOLOR[queue[queueFront].y + 1][queue[queueFront].x].rgbGreen == OriGreen&&NEWCOLOR[queue[queueFront].y + 1][queue[queueFront].x].rgbRed == OriRed)
			{
				queue[queueRear].x = queue[queueFront].x;
				queue[queueRear].y = queue[queueFront].y + 1;
				queueRear++;
			}
		}
		if (queue[queueFront].y - 1 >= 0)
		{
			if (NEWCOLOR[queue[queueFront].y - 1][queue[queueFront].x].rgbBlue == OriBlue&&NEWCOLOR[queue[queueFront].y - 1][queue[queueFront].x].rgbGreen == OriGreen&&NEWCOLOR[queue[queueFront].y - 1][queue[queueFront].x].rgbRed == OriRed)
			{
				queue[queueRear].x = queue[queueFront].x;
				queue[queueRear].y = queue[queueFront].y - 1;
				queueRear++;
			}
		}

		NEWCOLOR[queue[queueFront].y][queue[queueFront].x].rgbBlue = C & 0xFF;
		NEWCOLOR[queue[queueFront].y][queue[queueFront].x].rgbGreen = (C >> 8) & 0xFF;
		NEWCOLOR[queue[queueFront].y][queue[queueFront].x].rgbRed = (C >> 16) & 0xFF;
	}
}