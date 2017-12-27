#include "stdio.h"

int ANShave = 0;

void MUL(int n, int *ar);
void MINUS(int *big, int *small, int *ans);
void GO(int *ar);

int main()
{
	int a10[1500] = { 0 };
	int a9[1500] = { 0 };
	int ahave9[1500] = { 0 };
	int b10[1500] = { 0 };
	int b9[1500] = { 0 };
	int bhave9[1500] = { 0 };
	int ANS[1500] = { 0 };
	int Reset = 0;/*Reset专用*/
	int ifhave9 = 0;/*看最高位是否出现了9*/
	int iffirst = 0;/*看是否是第一位是9*/
	int ifplus = 0;/*检测到有9出现，那么这个9应该被输入，下一个开始不输入*/
	int T;/*数据组数*/
	int ANSprint = 0;/*仅用于输出*/
	char ch;/*读位*/

	scanf("%d", &T);
	getchar();/*取消T后的\n*/

	while (T >= 1)
	{
		/*Reset*/
		for (Reset = 0; Reset < 1500; Reset++)
		{
			a10[Reset] = -1;
			a9[Reset] = -1;
			ahave9[Reset] = -1;
			b10[Reset] = -1;
			b9[Reset] = -1;
			bhave9[Reset] = -1;
			ANS[Reset] = -1;
		}
		ifhave9 = 0;
		ANShave = 0;
		ANSprint = 0;

		ifplus = 0;
		iffirst = 1;/*看是否是第一位*/
		for (;;)/*录入A*/
		{
			ch = getchar();/*输入*/
			if (ch == ' ')
			{
				break;
			}

			if (ch == '9'&&ifhave9 == 0)/*搜索到第一个9*/
			{
				ifhave9 = 1;
			}
			if (iffirst == 1)
			{
				if (ch == '9')
				{
					ifplus = 1;
				}
				a10[0] = ch - 48;
				a9[0] = ch - 48;
				ahave9[0] = 0;
				iffirst = 0;
				continue;
			}

			MUL(10, a10);
			a10[0] = a10[0] + ch - 48;
			if (ifhave9 == 1)/*如果已检测到有最高位的9*/
			{
				if (ifplus == 0)
				{
					MUL(9, a9);
					a9[0] = a9[0] + ch - 48;
					ifplus = 1;
					
					if (a9[0] >= 100000000)
					{
						GO(a9);
					}
				}
				else
				{
					MUL(9, a9);
				}
			}
			else
			{
				MUL(9, a9);
				a9[0] = a9[0] + ch - 48;
			}
		}
		MINUS(a10, a9, ahave9);

		/*Reset ifhave9*/
		ifhave9 = 0;
		ifplus = 0;
		iffirst = 1;/*看是否是第一位是9*/
		for (;;)/*录入B*/
		{
			ch = getchar();/*输入*/
			if (ch == '\n')
			{
				break;
			}

			if (ch == '9'&&ifhave9 == 0)/*搜索到第一个9*/
			{
				ifhave9 = 1;
			}
			if (iffirst == 1)
			{
				if (ch == '9')
				{
					ifplus = 1;
				}
				b10[0] = ch - 48;
				b9[0] = ch - 48;
				bhave9[0] = 0;
				iffirst = 0;
				continue;
			}

			MUL(10, b10);
			b10[0] = b10[0] + ch - 48;
			if (ifhave9 == 1)/*如果已检测到有最高位的9*/
			{
				if (ifplus == 0)
				{
					MUL(9, b9);
					b9[0] = b9[0] + ch - 48;
					ifplus = 1;

					if (b9[0] >= 100000000)
					{
						GO(b9);
					}
				}
				else
				{
					MUL(9, b9);
				}
			}
			else
			{
				MUL(9, b9);
				b9[0] = b9[0] + ch - 48;
			}
		}
		MINUS(b10, b9, bhave9);


		MINUS(bhave9, ahave9, ANS);

		if (ifhave9 == 1)/*如果b本身含有9*/
		{
			ANS[0]++;
			if (ANS[0] >= 100000000)
			{
				int pl;/*用于ANS进位*/
				int t;/*用于检测是否进位*/
				for (pl = 0;; pl++)
				{
					t = ANS[pl] / 100000000;
					if (t >= 1)/*如果需要进位*/
					{
						if (ANS[pl + 1] == -1)/*如果需要再开一位*/
						{
							ANS[pl + 1] = t;
							ANShave++;
							ANS[pl] = ANS[pl] % 100000000;
						}
						else
						{
							ANS[pl + 1] = ANS[pl + 1] + t;
							ANS[pl] = ANS[pl] % 100000000;
						}
					}
					else/*不需要进位*/
					{
						break;
					}
				}
				for (ANSprint = ANShave; ANSprint >= 0; ANSprint--)
				{
					if (ANSprint == ANShave)
					{
						printf("%d", ANS[ANSprint]);
					}
					else
					{
						printf("%08d", ANS[ANSprint]);
					}
				}
				printf("\n");
			}
			else
			{
				for (ANSprint = ANShave; ANSprint >= 0; ANSprint--)
				{
					if (ANSprint == ANShave)
					{
						printf("%d", ANS[ANSprint]);
					}
					else
					{
						printf("%08d", ANS[ANSprint]);
					}
				}
				printf("\n");
			}
		}
		else
		{
			for (ANSprint = ANShave; ANSprint >= 0; ANSprint--)
			{
				if (ANSprint == ANShave)
				{
					printf("%d", ANS[ANSprint]);
				}
				else
				{
					printf("%08d", ANS[ANSprint]);
				}
			}
			printf("\n");
		}
		T--;
	}
}


