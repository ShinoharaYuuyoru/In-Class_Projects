#include "stdio.h"

int main()
{
	char I;//Input.
	char T;//Scan.
	char Orig[200] = { '\0' };//原式
	char Line[200] = { '\0' };//后缀

	char Stack[200] { '\0' };

	int Ex;//Expression counter.
	int OrigC;//Origin counter.
	int StackC = 0;// Stack counter.
	int LineC = 0;//Line counter.

	int Rs;//Reset.

	for (Ex = 1;; Ex++)
	{
		/*Reset*/
		for (Rs = 0; Rs < 200; Rs++)
		{
			Orig[Rs] = '\0';
			Line[Rs] = '\0';
			Stack[Rs] = '\0';
		}
		OrigC = 0;
		StackC = 0;
		LineC = 0;

		for (;;)
		{
			if (scanf("%c", &I) == EOF)
			{
				if (Orig[OrigC - 1] == 'F' || Orig[OrigC - 1] == 'V' || Orig[OrigC - 1] == ')')
				{
					Orig[OrigC] = '\n';
					break;
				}
			}
			else
			{
				if (I == ' ')
				{
					continue;
				}
				if (I == '\n')
				{
					Orig[OrigC] = I;
					break;
				}

				Orig[OrigC] = I;
				OrigC++;
			}
		}

		for (OrigC = 0; Orig[OrigC] != '\0'; OrigC++)
		{
			T = Orig[OrigC];

			if (T == '\n')
			{
				if (Stack[0] != '\0')
				{
					for (StackC--; StackC >= 0; StackC--)
					{
						Line[LineC] = Stack[StackC];
						LineC++;
					}
					StackC++;
					Stack[0] = '\0';
				}
				goto k;
			}
			if (T == 'V' || T == 'F')
			{
				Line[LineC] = T;
				LineC++;
				continue;
			}
			if (T == '(')
			{
				Stack[StackC] = T;
				StackC++;
				continue;
			}
			if (T == '!')
			{
				if (Orig[OrigC + 1] == 'F' || Orig[OrigC + 1] == 'V')
				{
					Line[LineC] = Orig[OrigC + 1];
					LineC++;
					Line[LineC] = Orig[OrigC];
					LineC++;
					OrigC++;
				}
				else
				{
					if (Orig[OrigC + 1] == '!')
					{
						OrigC++;
						continue;
					}
					else
					{
						Stack[StackC] = T;
						StackC++;
					}
					continue;
				}
			}
			if (T == '&')
			{
				if (Stack[0] == '\0')
				{
					Stack[0] = T;
					StackC++;
				}
				else
				{
					for (StackC--; Stack[StackC] == '&'; StackC--)
					{
						Line[LineC] = Stack[StackC];
						Stack[StackC] = '\0';
						LineC++;
					}
					StackC++;
					Stack[StackC++] = T;
				}
				continue;
			}
			if (T == '|')
			{
				if (Stack[0] == '\0')
				{
					Stack[0] = T;
					StackC++;
				}
				else
				{
					for (StackC--; Stack[StackC] == '&' || Stack[StackC] == '|'; StackC--)
					{
						Line[LineC] = Stack[StackC];
						Stack[StackC] = '\0';
						LineC++;
					}
					StackC++;
					Stack[StackC++] = T;
				}
				continue;
			}
			if (T == ')')
			{
				for (StackC--; Stack[StackC] != '('; StackC--)
				{
					Line[LineC] = Stack[StackC];
					Stack[StackC] = '\0';
					LineC++;
				}
				Stack[StackC] = '\0';
				continue;
			}
		}

	k:;
		char S;//Search.
		int x;
		int ExStack[200] = { 0 };//计算Stack.

		int ExStackC = 0;//ExStack counter.

		for (x = 0; Line[x] != '\0'; x++)
		{
			S = Line[x];

			if (S == 'V')
			{
				ExStack[ExStackC] = 1;
				ExStackC++;
				continue;
			}
			if (S == 'F')
			{
				ExStack[ExStackC] = 0;
				ExStackC++;
				continue;
			}
			if (S == '!')
			{
				if (ExStack[ExStackC - 1] == 0)
				{
					ExStack[ExStackC - 1] = 1;
				}
				else
				{
					ExStack[ExStackC - 1] = 0;
				}
				continue;
			}
			if (S == '|')
			{
				ExStack[ExStackC - 2] = (ExStack[ExStackC - 2] || ExStack[ExStackC - 1]);
				ExStackC--;
				ExStack[ExStackC] = 0;
				continue;
			}
			if (S == '&')
			{
				ExStack[ExStackC - 2] = (ExStack[ExStackC - 2] && ExStack[ExStackC - 1]);
				ExStackC--;
				ExStack[ExStackC] = 0;
				continue;
			}
		}
		if (ExStack[0] == 1)
		{
			printf("Expression %d: V\n", Ex);
		}
		else
		{
			printf("Expression %d: F\n", Ex);
		}
	}
}


/*Internet Code*/
//#include<cstdio>  
//const int maxn = 110;  
//     
//bool val[maxn];  
//int op[maxn], vp, pp;  
//     
//void insert(bool b)  
//{  
//    while (pp && op[pp - 1] == 3)  
//    {  
//        b = !b;  
//        --pp;  
//    }  
//    val[vp++] = b;  
//}  
//     
//void calc()  
//{  
//    bool b = val[--vp];  
//    bool a = val[--vp];  
//    int opr = op[--pp];  
//    insert(opr == 1 ? a | b : a & b);  
//}  
//     
///* 
//定义优先级为（数字越大优先级越高） 
//(:0 
//|:1 
//&:2 
//!:3 
//):4 
//*/
//int main()  
//{  
//    int cas = 0;  
//    char c;  
//    while (~(c = getchar()))  
//    {  
//        vp = pp = 0;  
//        do
//        {  
//            if (c == '(')  
//                op[pp++] = 0;  
//            else if (c == ')')  
//            {  
//                while (pp && op[pp - 1])///处理括号内的所有运算  
//                    calc();  
//                --pp;  
//                insert(val[--vp]);///算'!'  
//            }  
//            else if (c == '!')  
//                op[pp++] = 3;  
//            else if (c == '&')  
//            {  
//                while (pp && op[pp - 1] >= 2)///'&' '!'  
//                    calc();  
//                op[pp++] = 2;  
//            }  
//            else if (c == '|')  
//            {  
//                while (pp && op[pp - 1] >= 1)///'|' '&' '!'  
//                    calc();  
//                op[pp++] = 1;  
//            }  
//            else if (c == 'V' || c == 'F')  
//                insert(c == 'V' ? true : false);  
//            ///空格被忽略  
//        }  
//        while ((c = getchar()) != 10 && ~c);  
//        while (pp)  
//            calc();  
//        printf("Expression %d: %c\n", ++cas, (val[0] ? 'V' : 'F'));  
//    }  
//}