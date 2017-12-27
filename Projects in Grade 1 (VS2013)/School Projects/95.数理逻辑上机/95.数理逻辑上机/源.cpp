/*用真值表确定主析取、合取范式并输出*/

#include "stdio.h"

int count(char *formula);
void bina(int line);
int GetFirst(char i);
void Push(char ch);
char Pop(char *ch);
int RetNumber(char i);

char formula[1000];//公式 从第0位开始
int element;//元素个数
char sign[1000];//元素
int excel[1000][10];//真值表

char OPSTACK[1000];//运算符栈 用于中缀转后缀
int Pushcount = 0;//运算符入栈指针
int searchstack = 0;//运算符栈主函数指针
char NewFormula[1000];//后缀表达式
int NFcount = 0;//NewFormula指针

int main()
{
	int formc;//检索公式用
	int searchleftbra = 0;//临时搜索栈中是否有左括号

	scanf("%s", formula);//输入公式

	element = count(formula);

	int line, linesum = 1;
	int excelbraqplus;//用于根据括号拓展真值表

	excelbraqplus = element + 1;//将用于扩展真值表的指针定向到真值指派的下一个列

	for (line = 1; line <= element; line++)//行数确定 
	{
		linesum = linesum * 2;
	}

	for (line = 0; line < linesum; line++)//真值指派 
	{
		if (line >= 1)
		{
			bina(line);
		}
	}

	for (formc = 0; formula[formc] != '\0'; formc++)//中缀表达式转后缀表达式  检索公式
	{
		if (formula[formc] >= 'A'&&formula[formc] <= 'z')//如果是字母 则直接加入后缀表达式
		{
			NewFormula[NFcount] = formula[formc];
			NFcount++;
		}
		if (formula[formc] == '!' || formula[formc] == '+' || formula[formc] == '-' || formula[formc] == '|' || formula[formc] == '&' || formula[formc] == '(' || formula[formc] == ')')//如果是符号 需要判断优先级再加入表达式
		{
			if (OPSTACK[0] == '\0')//如果栈为空  直接入栈  注意  以后在POP的时候需要将位置改变成'\0'
			{
				Pushcount = 0;
				Push(formula[formc]);
			}
			else//如果栈不为空
			{
				for (searchstack = 0; OPSTACK[searchstack] != '\0'; searchstack++);
				searchstack--;
				for (; searchstack >= 0; searchstack--)//出栈
				{
					if (GetFirst(OPSTACK[searchstack]) >= GetFirst(formula[formc]))//从栈顶搜索 如果此符号优先级大于现在的符号 则弹出
					{
						if (formula[formc] == ')')//右括号 则弹出到左括号之前 并且弹出左括号但不输出
						{
							for (; OPSTACK[searchstack] != '('; searchstack--)
							{
								NewFormula[NFcount] = Pop(OPSTACK);
								NFcount++;
							}
							OPSTACK[searchstack] = '\0';
							break;
						}
						if (formula[formc] == '(')//特殊：左括号直接压栈
						{
							Push(formula[formc]);
							break;
						}
						else
						{
							for (searchleftbra = searchstack; searchleftbra >= 0; searchleftbra--)//从栈顶搜索有无左括号
							{
								if (OPSTACK[searchleftbra] == '(')//如果栈中有左括号  则弹出到左括号之前  不弹出左括号
								{
									for (searchleftbra = searchstack; GetFirst(OPSTACK[searchleftbra]) >= GetFirst(formula[formc]) && OPSTACK[searchleftbra] != '('; searchleftbra--)
									{
										NewFormula[NFcount] = Pop(OPSTACK);
										NFcount++;
									}
									Push(formula[formc]);
									goto k;
								}

							}
							if (searchleftbra == -1)//若栈中无左括号  则正常按照优先级弹出和压入
							{
								NewFormula[NFcount] = Pop(OPSTACK);
								NFcount++;
								Push(formula[formc]);//新符号压栈
							}

						}
					}
					else//如果没有比现有符号优先级大的 则直接压栈
					{
						Push(formula[formc]);
						break;
					}
				}
			k:;
			}
		}
	}
	if (OPSTACK[0] != '\0')//如果检索完所有公式后  操作栈中还有操作符  则将操作符依次弹出
	{
		for (searchstack = 0; OPSTACK[searchstack] != '\0'; searchstack++);
		searchstack--;
		for (; searchstack >= 0; searchstack--)
		{
			NewFormula[NFcount] = Pop(OPSTACK);
			NFcount++;
		}
	}

	int Point = 0;//定义计算的范围
	int opline[1000];//计算行
	int oplinecount = 0;//计算行指针

	for (line = 0; line < linesum; line++)//按每行开始真值指派
	{
		for (oplinecount = 0, Point = 0; NewFormula[Point] != '\0'; Point++)
		{
			if (NewFormula[Point] >= 'A'&&NewFormula[Point] <= 'z')//如果是元素
			{
				opline[oplinecount] = excel[line][RetNumber(NewFormula[Point])];
				oplinecount++;
			}
			else
			{
				if (NewFormula[Point] == '!')//非
				{
					if (opline[oplinecount - 1] == 1)
					{
						opline[oplinecount - 1] = 0;
					}
					else
					{
						opline[oplinecount - 1] = 1;
					}
				}
				if (NewFormula[Point] == '-')//蕴含
				{
					if (opline[oplinecount - 2] == 0)
					{
						opline[oplinecount - 2] = 1;
						oplinecount--;
					}
					else
					{
						if (opline[oplinecount - 1] == 0)
						{
							opline[oplinecount - 2] = 0;
							oplinecount--;
						}
						else
						{
							opline[oplinecount - 2] = 1;
							oplinecount--;
						}
					}
				}
				if (NewFormula[Point] == '+')//等价
				{
					if (opline[oplinecount - 2] == opline[oplinecount - 1])
					{
						opline[oplinecount - 2] = 1;
						oplinecount--;
					}
					else
					{
						opline[oplinecount - 2] = 0;
						oplinecount--;
					}
				}
				if (NewFormula[Point] == '|')//析取
				{
					if (opline[oplinecount - 2] == 0 && opline[oplinecount - 1] == 0)
					{
						opline[oplinecount - 2] = 0;
						oplinecount--;
					}
					else
					{
						opline[oplinecount - 2] = 1;
						oplinecount--;
					}

				}
				if (NewFormula[Point] == '&')//合取
				{
					if (opline[oplinecount - 2] == 1 && opline[oplinecount - 1] == 1)
					{
						opline[oplinecount - 2] = 1;
						oplinecount--;
					}
					else
					{
						opline[oplinecount - 2] = 0;
						oplinecount--;
					}
				}
			}
		}
		excel[line][element] = opline[oplinecount - 1];
	}

	int mnumber = 0, Mnumber = 0;
	int mnumbercount = 0, Mnumbercount = 0;

	for (line = 0; line < linesum; line++)//记录0和1的个数
	{
		if (excel[line][element] == 1)
		{
			mnumber++;
		}
		else
		{
			Mnumber++;
		}
	}

	if (mnumber == 0)
	{
		printf("0 ; ");
	}
	else
	{
		for (line = 0; line < linesum; line++)
		{
			if (excel[line][element] == 1)
			{
				mnumbercount++;
				printf("m%d ", line);
				if (mnumbercount < mnumber)
				{
					printf("∨ ");
				}
				if (mnumbercount == mnumber)
				{
					printf("; ");
				}
			}
		}
	}
	if (Mnumber == 0)
	{
		printf("1\n");
	}
	else
	{
		for (line = 0; line < linesum; line++)
		{
			if (excel[line][element] == 0)
			{
				Mnumbercount++;
				if (Mnumbercount == Mnumber)
				{
					printf("M%d\n", line);
					break;
				}
				printf("M%d ", line);
				if (Mnumbercount < Mnumber)
				{
					printf("∧ ");
				}
			}
		}
	}
}

