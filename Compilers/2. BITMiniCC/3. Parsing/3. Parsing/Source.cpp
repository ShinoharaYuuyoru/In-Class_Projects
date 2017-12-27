#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#define strLength 512

using namespace std;

typedef struct Node
{
	//int number;
	string value;
	string type;
	//int line;
	//string valid;
}tokenNode;

vector<tokenNode> Tokens;
int tokenPTR = 0;

FILE *TokenF;	// Token File
FILE *TreeF;	// Tree File

char IOBuffer[strLength];		// The IO Buffer
char Value[strLength];	// The Value get from Token File
char Type[strLength];	// The Type get from Token File

int	spacesNum = 0;			// The number of space, 1 means 2 spaces

void readToken();
void PROGRAM();
void printSpaces();

void EXTERNAL_DECL();
void FUNCTION();
void FUNLIST();
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
void RET_STMT();
void EXPR_STMT();
void WHILE_STMT();
void IF_STMT();
void ASSIGN_STMT();
void LOCAL_DECL();

void EXPR();
void TKN_SEMICOLON();
void TKN_KW_RET();
void TERM();
void TLIST();
void FACTOR();
void FLIST();
void TKN_PLUS();
void TKN_MUL();
void TKN_INT();
void TKN_FLOAT();
void TKN_KW_WHILE();
void TKN_KW_IF();
void TKN_EQUAL();

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("argc Error!\n");

		return 1;
	}

	TokenF = fopen(argv[1], "rt");
	TreeF = fopen(argv[2], "wt");
	
	char xmlHead[128] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<ParserTree name=\"";
	strcat(xmlHead, argv[2]);
	char xmlHeadEnd[16] = "\">\n";
	strcat(xmlHead, xmlHeadEnd);
	fputs(xmlHead, TreeF);

	readToken();

	PROGRAM();

	fprintf(TreeF, "</ParserTree>\n");
	fclose(TokenF);
	fclose(TreeF);

	return 0;
}

/* Read Token File and get the value and type. */
void readToken()
{
	tokenNode Temp;

	while (1)
	{
		fgets(IOBuffer, strLength, TokenF);

		if (strcmp(IOBuffer, "</project>\n") == 0)		// End of xml file
		{
			break;
		}
		else
		{
			if (strcmp(IOBuffer, "    </token>\n") == 0)	// End of this Token, push it to vector
			{
				Tokens.push_back(Temp);

				continue;
			}

			if (strcmp(IOBuffer, "    <token>\n") == 0)		// Get this Token
			{
				int InfoFlag = 1;
				for (InfoFlag = 1;InfoFlag <= 5;InfoFlag++)
				{
					fgets(IOBuffer, strLength, TokenF);

					if (InfoFlag == 2 || InfoFlag == 3)
					{// Get the Node Info
						int i = 0;
						for (i = 0;;i++)
						{
							if (IOBuffer[i] == '>')
							{
								break;
							}
						}
						i++;
						int j = i;
						for (j = i;;j++)
						{
							if (IOBuffer[j] == '<')
							{
								break;
							}
						}
						j--;

						int k = 0;
						char Info[strLength];
						for (k = 0;i <= j;k++, i++)	// Copy the Info
						{
							Info[k] = IOBuffer[i];
						}
						Info[k] = '\0';

						if (InfoFlag == 2)
						{
							Temp.value = Info;
						}
						if (InfoFlag == 3)
						{
							Temp.type = Info;
						}
					}
					else
					{
						continue;
					}
				}
			}
		}
	}

	return;
}

/*
	Start the Parser
	PROGRAM	->	EXTERNAL_DECL
*/
void PROGRAM()
{
	spacesNum++;					// Starts from 1
	printSpaces();
	fprintf(TreeF, "<PROGRAM>\n");

	EXTERNAL_DECL();

	printSpaces();
	fprintf(TreeF, "</PROGRAM>\n");
	spacesNum--;					// End at 0

	if (strcmp(Tokens[tokenPTR].type.c_str(), "#") == 0)	// End of parsing
	{
		printf("Parsing Completed.\n");

		return;
	}
	else
	{
		printf("PROGRAM ERROR!\n");

		exit(1);
	}
}

