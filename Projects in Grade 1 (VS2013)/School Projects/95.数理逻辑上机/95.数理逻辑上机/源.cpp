/*����ֵ��ȷ������ȡ����ȡ��ʽ�����*/

#include "stdio.h"

int count(char *formula);
void bina(int line);
int GetFirst(char i);
void Push(char ch);
char Pop(char *ch);
int RetNumber(char i);

char formula[1000];//��ʽ �ӵ�0λ��ʼ
int element;//Ԫ�ظ���
char sign[1000];//Ԫ��
int excel[1000][10];//��ֵ��

char OPSTACK[1000];//�����ջ ������׺ת��׺
int Pushcount = 0;//�������ջָ��
int searchstack = 0;//�����ջ������ָ��
char NewFormula[1000];//��׺���ʽ
int NFcount = 0;//NewFormulaָ��

int main()
{
	int formc;//������ʽ��
	int searchleftbra = 0;//��ʱ����ջ���Ƿ���������

	scanf("%s", formula);//���빫ʽ

	element = count(formula);

	int line, linesum = 1;
	int excelbraqplus;//���ڸ���������չ��ֵ��

	excelbraqplus = element + 1;//��������չ��ֵ���ָ�붨����ֵָ�ɵ���һ����

	for (line = 1; line <= element; line++)//����ȷ�� 
	{
		linesum = linesum * 2;
	}

	for (line = 0; line < linesum; line++)//��ֵָ�� 
	{
		if (line >= 1)
		{
			bina(line);
		}
	}

	for (formc = 0; formula[formc] != '\0'; formc++)//��׺���ʽת��׺���ʽ  ������ʽ
	{
		if (formula[formc] >= 'A'&&formula[formc] <= 'z')//�������ĸ ��ֱ�Ӽ����׺���ʽ
		{
			NewFormula[NFcount] = formula[formc];
			NFcount++;
		}
		if (formula[formc] == '!' || formula[formc] == '+' || formula[formc] == '-' || formula[formc] == '|' || formula[formc] == '&' || formula[formc] == '(' || formula[formc] == ')')//����Ƿ��� ��Ҫ�ж����ȼ��ټ�����ʽ
		{
			if (OPSTACK[0] == '\0')//���ջΪ��  ֱ����ջ  ע��  �Ժ���POP��ʱ����Ҫ��λ�øı��'\0'
			{
				Pushcount = 0;
				Push(formula[formc]);
			}
			else//���ջ��Ϊ��
			{
				for (searchstack = 0; OPSTACK[searchstack] != '\0'; searchstack++);
				searchstack--;
				for (; searchstack >= 0; searchstack--)//��ջ
				{
					if (GetFirst(OPSTACK[searchstack]) >= GetFirst(formula[formc]))//��ջ������ ����˷������ȼ��������ڵķ��� �򵯳�
					{
						if (formula[formc] == ')')//������ �򵯳���������֮ǰ ���ҵ��������ŵ������
						{
							for (; OPSTACK[searchstack] != '('; searchstack--)
							{
								NewFormula[NFcount] = Pop(OPSTACK);
								NFcount++;
							}
							OPSTACK[searchstack] = '\0';
							break;
						}
						if (formula[formc] == '(')//���⣺������ֱ��ѹջ
						{
							Push(formula[formc]);
							break;
						}
						else
						{
							for (searchleftbra = searchstack; searchleftbra >= 0; searchleftbra--)//��ջ����������������
							{
								if (OPSTACK[searchleftbra] == '(')//���ջ����������  �򵯳���������֮ǰ  ������������
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
							if (searchleftbra == -1)//��ջ����������  �������������ȼ�������ѹ��
							{
								NewFormula[NFcount] = Pop(OPSTACK);
								NFcount++;
								Push(formula[formc]);//�·���ѹջ
							}

						}
					}
					else//���û�б����з������ȼ���� ��ֱ��ѹջ
					{
						Push(formula[formc]);
						break;
					}
				}
			k:;
			}
		}
	}
	if (OPSTACK[0] != '\0')//������������й�ʽ��  ����ջ�л��в�����  �򽫲��������ε���
	{
		for (searchstack = 0; OPSTACK[searchstack] != '\0'; searchstack++);
		searchstack--;
		for (; searchstack >= 0; searchstack--)
		{
			NewFormula[NFcount] = Pop(OPSTACK);
			NFcount++;
		}
	}

	int Point = 0;//�������ķ�Χ
	int opline[1000];//������
	int oplinecount = 0;//������ָ��

	for (line = 0; line < linesum; line++)//��ÿ�п�ʼ��ֵָ��
	{
		for (oplinecount = 0, Point = 0; NewFormula[Point] != '\0'; Point++)
		{
			if (NewFormula[Point] >= 'A'&&NewFormula[Point] <= 'z')//�����Ԫ��
			{
				opline[oplinecount] = excel[line][RetNumber(NewFormula[Point])];
				oplinecount++;
			}
			else
			{
				if (NewFormula[Point] == '!')//��
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
				if (NewFormula[Point] == '-')//�̺�
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
				if (NewFormula[Point] == '+')//�ȼ�
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
				if (NewFormula[Point] == '|')//��ȡ
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
				if (NewFormula[Point] == '&')//��ȡ
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

	for (line = 0; line < linesum; line++)//��¼0��1�ĸ���
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
					printf("�� ");
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
					printf("�� ");
				}
			}
		}
	}
}