int count(char *formula)//计数公式中元素个数
{
	int x;//角标指针
	int signx;

	for (x = 0; formula[x] != '\0'; x++)
	{
		if (formula[x] >= 'A'&&formula[x] <= 'z')//先判断是否为字母
		{
			for (signx = 0; sign[signx] != '\0'; signx++)
			{
				if (sign[signx] == formula[x])
				{
					break;
				}
			}
			if (sign[signx] == '\0')
			{
				sign[signx] = formula[x];
			}
		}
	}
	for (signx = 0; sign[signx] != '\0'; signx++);
	return signx;
}

void bina(int line)//真值指派 
{
	int linecpy = line;

	for (int x = element - 1; x >= 0; x--)
	{
		excel[line][x] = linecpy % 2;
		linecpy = linecpy / 2;
	}
}

void Push(char ch)
{
	OPSTACK[Pushcount] = ch;
	Pushcount++;
}

char Pop(char *ch)
{
	char ret;//弹出的符号
	int Popcount = searchstack;
	ret = OPSTACK[Popcount];
	OPSTACK[Popcount] = '\0';
	Pushcount = Popcount;
	Popcount--;
	return ret;
}

int GetFirst(char i)//判断优先级
{
	if (i == '!')
	{
		return 3;
	}
	if (i == '+' || i == '-')
	{
		return 1;
	}
	if (i == '|' || i == '&')
	{
		return 2;
	}
	if (i == '(')
	{
		return 4;
	}
	if (i == ')')
	{
		return 0;
	}
	return 9;
}