void MUL(int n, int *ar)/*秦九韶累乘函数，仅处理累乘，不处理之后的加法*/
{
	int x;
	int temp = 0;

	for (x = 0; ar[x] != -1; x++)
	{
		if (ar[x] >= 100000000)
		{
			int p;
			int q;
			for (p = x;; p++)
			{
				q = ar[p] / 100000000;
				if (q >= 1)
				{
					if (ar[p + 1] == -1)
					{
						ar[p + 1] = q;
						ar[p] = ar[p] % 100000000;
					}
					else
					{
						ar[p + 1] = ar[p + 1] + q;
						ar[p] = ar[p] % 100000000;
					}
				}
				else
				{
					break;
				}
			}
		}
		ar[x] = ar[x] * n;
		ar[x] = ar[x] + temp;
		if (ar[x] >= 100000000)
		{
			if (ar[x + 1] == -1)
			{
				ar[x + 1] = ar[x] / 100000000;
				ar[x] = ar[x] % 100000000;
				break;
			}
			else
			{
				temp = ar[x] / 100000000;
				ar[x] = ar[x] % 100000000;
			}
		}
		else
		{
			temp = 0;
		}
	}
}

void MINUS(int *big, int *small, int *ans)/*压位高精度减法函数*/
{
	int count;
	int anscount;
	int temp;

	for (count = 0, anscount = 0; big[count] != -1; count++)
	{
		if (small[count] == -1)/*如果小数没有与大数相匹配的位*/
		{
			small[count] = 0;
		}
		temp = big[count] - small[count];
		if (temp < 0)
		{
			ans[anscount] = temp + 100000000;
			anscount++;
			if (big[count + 1] == 0)
			{
				int minus;/*向前退位*/
				for (minus = count + 1; big[minus] == 0; minus++)
				{
					big[minus] = 99999999;
				}/*将0变成99999999 并且定位到不为0的地方*/
				if (big[minus] == 1)/*如果需要向前来一位*/
				{
					big[minus] = -1;/*重置*/
				}
				else
				{
					big[minus]--;
				}
			}
			else
			{
				big[count + 1]--;
			}
		}
		else
		{
			ans[anscount] = temp;
			anscount++;
		}
	}
	ANShave = anscount - 1;
}

void GO(int *ar)
{
	/*在此处 ar[0]必定大于100000000*/

	int p;
	int q;
	for (p = 0;; p++)
	{
		q = ar[p] / 100000000;
		if (q >= 1)
		{
			if (ar[p + 1] == -1)
			{
				ar[p + 1] = q;
				ar[p] = ar[p] % 100000000;
			}
			else
			{
				ar[p + 1] = ar[p + 1] + q;
				ar[p] = ar[p] % 100000000;
			}
		}
		else
		{
			break;
		}
	}
}