int count(char *formula)//������ʽ��Ԫ�ظ���
{
	int x;//�Ǳ�ָ��
	int signx;

	for (x = 0; formula[x] != '\0'; x++)
	{
		if (formula[x] >= 'A'&&formula[x] <= 'z')//���ж��Ƿ�Ϊ��ĸ
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

void bina(int line)//��ֵָ�� 
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
	char ret;//�����ķ���
	int Popcount = searchstack;
	ret = OPSTACK[Popcount];
	OPSTACK[Popcount] = '\0';
	Pushcount = Popcount;
	Popcount--;
	return ret;
}

int GetFirst(char i)//�ж����ȼ�
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

int RetNumber(char i)//���� �ڼ���Ԫ��
{
	int RN;//return number
	
	for (RN = 0; sign[RN] != i; RN++);
	return RN;
}

/*�ָ�Ĵ���*/
//#include <stdio.h>  
//#include <stdlib.h>  
//#include <string.h>  
//#include <math.h> 
//#define OK 1
//#define ERROR -1
//#define DEBUG 0 
//*	Ǳ��BUG: ���ɴ�����4���������Ԫ�����⴦��infoCollector��
//*
//*
//*
//*
//*/
////��ջ����ʵ��  
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
////��ջ�������
//
////ȫ�����ƴ洢
//char names[27] = { "\0" };
//
////���ż����
//int isOperator(char c)
//{
//	char OP[] = "+-|&!()";
//	int i;
//	for (i = 0; i< 7; i++) if (c == OP[i]) return i;
//	return ERROR;
//}
//
////���ȼ��ж���  
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
////�����Ԫ������ȡ�����Ƽ�¼��
////�����Ѱ��ֵ�������  
//int getNumber(char* exp)
//{
//	int i, j, found, length, temp;
//	//�ռ�����
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
//	//��������
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
////��׺ת��׺ת����  
//void ExpConverter(char* Mid, char* destination)
//{
//	int i;
//	char pop_out;
//	LinkStack OperatorStack;
//	OperatorStack = initStack(OperatorStack);
//	for (i = 0; Mid[i] != 0; i++)//��׺����ʼ
//	{
//		if (isOperator(Mid[i]) == ERROR)//�ַ�ֱ�����
//			strncat(destination, &Mid[i], 1);
//		else
//		{
//			if (StackEmpty(OperatorStack) == OK)//Ϊ��ֱ��ѹ��
//				OperatorStack = Push(OperatorStack, Mid[i]);
//			else//��Ϊ��������ж�
//			{
//				char pop_out;
//				OperatorStack = Pop(OperatorStack, &pop_out);//��pop��һ�����϶�����û�еģ�
//				if (pop_out == '(' || Mid[i] == '(')//���������⴦��
//				{
//					OperatorStack = Push(OperatorStack, pop_out);
//					OperatorStack = Push(OperatorStack, Mid[i]);
//					continue;
//				}
//				if (Mid[i] == ')')//���������⴦��
//				{
//					while (pop_out != '(')//��������Ϊֹ
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
////������
//void ControlUnit(char* exp, int number, int pows, int *m, int *M)//��ģ����ȫ������
//{
//	int i, j, temp;
//	int *BinarySet;
//	//��̬BiSet����
//	BinarySet = (int*)malloc(number*sizeof(int)+1);
//	//BiSet��ʼ��
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
//		//�����¼
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
////������  
//int ArithmeticUnit(char* exp, int length, int* BinarySet)
//{
//	LinkStack OperandStack;
//	OperandStack = initStack(OperandStack);
//	int i, j, oprand1 = 0, oprand2 = 0;
//	char pop_out;
//	for (i = 0; exp[i] != 0; i++)
//	{
//		if (isOperator(exp[i]) == ERROR)//�ַ��ĸ�ֵ
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
//			switch (exp[i])//���㲿��
//			{
//				//˫Ŀ�����
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
//				//��Ŀ�����
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
//	OperandStack = Pop(OperandStack, &pop_out);//�������ս��
//	return pop_out;
//}
//
////�м�ֵ��Ϣ�ռ���
//void infoCollector(int *m, int *M, char *destm, char *destM, int pows)//����Ǳ��bug
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
//	//��ȡ�׶�
//	gets(buffer);
//	length = strlen(buffer);
//	numbers = getNumber(buffer);
//	//��ʼ���׶� 
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
//	//ת��Ϊ��׺���ʽ 
//	ExpConverter(buffer, tobeOperated);
//	//���ж����Ƽӷ������㣬��¼���
//	ControlUnit(tobeOperated, numbers, pows, m, M);
//
//	//�����ʽ��
//	infoCollector(m, M, destm, destM, pows);
//	for (mi = 0; destm[mi] != 0; mi++);
//	for (Mi = 0; destM[Mi] != 0; Mi++);
//
//
//	if (mi == 0)//����ʽ����
//	{
//		printf("NO\n");
//	}
//	else
//	{
//		printf("YES\n");
//	}
//	//β����
//	free(tobeOperated); free(m); free(M); free(destm); free(destM);
//	return 0;
//}