int RetNumber(char i)//返回 第几个元素
{
	int RN;//return number
	
	for (RN = 0; sign[RN] != i; RN++);
	return RN;
}

/*林哥的代码*/
//#include <stdio.h>  
//#include <stdlib.h>  
//#include <string.h>  
//#include <math.h> 
//#define OK 1
//#define ERROR -1
//#define DEBUG 0 
//*	潜在BUG: 不可处理超过4个的命题变元，问题处于infoCollector处
//*
//*
//*
//*
//*/
////堆栈功能实现  
//typedef struct node
//{
//	char data;
//	struct node* next;
//}StackNode, *LinkStack;
//
//LinkStack initStack(LinkStack top)
//{
//	top = (LinkStack)malloc(sizeof(StackNode));
//	top->data = '#';
//	top->next = NULL;
//	return top;
//}
//
//int StackEmpty(LinkStack top)
//{
//	if (top->data == '#')
//		return OK;
//	else
//		return ERROR;
//}
//
//LinkStack Push(LinkStack top, char x)
//{
//	StackNode *s;
//	s = (LinkStack)malloc(sizeof(StackNode));
//	s->data = x;
//	s->next = top;
//	top = s;
//	return top;
//}
//
//LinkStack Pop(LinkStack top, char *x)
//{
//	StackNode *p;
//	if (top->data == '#')
//		return NULL;
//	else
//	{
//		*x = top->data;
//		p = top;
//		top = top->next;
//		free(p);
//		p = NULL;
//		return top;
//	}
//}
////堆栈功能完结
//
////全局名称存储
//char names[27] = { "\0" };
//
////符号检测器
//int isOperator(char c)
//{
//	char OP[] = "+-|&!()";
//	int i;
//	for (i = 0; i< 7; i++) if (c == OP[i]) return i;
//	return ERROR;
//}
//
////优先级判断器  
//char Preceder(char OPTR1, char OPTR2)
//{
//	int i, j;
//	char OP[] = "+-|&!";
//	char tab[6][6] = {
//		"><<<<",
//		">><<<",
//		">>><<",
//		">>>><",
//		">>>>>"
//	};
//	for (i = 0; i < 5; i++) if (OP[i] == OPTR1) break;
//	for (j = 0; j < 5; j++) if (OP[j] == OPTR2) break;
//	return tab[j][i];
//}
//
////命题变元数量获取、名称记录器
////名称已按字典序排列  
//int getNumber(char* exp)
//{
//	int i, j, found, length, temp;
//	//收集名称
//	for (i = 0; exp[i] != 0; i++)
//	{
//		if (isOperator(exp[i]) == ERROR)
//		{
//			found = 0;
//			for (j = 0; names[j] != 0; j++)
//			{
//				if (exp[i] == names[j])
//				{
//					found = 1;
//					break;
//				}
//			}
//			if (!found)
//			{
//				strncat(names, &exp[i], 1);
//			}
//		}
//	}
//	//名称排序
//	length = strlen(names);
//	for (i = 0; i < length - 1; i++)
//	{
//		for (j = 0; j < length - 1 - i; j++)
//		{
//			if (names[j] > names[j + 1])
//			{
//				temp = names[j];
//				names[j] = names[j + 1];
//				names[j + 1] = temp;
//			}
//		}
//	}
//	if (DEBUG == 1)
//		printf("The names are: %s\n", names);
//	return length;
//}
//
////中缀转后缀转换器  
//void ExpConverter(char* Mid, char* destination)
//{
//	int i;
//	char pop_out;
//	LinkStack OperatorStack;
//	OperatorStack = initStack(OperatorStack);
//	for (i = 0; Mid[i] != 0; i++)//中缀处理开始
//	{
//		if (isOperator(Mid[i]) == ERROR)//字符直接输出
//			strncat(destination, &Mid[i], 1);
//		else
//		{
//			if (StackEmpty(OperatorStack) == OK)//为空直接压入
//				OperatorStack = Push(OperatorStack, Mid[i]);
//			else//不为空则进行判断
//			{
//				char pop_out;
//				OperatorStack = Pop(OperatorStack, &pop_out);//先pop出一个（肯定不会没有的）
//				if (pop_out == '(' || Mid[i] == '(')//左括号特殊处理
//				{
//					OperatorStack = Push(OperatorStack, pop_out);
//					OperatorStack = Push(OperatorStack, Mid[i]);
//					continue;
//				}
//				if (Mid[i] == ')')//右括号特殊处理
//				{
//					while (pop_out != '(')//到左括号为止
//					{
//						strncat(destination, &pop_out, 1);
//						OperatorStack = Pop(OperatorStack, &pop_out);
//					}
//					continue;
//				}
//				switch (Preceder(pop_out, Mid[i]))
//				{
//				case '>':
//				{
//							OperatorStack = Push(OperatorStack, pop_out);
//							OperatorStack = Push(OperatorStack, Mid[i]);
//							break;
//				}
//				case '<':
//				{
//							OperatorStack = Push(OperatorStack, Mid[i]);
//							strncat(destination, &pop_out, 1);
//							break;
//				}
//				default:
//				{
//						   fprintf(stderr, "PrecederResultExcption: Invalid result: %c"\
//							   , Preceder(pop_out, Mid[i]));
//						   exit(ERROR);
//				}
//				}
//
//			}
//		}
//	}
//	while (StackEmpty(OperatorStack) == ERROR)
//	{
//		OperatorStack = Pop(OperatorStack, &pop_out);
//		strncat(destination, &pop_out, 1);
//	}
//	if (DEBUG == 1)
//		printf("The converted expression is %s\n", destination);
//}
//
////控制器
//void ControlUnit(char* exp, int number, int pows, int *m, int *M)//本模块有全局依赖
//{
//	int i, j, temp;
//	int *BinarySet;
//	//动态BiSet生成
//	BinarySet = (int*)malloc(number*sizeof(int)+1);
//	//BiSet初始化
//	for (i = 0; i < number; i++) BinarySet[i] = 0;
//	for (i = 0; i < pows; i++)
//	{
//		temp = i;
//		for (j = number - 1; j >= 0; j--)
//		{
//			BinarySet[j] = temp % 2;
//			temp /= 2;
//		}
//		if (DEBUG == 1)
//		{
//			printf("The BinarySet is: ");
//			for (temp = 0; temp < number; temp++)
//			{
//				printf("%d", BinarySet[temp]);
//			}
//			printf("\n");
//		}
//		//结果记录
//		if (ArithmeticUnit(exp, number, BinarySet) == 1)
//		{
//			m[i] = 1;
//			if (DEBUG == 1)
//				printf("The result is 1\n");
//		}
//		else
//		{
//			M[i] = 1;
//			if (DEBUG == 1)
//				printf("The result is 0\n");
//		}
//	}
//}
//
////运算器  
//int ArithmeticUnit(char* exp, int length, int* BinarySet)
//{
//	LinkStack OperandStack;
//	OperandStack = initStack(OperandStack);
//	int i, j, oprand1 = 0, oprand2 = 0;
//	char pop_out;
//	for (i = 0; exp[i] != 0; i++)
//	{
//		if (isOperator(exp[i]) == ERROR)//字符的赋值
//		{
//			for (j = 0; j < length; j++)
//			{
//				if (exp[i] == names[j])
//				{
//					OperandStack = Push(OperandStack, BinarySet[j]);
//					break;
//				}
//			}
//			if (j == length)
//			{
//				fprintf(stderr, "OprandNotFoundExcption: Invalid oprand: %c\n", exp[i]);
//				exit(ERROR);
//			}
//		}
//		else
//		{
//			switch (exp[i])//计算部分
//			{
//				//双目运算符
//			case '&':
//			{
//						OperandStack = Pop(OperandStack, &oprand1);
//						OperandStack = Pop(OperandStack, &oprand2);
//						OperandStack = Push(OperandStack, oprand1 && oprand2);
//						break;
//			}
//			case '|':
//			{
//						OperandStack = Pop(OperandStack, &oprand1);
//						OperandStack = Pop(OperandStack, &oprand2);
//						OperandStack = Push(OperandStack, oprand1 || oprand2);
//						break;
//			}
//			case '+':
//			{
//						OperandStack = Pop(OperandStack, &oprand1);
//						OperandStack = Pop(OperandStack, &oprand2);
//						OperandStack = Push(OperandStack, \
//							(!oprand1 || oprand2) && (oprand1 || !oprand2));
//						break;
//			}
//			case '-':
//			{
//						OperandStack = Pop(OperandStack, &oprand1);
//						OperandStack = Pop(OperandStack, &oprand2);
//						OperandStack = Push(OperandStack, !oprand2 || oprand1);
//						break;
//			}
//				//单目运算符
//			case '!':
//			{
//						OperandStack = Pop(OperandStack, &oprand1);
//						OperandStack = Push(OperandStack, !oprand1);
//						break;
//			}
//			default:
//			{
//					   fprintf(stderr, "OperatorNotFoundExcption: Invalid operator: %c\n", exp[i]);
//					   exit(ERROR);
//			}
//			}
//		}
//	}
//	OperandStack = Pop(OperandStack, &pop_out);//返回最终结果
//	return pop_out;
//}
//
////有价值信息收集器
//void infoCollector(int *m, int *M, char *destm, char *destM, int pows)//存在潜在bug
//{
//	int i;
//	char digit;
//	for (i = 0; i < pows; i++)
//	{
//		if (m[i] == 1)
//		{
//			digit = i + 48;
//			strncat(destm, &digit, 1);
//		}
//		if (M[i] == 1)
//		{
//			digit = i + 48;
//			strncat(destM, &digit, 1);
//		}
//	}
//	if (DEBUG == 1)
//	{
//		printf("destm is: %s\n", destm);
//		printf("destM is: %s\n", destM);
//	}
//
//}
//
//int main()
//{
//	char buffer[10000];
//	int i, mi, mj, Mi, Mj, numbers = 0, pows = 0, length;
//	//获取阶段
//	gets(buffer);
//	length = strlen(buffer);
//	numbers = getNumber(buffer);
//	//初始化阶段 
//	pows = (int)pow(2, numbers);
//	char *tobeOperated;
//	tobeOperated = (char*)malloc(length + 1);
//	int *m, *M;
//	char *destm, *destM;
//	m = (int*)malloc(pows*sizeof(int)+1);
//	M = (int*)malloc(pows*sizeof(int)+1);
//	destm = (char*)malloc(pows*sizeof(char)+1);
//	destM = (char*)malloc(pows*sizeof(char)+1);
//	for (i = 0; i< length; i++) tobeOperated[i] = '\0';
//	for (i = 0; i< numbers; i++) destm[i] = '\0';
//	for (i = 0; i< numbers; i++) destM[i] = '\0';
//	//转换为后缀表达式 
//	ExpConverter(buffer, tobeOperated);
//	//进行二进制加法器运算，记录结果
//	ControlUnit(tobeOperated, numbers, pows, m, M);
//
//	//输出格式化
//	infoCollector(m, M, destm, destM, pows);
//	for (mi = 0; destm[mi] != 0; mi++);
//	for (Mi = 0; destM[Mi] != 0; Mi++);
//
//
//	if (mi == 0)//永假式处理
//	{
//		printf("NO\n");
//	}
//	else
//	{
//		printf("YES\n");
//	}
//	//尾处理
//	free(tobeOperated); free(m); free(M); free(destm); free(destM);
//	return 0;
//}