/* Print the spaces in front of the label */
void printSpaces()
{
	int i = 0;
	for (i = 0;i < spacesNum;i++)
	{
		fprintf(TreeF, "  ");
	}

	return;
}

/* 
	External Declare
	EXTERNAL_DECL	->	DECLARES	|	FUNCTIONS

	*****	But DECLARES has not been solved!	*****
	*****	So this fuction is equal to FUNCTIONS() now!	*****
	*****	This means this compile can't solve declaration out of the functions.	*****
	FUNCTIONS	->	FUNCTION	FLIST
*/
void EXTERNAL_DECL()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<FUNCTIONS>\n");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		FUNCTION();
		FUNLIST();
	}
	else
	{
		printf("FUNCTIONS ERROR!\n");

		exit(1);
	}

	printSpaces();
	fprintf(TreeF, "</FUNCTIONS>\n");
	spacesNum--;
}

/*
	FUNCTION
	FUNCTION	->	TYPE	TKN_ID	TKN_LP	ARGS	TKN_RP	FUNC_BODY
*/
void FUNCTION()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<FUNCTION>\n");

	TYPE();
	TKN_ID();
	TKN_LP();
	ARGS();
	TKN_RP();
	FUNC_BODY();
	
	printSpaces();
	fprintf(TreeF, "</FUNCTION>\n");
	spacesNum--;
}

/*
	FUNLIST
	FUNLIST	->	FUNCTION	FUNLIST	|	e
*/
void FUNLIST()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<FUNLIST>\n");

		while (1)
		{
			FUNCTION();

			if (strcmp(Tokens[tokenPTR].type.c_str(), "#") == 0)
			{
				break;
			}
			else
			{
				printf("FUNLIST ERROR!\n");

				exit(1);
			}
		}

		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<FUNLIST />\n");
		spacesNum--;

		printSpaces();
		fprintf(TreeF, "</FUNLIST>\n");
		spacesNum--;
	}
	else
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<FUNLIST />\n");
		spacesNum--;
	}
}

/*
	TYPE
	TYPE	->	TKN_INT	|	TKN_FLOAT
*/
void TYPE()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<TYPE>\n");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		if (strcmp(Tokens[tokenPTR].value.c_str(), "int") == 0)
		{
			TKN_INT();
		}
		else if (strcmp(Tokens[tokenPTR].value.c_str(), "float") == 0)
		{
			TKN_FLOAT();
		}
		else
		{
			printf("Type Undefined. ERROR!\n");

			exit(1);
		}
	}
	else
	{
		printf("TYPE ERROR!\n");

		exit(1);
	}

	printSpaces();
	fprintf(TreeF, "</TYPE>\n");
	spacesNum--;
}

/*
	TKN_ID
	Print the ID value
	FINAL SYMBOL
*/
void TKN_ID()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<identifier>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "identifier") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_ID ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</identifier>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	TKN_LP
	Print left bracket
	FINAL SYMBOL
*/
void TKN_LP()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<separator>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_LP ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</separator>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	ARGS
	ARGS	->	FARGS	ALIST	|	e
*/
void ARGS()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<ARGS>\n");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		FARGS();
		ALIST();
	}
	else
	{
		if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0 && strcmp(Tokens[tokenPTR].value.c_str(), ")") == 0)	// e
		{
			printSpaces();
			fprintf(TreeF, "</ARGS>\n");
			spacesNum--;

			return;
		}
		else
		{
			printf("ARGS ERROR!\n");

			exit(1);
		}
	}

	printSpaces();
	fprintf(TreeF, "</ARGS>\n");
	spacesNum--;
}

/*
	TKN_RP
	Print right bracket
	FINAL SYMBOL
*/
void TKN_RP()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<separator>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_RP ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</separator>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	FUNC_BODY
	FUNC_BODY	->	TKN_LB	STMTS	TKN_RB
*/
void FUNC_BODY()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<FUNC_BODY>\n");

	TKN_LB();
	STMTS();
	TKN_RB();

	printSpaces();
	fprintf(TreeF, "</FUNC_BODY>\n");
	spacesNum--;
}

