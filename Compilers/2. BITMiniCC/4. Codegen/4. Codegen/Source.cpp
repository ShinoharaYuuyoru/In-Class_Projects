#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stack>

using namespace std;

#define strLength 512

typedef struct Node
{
	int	Depth;
	string type;
	string value;
}tokenNode;

tokenNode TEMPTOKEN;
vector<tokenNode> theTree;
int TreePtr = 0;

typedef struct OP
{
	string para;
	string op;
}OP;
stack<OP> OPStack;
OP TEMP;

string IdTemp;
string OpTemp;

FILE *TokenF;	// Token File
FILE *AsmF;	// Tree File

char IOBuffer[strLength];		// The IO Buffer
int checkDepth = 0;

int isARG = 1;	// Check the variable is the argument or not. 1 is argument, 0 is a variable.
int isInt = 0;	// Check the type is int or not. *** NOW WE JUST SOLVED INT SITUATION. ***

void readToken();
void codeGenerate();
void PrePrint();
void PROGRAM();
void FUNCTIONS();
void FUNLIST();
void FUNCTION();
void TYPE();
void TKN_ID();
void TKN_LP();
void ARGS();
void TKN_RP();
void FUNC_BODY();
void FARGS();
void ALIST();
void TKN_COMMA();
void TKN_LB();
void STMTS();
void TKN_RB();
void STMT();
void EXPR_STMT();
void RET_STMT();
void ASSIGN_STMT();
void EXPR();
void TKN_SEMICOLON();
void TKN_KW_RET();
void TERM();
void TLIST();
void FACTOR();
void FLIST();
void TKN_PLUS();
void TKN_INT();
void TKN_EQUAL();
void Calculate();
void EndPrint();

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("argc Error!\n");

		return 1;
	}

	TokenF = fopen(argv[1], "rt");
	AsmF = fopen(argv[2], "wt");

	readToken();

	codeGenerate();

	fclose(TokenF);
	fclose(AsmF);

	return 0;
}

/* Print the *.asm declaration at the start. */
void PrePrint()
{
	fprintf(AsmF, ".386\n");
	fprintf(AsmF, ".model\tflat,stdcall\n");
	fprintf(AsmF, ".data\n");//不支持全局变量
	fprintf(AsmF, ".code\n");
}

/* Read Token lines. */
void readToken()
{
	int spaceNum = 0;	// 2 space is a depth
	char tempType[strLength] = { '\0' };
	char tempValue[strLength] = { '\0' };

	while (1)
	{
		TEMPTOKEN.Depth = 0;
		TEMPTOKEN.type = "";
		TEMPTOKEN.value = "";
		tempType[0] = '\0';
		tempValue[0] = '\0';

		fgets(IOBuffer, strLength, TokenF);

		if (strcmp(IOBuffer, "</ParserTree>\n") == 0)	// END
		{
			TEMPTOKEN.Depth = spaceNum / 2;
			TEMPTOKEN.type = "";
			TEMPTOKEN.value = "";

			break;
		}

		// Count space numbers
		int i = 0;
		for (i = 0;;i++)
		{
			if (IOBuffer[i] == ' ')
			{
				continue;
			}
			else
			{
				break;
			}
		}
		if (i == 0)
		{
			/*
			* If the tree is valid, the i must bigger than 0, or it is invalid.
			* When the i is 0, and we already know that this line is not the endline(\n at the end of the tree *.xml file),
			* so this line must be a useless line, like declaration in a *.xml file.
			*/

			TEMPTOKEN.Depth = 0;
			TEMPTOKEN.type = "DECLARATION OF XML";
			TEMPTOKEN.value = "DECLARATION OF XML";

			continue;
		}
		else
		{
			spaceNum = i;
		}
		TEMPTOKEN.Depth = spaceNum / 2;

		// Get the type
		if (IOBuffer[i] == '<')
		{
			i++;
			int j = 0;
			for (;;i++)
			{
				if (IOBuffer[i] == '>')
				{
					tempType[j] = '\0';

					break;
				}
				else
				{
					tempType[j] = IOBuffer[i];
					j++;
				}
			}

			// Skip the <xxx /> tokens.
			if (IOBuffer[i - 1] == '/'&&IOBuffer[i - 2] == ' ')
			{
				continue;
			}
		}
		else
		{
			printf("Error! Invalid token!\n");

			exit(1);
		}
		TEMPTOKEN.type = tempType;

		i++;
		if (IOBuffer[i] == '\n')
		{
			TEMPTOKEN.value = "";
		}
		else
		{
			// Get the value
			int j = 0;
			for (;;i++)
			{
				if (IOBuffer[i] == '<')
				{
					tempValue[j] = '\0';

					break;
				}
				else
				{
					tempValue[j] = IOBuffer[i];
					j++;
				}
			}
		}
		TEMPTOKEN.value = tempValue;

		theTree.push_back(TEMPTOKEN);
	}
}

