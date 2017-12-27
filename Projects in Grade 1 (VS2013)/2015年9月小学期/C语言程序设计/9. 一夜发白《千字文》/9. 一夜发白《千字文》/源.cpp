#include "stdio.h"
#include "string.h"
#include "math.h"

unsigned int Moji[65536] = { 0 };/*�±꼴ΪUnicode�����Ӧ��ʮ������ ֵΪ�ظ�����*/

char chBina[10];
char extrach2Bina[10];
char extrach3Bina[10];

int Dec(char* str);
void itoa(int N, char *s);//��ˮ��itoa ����ʮת��

int main()
{
	unsigned char ch;/*��һ���ֽڣ�ͷ�ֽڣ�*/
	unsigned char ch2, ch3;/*�ڶ��������ֽ�*/
	int onesearch, onenum;/*����ch���������1*/
	char AllBina[26];/*�����ַ������Ʊ�ʾ*/
	char UniBina[18];/*Unicode���Ӧ�Ķ�������*/
	int UniBinax,UniBinay;/*x��תUnicode������ʱ����UTF-8������ y����¼Unicode������*/
	int endsearch;/*��������*/
	char UTFTEMP[26];/*UnicodeתUTF-8 δ��0*/
	int pl;/*��0����*/
	char UTF[26];/*UnicodeתUTF-8 ����*/
	int UTFmove;/*����UnicodeתUTF-8��λ*/
	int move;/*����ȷ����Ҫ��λ����*/
	char Chi[3][10];/*���UTF*/
	int ANS[3];/*���պ��֣���������*/
	int flag = 0;

	//int feff = 0;/*��ʱ�����������ڼ��feff*/

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
				itoa(ch, chBina);/*��ס���������������������*/

				for (onesearch = 0, onenum = 0; chBina[onesearch] != '0'; onesearch++)/*�жϺ�����Ҫ�����ֽ�*//*�����ҪReset chBina*/
				{
					if (chBina[onesearch] == '1')
					{
						onenum++;
					}
				}
				if (onenum == 2)/*����Ҫһ���ֽ�*/
				{
					ch2 = getchar();
					itoa(ch2, extrach2Bina);
					strcpy(AllBina, chBina);
					strcat(AllBina, extrach2Bina);/*AllBina���Ƕ��ֽ��ַ���ȫ�������ƣ�UTF-8����ʾ*/

					/*����������UTF-8תUnicode*/
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

					Moji[Dec(UniBina)]++;/*��¼��+1*/
				}
				if (onenum == 3)/*����Ҫ�����ֽ�*/
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

					/*����������UTF-8תUnicode*/
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
					Moji[Dec(UniBina)]++;/*��¼��+1*/
				}
			}
		}
	}

	for (endsearch = 0; endsearch < 65536; endsearch++)
	{
		if (Moji[endsearch] >= 2)
		{
			flag = 1;/*���ظ���¼*/
			itoa(endsearch, UTFTEMP);
			/*UnicodeתUTF-8*/
			if (endsearch <= 2047)/*�����2�ֽ�*/
			{
				for (UTFmove = 0; UTFTEMP[UTFmove] != '\0'; UTFmove++);
				/*��Ҫ��0*/
				if (UTFmove < 11)
				{
					pl = 11 - UTFmove;/*��0����*/
					for (UTF[pl] = '\0'; pl > 0; pl--)
					{
						UTF[pl - 1] = '0';
					}
				}
				strcat(UTF, UTFTEMP);
				UTFmove = 11;

				/*��6+1λ��5����ǰ5λ��3��*/
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
			else/*�����3�ֽ�*/
			{
				for (UTFmove = 0; UTFTEMP[UTFmove] != '\0'; UTFmove++);
				/*��Ҫ��0*/
				if (UTFmove < 16)
				{
					pl = 16 - UTFmove;/*��0����*/
					for (UTF[pl] = '\0'; pl > 0; pl--)
					{
						UTF[pl - 1] = '0';
					}
				}
				strcat(UTF, UTFTEMP);
				UTFmove = 16;

				/*��6+1λ��8������6λ��6����ǰ4λ��4��*/
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

int Dec(char* str)/*������ת��ʮ������*/
{
	int num;
	int x, y;/*x������ y������2�ĳ˷�����*/
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

void itoa(int N, char *s)//��ˮ��itoa ����ʮת��
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