/*
	FARGS
	FARGS	->	TYPE	TKN_ID
*/
void FARGS()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<FARGS>\n");

	TYPE();
	TKN_ID();

	printSpaces();
	fprintf(TreeF, "</FARGS>\n");
	spacesNum--;
}

/*
	ALIST
	ALIST	->	TKN_COMMA	FARGS	ALIST	|	e
*/
void ALIST()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<ALIST>\n");

		while (1)
		{
			TKN_COMMA();
			FARGS();

			if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0 && strcmp(Tokens[tokenPTR].value.c_str(), ")") == 0)	// e
			{
				break;
			}
			else
			{
				printf("ALIST ERROR!\n");

				exit(1);
			}
		}

		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<ALIST />\n");
		spacesNum--;

		printSpaces();
		fprintf(TreeF, "</ALIST>\n");
		spacesNum--;
	}
	else
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<ALIST />\n");
		spacesNum--;
	}
}

/*
	TKN_COMMA
	Print a comma
	FINAL SYMBOL
*/
void TKN_COMMA()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<separator>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_COMMA ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</separator>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	TKN_LB
	Print left big bracket
	FINAL SYMBOL
*/
void TKN_LB()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<separator>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_LB ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</separator>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	STMTS
	STMTS	->	STMT	STMTS	|	e
*/
void STMTS()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") != 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<STMTS>\n");

		while (1)
		{
			STMT();

			if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0)
			{
				break;
			}
		}

		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<STMTS />\n");
		spacesNum--;

		printSpaces();
		fprintf(TreeF, "</STMTS>\n");
		spacesNum--;
	}
	else
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<STMTS />\n");
		spacesNum--;
	}
}

/*
	TKN_RB
	Print left big bracket
	FINAL_SYMBOL
*/
void TKN_RB()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<separator>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_RB ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</separator>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	STMT
	STMT	->	EXPR_STMT	|	RET_STMT	|	WHILE_STMT	|	IF_STMT	|	ASSIGN_STMT	|	LOCAL_DECL
*/
void STMT()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<STMT>\n");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		if (strcmp(Tokens[tokenPTR].value.c_str(), "return") == 0)
		{
			RET_STMT();
		}
		if (strcmp(Tokens[tokenPTR].value.c_str(), "while") == 0)
		{
			WHILE_STMT();
		}
		if (strcmp(Tokens[tokenPTR].value.c_str(), "if") == 0)
		{
			IF_STMT();
		}
		if (strcmp(Tokens[tokenPTR].value.c_str(), "int") == 0||
			strcmp(Tokens[tokenPTR].value.c_str(), "float") == 0)
		{
			LOCAL_DECL();
		}
	}
	else
	{
		if (strcmp(Tokens[tokenPTR].type.c_str(), "identifier") == 0)
		{
			if (strcmp(Tokens[tokenPTR+1].type.c_str(), "operator") == 0 && strcmp(Tokens[tokenPTR+1].value.c_str(), "=") == 0)
			{
				ASSIGN_STMT();
			}
			else
			{
				if (strcmp(Tokens[tokenPTR + 1].value.c_str(), "=") != 0)
				{
					EXPR_STMT();
				}
			}
		}
		else
		{
			printf("STMT ERROR!\n");

			exit(1);
		}
	}

	printSpaces();
	fprintf(TreeF, "</STMT>\n");
	spacesNum--;
}

/*
	RET_STMT
	RET_STMT	->	TKN_KW_RET	EXPR_STMT
*/
void RET_STMT()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<RET_STMT>\n");

	TKN_KW_RET();
	EXPR_STMT();

	printSpaces();
	fprintf(TreeF, "</RET_STMT>\n");
	spacesNum--;
}

/*
	EXPR_STMT
	EXPR_STMT	->	EXPR	TKN_SEMICOLON
*/
void EXPR_STMT()
{
	if ((strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0&& strcmp(Tokens[tokenPTR].value.c_str(), "(") == 0)|| strcmp(Tokens[tokenPTR].type.c_str(), "identifier") == 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<EXPR_STMT>\n");

		EXPR();
		TKN_SEMICOLON();

		printSpaces();
		fprintf(TreeF, "</EXPR_STMT>\n");
		spacesNum--;
	}
	else
	{
		printf("EXPR_STMT ERROR!\n");

		exit(1);
	}
}