/* Code Generate. Main. */
void codeGenerate()
{
	PrePrint();

	PROGRAM();

	EndPrint();
}

/* PROGRAM	->	FUNCTIONS */
void PROGRAM()
{
	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	FUNCTIONS();

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/PROGRAM")
	{
		TreePtr++;
	}

	checkDepth--;
}

/* FUNCTIONS	->	FUNCTION	FUNLIST */
void FUNCTIONS()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	FUNCTION();
	if (theTree[TreePtr + 1].type == "FUNLIST")
	{
		FUNLIST();
	}

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/FUNCTIONS")
	{
		TreePtr++;
	}

	checkDepth--;
}

/* FUNLIST	->	FUNCTION	FUNLIST	|	e */
void FUNLIST()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	while (1)
	{
		FUNCTION();

		if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/FUNLIST")
		{
			TreePtr++;

			break;
		}
	}

	checkDepth--;
}

/* FUNCTION	->	TYPE	TKN_ID	TKN_LP	ARGS	TKN_RP	FUNC_BODY */
void FUNCTION()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	TYPE();
	TKN_ID();
	fprintf(AsmF, "%s\tproc\tC", IdTemp.c_str());
	TKN_LP();
	ARGS();
	TKN_RP();
	fprintf(AsmF, "\n");

	isARG = 0;
	FUNC_BODY();

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/FUNCTION")
	{
		TreePtr++;
	}

	checkDepth--;
}

/* TYPE	->	TKN_INT */
void TYPE()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	TKN_INT();

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/TYPE")
	{
		TreePtr++;
	}

	checkDepth--;
}

/*
	TKN_ID
	Print the ID value
	FINAL SYMBOL
*/
void TKN_ID()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	IdTemp = theTree[TreePtr].value;

	checkDepth--;
}

/*
	TKN_LP
	Print left bracket
	FINAL SYMBOL
*/
void TKN_LP()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	checkDepth--;
}

/* ARGS	->	FARGS	ALIST	|	e */
void ARGS()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	FARGS();
	if (theTree[TreePtr + 1].type == "ALIST")
	{
		ALIST();
	}

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/ARGS")
	{
		TreePtr++;
	}

	checkDepth--;
}

/*
	TKN_RP
	Print right bracket
	FINAL SYMBOL
*/
void TKN_RP()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	checkDepth--;
}

/* FUNC_BODY	->	TKN_LB	STMTS	TKN_RB */
void FUNC_BODY()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	TKN_LB();
	STMTS();
	TKN_RB();

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/FUNC_BODY")
	{
		TreePtr++;
	}

	checkDepth--;
}

/* FARGS	->	TYPE	TKN_ID */
void FARGS()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	TYPE();
	TKN_ID();
	if (isARG == 1 && isInt == 1)
	{
		fprintf(AsmF, "\t%s:DWORD", theTree[TreePtr].value.c_str());
	}
	else
	{
		if (isARG == 0 && isInt == 1)
		{
			fprintf(AsmF, "\tlocal\t%s:DWORD", theTree[TreePtr].value.c_str());
		}
	}

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/FARGS")
	{
		TreePtr++;
	}

	checkDepth--;
}

/* ALIST	->	TKN_COMMA	FARGS	ALIST	|	e */
void ALIST()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	while (1)
	{
		TKN_COMMA();
		FARGS();

		if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/ALIST")
		{
			TreePtr++;

			break;
		}
	}

	checkDepth--;
}

/*
	TKN_COMMA
	Print a comma
	FINAL SYMBOL
*/
void TKN_COMMA()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	fprintf(AsmF, ",");

	checkDepth--;
}

/*
	TKN_LB
	Print left big bracket
	FINAL SYMBOL
*/
void TKN_LB()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	checkDepth--;
}

/* STMTS	->	STMT	STMTS	|	e */
void STMTS()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	while (1)
	{
		STMT();

		if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/STMTS")
		{
			TreePtr++;

			break;
		}
	}

	checkDepth--;
}

/*
	TKN_RB
	Print left big bracket
	FINAL_SYMBOL
*/
void TKN_RB()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	checkDepth--;
}

/* STMT	->	EXPR_STMT	|	RET_STMT	|	ASSIGN_STMT */
void STMT()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	if (theTree[TreePtr + 1].type == "RET_STMT")
	{
		RET_STMT();
	}
	else if (theTree[TreePtr + 1].type == "EXPR_STMT")
	{
		EXPR_STMT();
	}
	else if (theTree[TreePtr + 1].type == "ASSIGN_STMT")
	{
		ASSIGN_STMT();
	}

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/STMT")
	{
		TreePtr++;
	}

	checkDepth--;
}

