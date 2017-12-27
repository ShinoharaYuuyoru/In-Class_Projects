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
	int Reset = 0;/*Resetר��*/
	int ifhave9 = 0;/*�����λ�Ƿ������9*/
	int iffirst = 0;/*���Ƿ��ǵ�һλ��9*/
	int ifplus = 0;/*��⵽��9���֣���ô���9Ӧ�ñ����룬��һ����ʼ������*/
	int T;/*��������*/
	int ANSprint = 0;/*���������*/
	char ch;/*��λ*/

	scanf("%d", &T);
	getchar();/*ȡ��T���\n*/

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
		iffirst = 1;/*���Ƿ��ǵ�һλ*/
		for (;;)/*¼��A*/
		{
			ch = getchar();/*����*/
			if (ch == ' ')
			{
				break;
			}

			if (ch == '9'&&ifhave9 == 0)/*��������һ��9*/
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
			if (ifhave9 == 1)/*����Ѽ�⵽�����λ��9*/
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
		iffirst = 1;/*���Ƿ��ǵ�һλ��9*/
		for (;;)/*¼��B*/
		{
			ch = getchar();/*����*/
			if (ch == '\n')
			{
				break;
			}

			if (ch == '9'&&ifhave9 == 0)/*��������һ��9*/
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
			if (ifhave9 == 1)/*����Ѽ�⵽�����λ��9*/
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

		if (ifhave9 == 1)/*���b������9*/
		{
			ANS[0]++;
			if (ANS[0] >= 100000000)
			{
				int pl;/*����ANS��λ*/
				int t;/*���ڼ���Ƿ��λ*/
				for (pl = 0;; pl++)
				{
					t = ANS[pl] / 100000000;
					if (t >= 1)/*�����Ҫ��λ*/
					{
						if (ANS[pl + 1] == -1)/*�����Ҫ�ٿ�һλ*/
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
					else/*����Ҫ��λ*/
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


void MUL(int n, int *ar)/*�ؾ����۳˺������������۳ˣ�������֮��ļӷ�*/
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

void MINUS(int *big, int *small, int *ans)/*ѹλ�߾��ȼ�������*/
{
	int count;
	int anscount;
	int temp;

	for (count = 0, anscount = 0; big[count] != -1; count++)
	{
		if (small[count] == -1)/*���С��û���������ƥ���λ*/
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
				int minus;/*��ǰ��λ*/
				for (minus = count + 1; big[minus] == 0; minus++)
				{
					big[minus] = 99999999;
				}/*��0���99999999 ���Ҷ�λ����Ϊ0�ĵط�*/
				if (big[minus] == 1)/*�����Ҫ��ǰ��һλ*/
				{
					big[minus] = -1;/*����*/
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
	/*�ڴ˴� ar[0]�ض�����100000000*/

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