/*
	WHILE_STMT
	WHILE_STMT	->	TKN_KW_WHILE	TKN_LP	EXPR	TKN_RP	TKN_LB	STMTS	TKN_RB
	*****	Must have { ... }	*****
*/
void WHILE_STMT()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0 && strcmp(Tokens[tokenPTR].value.c_str(), "while") == 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<WHILE_STMT>\n");

		TKN_KW_WHILE();
		TKN_LP();
		EXPR();
		TKN_RP();
		TKN_LB();
		STMTS();
		TKN_RB();

		printSpaces();
		fprintf(TreeF, "</WHILE_STMT>\n");
		spacesNum--;
	}
	else
	{
		printf("WHILE_STMT ERROR!\n");

		exit(1);
	}
}

/*
	IF_STMT
	IF_STMT	->	TKN_KW_IF	TKN_LP	EXPR	TKN_RP	TKN_LB	TKN_STMTS	TKN_RB
*/
void IF_STMT()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0 && strcmp(Tokens[tokenPTR].value.c_str(), "if") == 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<IF_STMT>\n");

		TKN_KW_IF();
		TKN_LP();
		EXPR();
		TKN_RP();
		TKN_LB();
		STMTS();
		TKN_RB();

		printSpaces();
		fprintf(TreeF, "</IF_STMT>\n");
		spacesNum--;
	}
	else
	{
		printf("WHILE_STMT ERROR!\n");

		exit(1);
	}
}

/*
	ASSIGN_STMT
	ASSIGN_STMT	->	TKN_ID	TKN_EQUAL	EXPR_STMT
*/
void ASSIGN_STMT()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "identifier") == 0 && strcmp(Tokens[tokenPTR + 1].type.c_str(), "operator") == 0 && strcmp(Tokens[tokenPTR + 1].value.c_str(), "=") == 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<ASSIGN_STMT>\n");

		TKN_ID();
		TKN_EQUAL();
		EXPR_STMT();

		printSpaces();
		fprintf(TreeF, "</ASSIGN_STMT>\n");
		spacesNum--;
	}
	else
	{
		printf("ASSIGN_STMT ERROR!\n");
		
		exit(1);
	}
}

/*
	LOCAL_DECL
	LOCAL_DECL	->	TYPE	TKN_ID	TKN_SEMICOLON
*/
void LOCAL_DECL()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		TYPE();
		TKN_ID();
		TKN_SEMICOLON();
	}
	else
	{
		printf("LOCAL_DECL ERROR!\n");

		exit(1);
	}
}

/*
	EXPR
	EXPR	->	TERM	TLIST
*/
void EXPR()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "identifier") == 0 || strcmp(Tokens[tokenPTR].type.c_str(), "operator") == 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<EXPR>\n");

		TERM();
		TLIST();

		printSpaces();
		fprintf(TreeF, "</EXPR>\n");
		spacesNum--;
	}
	else
	{
		printf("EXPR ERROR!\n");

		exit(1);
	}
}

/*
	TKN_SEMICOLON
	Print a semicolon
	FINAL SYMBOL
*/
void TKN_SEMICOLON()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<separator>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_KW_RET ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</separator>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	TKN_KW_RET
	Print Keyword return
	FINAL SYMBOL
*/
void TKN_KW_RET()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<keyword>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_KW_RET ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</keyword>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	TERM
	TERM	->	FACTOR	FLIST
*/
void TERM()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0 || strcmp(Tokens[tokenPTR].type.c_str(), "identifier") == 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<TERM>\n");

		FACTOR();
		FLIST();

		printSpaces();
		fprintf(TreeF, "</TERM>\n");
		spacesNum--;
	}
	else
	{
		printf("TERM ERROR!\n");

		exit(1);
	}
}