/* EXPR_STMT	->	EXPR	TKN_SEMICOLON */
void EXPR_STMT()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	EXPR();
	TKN_SEMICOLON();
	Calculate();

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/EXPR_STMT")
	{
		TreePtr++;
	}

	checkDepth--;
}

/* RET_STMT	->	TKN_KW_RET	EXPR_STMT */
void RET_STMT()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	TKN_KW_RET();
	EXPR_STMT();
	fprintf(AsmF, "\tret\n");

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/RET_STMT")
	{
		TreePtr++;
	}

	checkDepth--;
}

/* ASSIGN_STMT	->	TKN_ID	TKN_EQUAL	EXPR_STMT */
void ASSIGN_STMT()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	TKN_ID();
	TKN_EQUAL();

	TEMP.para = IdTemp;
	TEMP.op = OpTemp;
	OPStack.push(TEMP);

	EXPR_STMT();

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/ASSIGN_STMT")
	{
		TreePtr++;
	}

	checkDepth--;
}

/* EXPR	->	TERM	TLIST */
void EXPR()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	TERM();
	if (theTree[TreePtr + 1].type == "TLIST")
	{
		TLIST();
	}

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/EXPR")
	{
		TreePtr++;
	}

	checkDepth--;
}

/*
	TKN_SEMICOLON
	Print a semicolon
	FINAL SYMBOL
*/
void TKN_SEMICOLON()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	checkDepth--;
}

/*
	TKN_KW_RET
	Print Keyword return
	FINAL SYMBOL
*/
void TKN_KW_RET()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	checkDepth--;
}

/* TERM	->	FACTOR	FLIST */
void TERM()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	FACTOR();
	TEMP.para = IdTemp;
	OPStack.push(TEMP);

	if (theTree[TreePtr + 1].type == "FLIST")
	{
		FLIST();
	}

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/TERM")
	{
		TreePtr++;
	}

	checkDepth--;
}

/*
	TLIST	->	TKN_PLUS	TERM	TLIST	|	e
	*****	This just solved + operator	*****
*/
void TLIST()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	while (1)
	{
		TKN_PLUS();
		TERM();

		if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/TLIST")
		{
			TreePtr++;

			break;
		}
	}

	checkDepth--;
}

/* FACTOR	->	TKN_ID */
void FACTOR()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}
	
	TKN_ID();

	if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/FACTOR")
	{
		TreePtr++;
	}

	checkDepth--;
}

/* FLIST	->	TKN_PLUS	FACTOR	FLIST	|	e */
void FLIST()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	while (1)
	{
		TKN_PLUS();
		FACTOR();

		TEMP.para = IdTemp;
		TEMP.op = OpTemp;
		OPStack.push(TEMP);

		if (checkDepth == theTree[TreePtr + 1].Depth&&theTree[TreePtr + 1].type == "/FLIST")
		{
			TreePtr++;

			break;
		}
	}

	checkDepth--;
}

/*
	TKN_PLUS
	Print plus symbol
	FINAL SYMBOL
*/
void TKN_PLUS()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	OpTemp = "+";

	checkDepth--;
}

/*
	TKN_INT
	Print int keyword
	FINAL SYMBOL
*/
void TKN_INT()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	isInt = 1;

	checkDepth--;
}

/*
	TKN_EQUAL
	Print equal symbol
*/
void TKN_EQUAL()
{
	TreePtr++;

	checkDepth++;
	if (checkDepth != theTree[TreePtr].Depth)
	{
		printf("Tree Depth Error!\n");
		exit(1);
	}

	OpTemp = "=";

	checkDepth--;
}

/* Calculate */
void Calculate()
{
	int flag = 0;
	while (OPStack.empty() != 1)
	{
		OP paraB;
		paraB = OPStack.top();
		OPStack.pop();
		if (OPStack.empty() == 1)
		{
			break;
		}
		else
		{
			OP paraA;
			paraA = OPStack.top();

			if (paraB.op == "+")
			{
				if (flag == 0)
				{
					fprintf(AsmF, "mov eax, %s\n", paraB.para.c_str());
				}
				fprintf(AsmF, "add eax, %s\n", paraA.para.c_str());
			}
			else if (paraA.op == "=")
			{
				fprintf(AsmF, "mov %s, eax\n", paraA.para.c_str());
			}
		}
		
		flag++;
	}
}

/* Print the *.asm declaration at the end. */
void EndPrint()
{
	fprintf(AsmF, "end\tmain");
}