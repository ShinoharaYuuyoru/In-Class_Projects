#include "stdio.h"
#include "string.h"
#include "math.h"

unsigned int Moji[65536] = { 0 };/*下标即为Unicode代码对应的十进制数 值为重复次数*/

char chBina[10];
char extrach2Bina[10];
char extrach3Bina[10];

int Dec(char* str);
void itoa(int N, char *s);//缩水版itoa 用于十转二

int main()
{
	unsigned char ch;/*第一个字节（头字节）*/
	unsigned char ch2, ch3;/*第二第三个字节*/
	int onesearch, onenum;/*搜索ch二进制里的1*/
	char AllBina[26];/*整个字符二进制表示*/
	char UniBina[18];/*Unicode码对应的二进制码*/
	int UniBinax,UniBinay;/*x：转Unicode二进制时搜索UTF-8二进制 y：记录Unicode二进制*/
	int endsearch;/*最终搜索*/
	char UTFTEMP[26];/*Unicode转UTF-8 未补0*/
	int pl;/*补0数量*/
	char UTF[26];/*Unicode转UTF-8 完整*/
	int UTFmove;/*用于Unicode转UTF-8移位*/
	int move;/*用于确定需要移位个数*/
	char Chi[3][10];/*拆分UTF*/
	int ANS[3];/*最终汉字！！！！！*/
	int flag = 0;

	//int feff = 0;/*临时！！！！用于检测feff*/

	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	while (1)
	{
		ch = getchar();
		if (ch == 255)/*EOF*/
		{
			break;
		}
		else
		{
			if (ch <= 127)
			{
				continue;
			}
			else
			{
				itoa(ch, chBina);/*记住这个函数！！！！！！！*/

				for (onesearch = 0, onenum = 0; chBina[onesearch] != '0'; onesearch++)/*判断后续需要几个字节*//*最后需要Reset chBina*/
				{
					if (chBina[onesearch] == '1')
					{
						onenum++;
					}
				}
				if (onenum == 2)/*再需要一个字节*/
				{
					ch2 = getchar();
					itoa(ch2, extrach2Bina);
					strcpy(AllBina, chBina);
					strcat(AllBina, extrach2Bina);/*AllBina便是二字节字符的全部二进制（UTF-8）表示*/

					/*接下来进行UTF-8转Unicode*/
					for (UniBinax = 3, UniBinay = 0; UniBinax <= 15; UniBinax++)
					{
						if (UniBinax == 8 || UniBinax == 9)
						{
							continue;
						}
						else
						{
							UniBina[UniBinay] = AllBina[UniBinax];
							UniBinay++;
						}
					}
					UniBina[UniBinay] = '\0';

					Moji[Dec(UniBina)]++;/*记录数+1*/
				}
				if (onenum == 3)/*再需要两个字节*/
				{
					//if (feff == 0)
					//{
					//	ch2 = getchar();
					//	ch3 = getchar();
					//	feff = 1;
					//	continue;
					//}
					ch2 = getchar();
					ch3 = getchar();
					itoa(ch2, extrach2Bina);
					itoa(ch3, extrach3Bina);
					strcpy(AllBina, chBina);
					strcat(AllBina, extrach2Bina);
					strcat(AllBina, extrach3Bina);

					/*接下来进行UTF-8转Unicode*/
					for (UniBinax = 4, UniBinay = 0; UniBinax <= 23; UniBinax++)
					{
						if (UniBinax == 8 || UniBinax == 9 || UniBinax == 16 || UniBinax == 17)
						{
							continue;
						}
						else
						{
							UniBina[UniBinay] = AllBina[UniBinax];
							UniBinay++;
						}
					}
					UniBina[UniBinay] = '\0';
					Moji[Dec(UniBina)]++;/*记录数+1*/
				}
			}
		}
	}

	for (endsearch = 0; endsearch < 65536; endsearch++)
	{
		if (Moji[endsearch] >= 2)
		{
			flag = 1;/*有重复记录*/
			itoa(endsearch, UTFTEMP);
			/*Unicode转UTF-8*/
			if (endsearch <= 2047)/*如果是2字节*/
			{
				for (UTFmove = 0; UTFTEMP[UTFmove] != '\0'; UTFmove++);
				/*需要补0*/
				if (UTFmove < 11)
				{
					pl = 11 - UTFmove;/*补0数量*/
					for (UTF[pl] = '\0'; pl > 0; pl--)
					{
						UTF[pl - 1] = '0';
					}
				}
				strcat(UTF, UTFTEMP);
				UTFmove = 11;

				/*后6+1位移5个，前5位移3个*/
				for (move = 7; move >= 1; move--)
				{
					UTF[UTFmove + 5] = UTF[UTFmove];
					UTFmove--;
				}
				for (move = 5; move >= 1; move--)
				{
					UTF[UTFmove + 3] = UTF[UTFmove];
					UTFmove--;
				}
				UTF[0] = '1';
				UTF[1] = '1';
				UTF[2] = '0';
				UTF[8] = '1';
				UTF[9] = '0';
				
				for (move = 0; move <= 7; move++)
				{
					Chi[0][move] = UTF[move];
				}
				Chi[0][move] = '\0';
				ANS[0] = Dec(Chi[0]);
				for (; move <= 16; move++)
				{
					Chi[1][move - 8] = UTF[move];
				}
				ANS[1] = Dec(Chi[1]);

				printf("%c%c 0x%04x %d\n", ANS[0], ANS[1], endsearch, Moji[endsearch]);
				UTF[0] = '\0';
			}
			else/*如果是3字节*/
			{
				for (UTFmove = 0; UTFTEMP[UTFmove] != '\0'; UTFmove++);
				/*需要补0*/
				if (UTFmove < 16)
				{
					pl = 16 - UTFmove;/*补0数量*/
					for (UTF[pl] = '\0'; pl > 0; pl--)
					{
						UTF[pl - 1] = '0';
					}
				}
				strcat(UTF, UTFTEMP);
				UTFmove = 16;

				/*后6+1位移8个，中6位移6个，前4位移4个*/
				for (move = 7; move >= 1; move--)
				{
					UTF[UTFmove + 8] = UTF[UTFmove];
					UTFmove--;
				}
				for (move = 6; move >= 1; move--)
				{
					UTF[UTFmove + 6] = UTF[UTFmove];
					UTFmove--;
				}
				for (move = 4; move >= 1; move--)
				{
					UTF[UTFmove + 4] = UTF[UTFmove];
					UTFmove--;
				}
				UTF[0] = '1';
				UTF[1] = '1';
				UTF[2] = '1';
				UTF[3] = '0';
				UTF[8] = '1';
				UTF[9] = '0';
				UTF[16] = '1';
				UTF[17] = '0';

				for (move = 0; move <= 7; move++)
				{
					Chi[0][move] = UTF[move];
				}
				Chi[0][move] = '\0';
				ANS[0] = Dec(Chi[0]);
				for (; move <= 15; move++)
				{
					Chi[1][move - 8] = UTF[move];
				}
				Chi[1][move - 8] = '\0';
				ANS[1] = Dec(Chi[1]);
				for (; move <= 24; move++)
				{
					Chi[2][move - 16] = UTF[move];
				}
				ANS[2] = Dec(Chi[2]);

				printf("%c%c%c 0x%04x %d\n", ANS[0], ANS[1], ANS[2], endsearch, Moji[endsearch]);
				UTF[0] = '\0';
			}
		}
	}
	if (flag == 0)
	{
		printf("No repeat!\n");
	}
	return 0;
}

int Dec(char* str)/*二进制转成十进制数*/
{
	int num;
	int x, y;/*x：计数 y：用于2的乘方计算*/
	int temp;
	int ans = 0;

	num = strlen(str);

	for (x = num-1, y = 0; x >= 0; x--, y++)
	{
		temp = pow(2.0, y)*(str[x] - 48);
		ans = ans + temp;
	}
	return ans;
}

void itoa(int N, char *s)//缩水版itoa 用于十转二
{
	int x;
	for (x = 0; N != 0; x++)
	{
		s[x] = (N % 2 + 48);
		N = N / 2;
	}
	s[x] = '\0';
	x--;
	int y;
	char t;/*temp*/
	for (y = 0; x > y;)
	{
		t = s[y];
		s[y] = s[x];
		s[x] = t;
		x--;
		y++;
	}
	return;
}