/*
	TLIST
	TLIST	->	TKN_PLUS	TERM	TLIST	|	e
	*****	This just solved + operator	*****
*/
void TLIST()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "operator") == 0 && strcmp(Tokens[tokenPTR].value.c_str(), "+") == 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<TLIST>\n");

		while (1)
		{
			TKN_PLUS();
			TERM();

			if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0 && strcmp(Tokens[tokenPTR].value.c_str(), ";") == 0)
			{
				break;
			}
			else
			{
				printf("TLIST ERROR!\n");

				exit(1);
			}
		}

		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<TLIST />\n");
		spacesNum--;

		printSpaces();
		fprintf(TreeF, "</TLIST>\n");
		spacesNum--;
	}
	else
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<TLIST />\n");
		spacesNum--;
	}
}

/*
	FACTOR
	FACTOR	->	TKN_LP	EXPR	TKN_RP	|	TKN_ID
*/
void FACTOR()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<FACTOR>\n");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0 && strcmp(Tokens[tokenPTR].value.c_str(), "(") == 0)
	{
		TKN_LP();
		EXPR();
		TKN_RP();
	}
	else
	{
		if (strcmp(Tokens[tokenPTR].type.c_str(), "identifier") == 0)
		{
			TKN_ID();
		}
		else
		{
			printf("FACTOR ERROR!\n");

			exit(1);
		}
	}

	printSpaces();
	fprintf(TreeF, "</FACTOR>\n");
	spacesNum--;
}

/*
	FLIST
	FLIST	->	TKN_MUL	FACTOR	FLIST	|	e
*/
void FLIST()
{
	if (strcmp(Tokens[tokenPTR].type.c_str(), "operator") == 0 && strcmp(Tokens[tokenPTR].value.c_str(), "*") == 0)
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<FLIST>");

		while (1)
		{
			TKN_MUL();
			FACTOR();

			if (strcmp(Tokens[tokenPTR].type.c_str(), "separator") == 0 && strcmp(Tokens[tokenPTR].value.c_str(), ";") == 0)
			{
				break;
			}
			else if (strcmp(Tokens[tokenPTR].type.c_str(), "operator") == 0 && strcmp(Tokens[tokenPTR].value.c_str(), "+") == 0)
			{
				break;
			}
			else
			{
				printf("FLIST ERROR!\n");

				exit(1);
			}
		}

		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<FLIST />\n");
		spacesNum--;

		printSpaces();
		fprintf(TreeF, "</FLIST>\n");
		spacesNum--;
	}
	else
	{
		spacesNum++;
		printSpaces();
		fprintf(TreeF, "<FLIST />\n");
		spacesNum--;
	}
}

/*
	TKN_PLUS
	Print plus symbol
	FINAL SYMBOL
*/
void TKN_PLUS()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<operator>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "operator") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_PLUS ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</operator>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	TKN_MUL
	Print multipation symbol
	FINAL SYMBOL
*/
void TKN_MUL()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<operator>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "operator") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_MUL ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</operator>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	TKN_INT
	Print int keyword
	FINAL SYMBOL
*/
void TKN_INT()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<keyword>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_MUL ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</keyword>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	TKN_FLOAT
	Print float keyword
	FINAL SYMBOL
*/
void TKN_FLOAT()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<keyword>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_FLOAT ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</keyword>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	TKN_WHILE
	Print while keyword
	FINAL SYMBOL
*/
void TKN_KW_WHILE()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<keyword>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_WHILE ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</keyword>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	TKN_IF
	Print if keyword
	FINAL SYMBOL
*/
void TKN_KW_IF()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<keyword>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "keyword") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_IF ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</keyword>\n");
	spacesNum--;

	tokenPTR++;
}

/*
	TKN_EQUAL
	Print equal symbol
*/
void TKN_EQUAL()
{
	spacesNum++;
	printSpaces();
	fprintf(TreeF, "<operator>");

	if (strcmp(Tokens[tokenPTR].type.c_str(), "operator") == 0)
	{
		fprintf(TreeF, Tokens[tokenPTR].value.c_str());
	}
	else
	{
		printf("TKN_EQUAL ERROR!\n");

		exit(1);
	}

	//printSpaces();
	fprintf(TreeF, "</operator>\n");
	spacesNum--;

	tokenPTR++;
}