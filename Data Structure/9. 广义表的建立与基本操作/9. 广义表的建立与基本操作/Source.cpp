#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//typedef char AtomType;
//
//typedef enum 
//{
//	ATOM,LIST
//}ElemTag;
//
//typedef struct GLNode
//{
//	ElemTag Tag;
//	union
//	{
//		AtomType Atom;
//
//		struct
//		{
//			struct GLNode *hp, *tp;
//		}ptr;
//	};
//}*GList;

char Line[1000];
int Length;
int OP;

void GetHead();
void GetTail();

int main()
{
	scanf("%s", Line);

	while (1)
	{
		scanf("%d", &OP);

		printf("generic list: %s\n", Line);
		Length = strlen(Line);

		if (Length == 2 || Length == 1)
		{
			break;
		}

		if (OP == 1)//Get Head
		{
			GetHead();
		}
		else//Get Tail
		{
			GetTail();
		}
	}

	return 0;
}

void GetHead()
{
	int CutStart = 1;
	int CutEnd = 0;
	int LeftBC = 0;
	char ListTemp[1000];
	int ListTempC = 0;

	printf("destroy tail\n");
	printf("free list node\n");

	memset(ListTemp, 0, sizeof(ListTemp));

	if (Line[CutStart] == '(')
	{
		LeftBC++;

		for (CutEnd = CutStart + 1;CutEnd < Length;CutEnd++)
		{
			if (Line[CutEnd] == '(')
			{
				LeftBC++;
			}
			if (Line[CutEnd] == ')')
			{
				LeftBC--;

				if (LeftBC == 0)
				{
					break;
				}
			}
		}

		for (ListTempC = 0;CutStart <= CutEnd;CutStart++, ListTempC++)
		{
			ListTemp[ListTempC] = Line[CutStart];
		}
	}
	else
	{
		ListTemp[0] = Line[CutStart];
	}

	strcpy(Line, ListTemp);

	return;
}

void GetTail()
{
	int CutStart = 0;
	int CutEnd = Length - 2;
	int RightBC = 0;
	char ListTemp[1000];
	int ListTempC = 0;

	printf("free head node\n");
	printf("free list node\n");

	memset(ListTemp, 0, sizeof(ListTemp));

	int LeftBC = 0;
	int CE = 0;

	if (Line[1] == '(')
	{
		for (CE = 1;CE < Length;CE++)
		{
			if (Line[CE] == '(')
			{
				LeftBC++;
			}
			if (Line[CE] == ')')
			{
				LeftBC--;

				if (LeftBC == 0)
				{
					break;
				}
			}
		}

		if (CutStart == CutEnd)
		{
			ListTemp[0] = '(';
			ListTemp[1] = ')';

			strcpy(Line, ListTemp);

			return;
		}
	}
	else
	{
		CE = 1;
	}

	CutStart = CE + 2;

	for (ListTempC = 1;CutStart <= CutEnd;CutStart++, ListTempC++)
	{
		ListTemp[ListTempC] = Line[CutStart];
	}
	ListTemp[0] = '(';
	ListTemp[ListTempC] = ')';

	strcpy(Line, ListTemp);

	return;
}