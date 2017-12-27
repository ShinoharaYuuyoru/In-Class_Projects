#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <regex>

using namespace std;

#define state_Default 0
#define state_Identifier 1
#define state_Operator 2
#define state_Separator 3
#define state_Number 4
#define state_String 5
#define state_Error 9

map<string, bool> key_map;
map<string, bool> opr_map;

typedef struct Node
{
	int number;
	string value;
	/*type:
	0:keyword
	1:indenfitier
	2:operator
	3:separator
	4:number, integer(const_int)
	5:string
	6:number, float(const_float)
	7:number, oct(const_oct)
	8:number, hex(const_hex)
	*/
	int type;
	int line;
	bool valid;
}tokenNode;

FILE *SrcCodeF;
FILE *TokenF;
string SrcCode = "";

int lineCounter = 1;
int wordCounter = 1;
vector<tokenNode> Tokens;
int lastState = 0;
char currentChar = '\0';
int currentState = 0;

string Idt;	//Identifier buffer
string Opr;	//Operator buffer
string Num;	//Number buffer
string Str;	//String buffer

void ReadSrctoStr();
void Scanner();
void getCurrentState();
void belongstoState();
void createIdtToken();
void createOprToken();
void createSepToken();
void createNumToken();
void createStrToken();
void init_keymap();
void init_oprmap();
bool is_keyword(string Idt);
bool is_operator(string Opr);
bool is_separator(char currentChar);
bool is_int(string Num);
bool is_float(string Num);
bool is_oct(string Num);
bool is_hex(string Num);
void printToken();

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Error: argc error." << endl;

		exit(1);
	}

	SrcCodeF = fopen(argv[1], "rt");
	TokenF = fopen(argv[2], "wt");	//Need change output file name.
	if (SrcCodeF == NULL)
	{
		cout << "Error: Source code file not exists." << endl;

		exit(1);
	}
	if (TokenF == NULL)
	{
		cout << "Error: Open/Create Token xml file error." << endl;

		exit(1);
	}

	ReadSrctoStr();

	/*Output the xml head*/
	char tokenHead[128] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<project name=\"";
	strcat(tokenHead, argv[2]);
	char Headend[32] = "\">\n  <tokens>\n";
	strcat(tokenHead, Headend);
	fputs(tokenHead, TokenF);

	Scanner();

	printToken();

	/*Output the xml tail*/
	char tokenTail[32] = "  </tokens>\n</project>\n";
	fputs(tokenTail, TokenF);

	fclose(SrcCodeF);
	fclose(TokenF);

	cout << "2. Scanner finished!" << endl;
}

/*Read the source code to SrcCode string.*/
void ReadSrctoStr()
{
	int i = 0;
	char temp;

	while ((temp = fgetc(SrcCodeF)) != EOF)
	{
		SrcCode.push_back(temp);
	}
}

/*Scanner*/
void Scanner()
{
	init_keymap();
	init_oprmap();

	int SrcLength = SrcCode.size();
	int codePtr = 0;

	for (;codePtr < SrcLength;codePtr++)
	{
		currentChar = SrcCode[codePtr];
		
		getCurrentState();

		switch (currentState)
		{
		case state_Default:
		{
			createIdtToken();
			createOprToken();
			createNumToken();
			createStrToken();
			createSepToken();

			if (currentChar == '\n')
			{
				lineCounter++;
			}
			break;
		}
		case state_Identifier:
		{
			createOprToken();
			createSepToken();

			Idt.push_back(currentChar);
			break;
		}
		case state_Operator:
		{
			createIdtToken();
			createSepToken();
			createNumToken();

			Opr.push_back(currentChar);
			break;
		}
		case state_Separator:
		{
			createIdtToken();
			createOprToken();
			createNumToken();
			createSepToken();

			break;
		}
		case state_Number:
		{
			createSepToken();
			createOprToken();

			Num.push_back(currentChar);
			break;
		}
		case state_String:
		{
			createIdtToken();
			createOprToken();
			createNumToken();
			createSepToken();

			Str.push_back(currentChar);
			break;
		}
		case state_Error:
		{
			cout << "state Error!" << endl;
			exit(1);
			break;
		}
		}
	}
}

/*Get current state*/
void getCurrentState()
{
	belongstoState();

	switch (lastState)
	{
	case state_Default:
	{
		break;
	}
	case state_Identifier:
	{
		break;
	}
	case state_Operator:
	{
		break;
	}
	case state_Separator:
	{
		if (currentChar == '+' || currentChar == '-')
		{
			currentState = state_Number;
		}
		break;
	}
	case state_Number:
	{
		if (currentChar == '.')
		{
			currentState = state_Number;
		}
		if (currentChar >= 'A'&&currentChar <= 'Z' || currentChar >= 'a'&&currentChar <= 'z' || currentChar == '_')
		{
			if ((currentChar >= 'A' && currentChar <= 'F') || 
				currentChar == 'L' || currentChar == 'U' || currentChar == 'X' || 
				(currentChar >= 'a' && currentChar <= 'f') || 
				currentChar == 'l' || currentChar == 'u' || currentChar == 'x'
				)
			{
				currentState = state_Number;
			}
			else
			{
				currentState = state_Error;
			}
		}
		break;
	}
	case state_String:
	{
		if (currentChar == '\"' || currentChar == '\'')
		{
			currentState = state_Default;
		}
		else
		{
			if (currentChar == '\n')
			{
				currentState = state_Error;
			}
			else
			{
				currentState = state_String;
			}
		}
		break;
	}
	case state_Error:
	{
		break;
	}
	}

	lastState = currentState;
}

/*The state that current char belongs to*/
void belongstoState()
{
	if (
		currentChar == ' ' || currentChar == '\t' || currentChar == '\n'
		)
	{
		currentState = state_Default;
	}

	if (
		currentChar >= 'A'&&currentChar <= 'Z' || currentChar >= 'a'&&currentChar <= 'z' || currentChar == '_'
		)
	{
		currentState = state_Identifier;
	}

	if (
		currentChar == '+' || currentChar == '-' || currentChar == '*' ||
		currentChar == '/' || currentChar == '%' || currentChar == '<' ||
		currentChar == '=' || currentChar == '>' || currentChar == '~' ||
		currentChar == '!' || currentChar == '^' || currentChar == '&' ||
		currentChar == '|' || currentChar == '.'
		)
	{
		currentState = state_Operator;
	}

	if (
		currentChar == '{' || currentChar == '}' || currentChar == '[' ||
		currentChar == ']' || currentChar == '(' || currentChar == ')' ||
		currentChar == ';' || currentChar == ','
		)
	{
		currentState = state_Separator;
	}

	if (
		currentChar >= '0'&&currentChar <= '9'
		)
	{
		currentState = state_Number;
	}

	if (
		currentChar == '\"' || currentChar == '\''
		)
	{
		currentState = state_String;
	}
}

/*Create Identifier token*/
void createIdtToken()
{
	if (!Idt.empty())
	{
		tokenNode Temp;
		Temp.number = wordCounter;
		Temp.value = Idt;
		Temp.type = 1;
		if (is_keyword(Idt))
		{
			Temp.type = 0;
		}
		Temp.line = lineCounter;
		Temp.valid = true;

		Tokens.push_back(Temp);

		wordCounter++;
		Idt.clear();
	}
}

/*Create Operator token*/
void createOprToken()
{
	if (!Opr.empty())
	{
		int i = 0;
		while (i < Opr.length())
		{
			int j = Opr.length() - 1;
			for (;j >= i;j--)
			{
				if (is_operator(Opr.substr(i, (j - i + 1))))
				{
					tokenNode Temp;
					Temp.number = wordCounter;
					Temp.value = Opr.substr(i, (j - i + 1));
					Temp.type = 2;
					Temp.line = lineCounter;
					Temp.valid = true;

					Tokens.push_back(Temp);

					wordCounter++;

					i = j + 1;
				}
			}
		}

		Opr.clear();
	}
}

/*Create Separator token*/
void createSepToken()
{
	if (is_separator(currentChar))
	{
		tokenNode Temp;
		Temp.number = wordCounter;
		Temp.value = currentChar;
		Temp.type = 3;
		Temp.line = lineCounter;
		Temp.valid = true;
		
		Tokens.push_back(Temp);

		wordCounter++;
	}
}

/*Create Number token*/
void createNumToken()
{
	if (!Num.empty())
	{
		tokenNode Temp;
		Temp.number = wordCounter;
		Temp.value = Num;
		if (is_int(Num))
		{
			Temp.type = 4;
		}
		else if (is_float(Num))
		{
			Temp.type = 6;
		}
		else if(is_oct(Num))
		{
			Temp.type = 7;
		}
		else if (is_hex(Num))
		{
			Temp.type = 8;
		}
		else
		{
			cout << "Number Error!" << endl;
		}
		Temp.line = lineCounter;
		Temp.valid = true;

		Tokens.push_back(Temp);

		wordCounter++;
		Num.clear();
	}
}

/*Create String token*/
void createStrToken()
{
	if (!Str.empty())
	{
		tokenNode Temp;
		Temp.number = wordCounter;
		Temp.value = Str + "\"";
		Temp.type = 5;
		Temp.line = lineCounter;
		Temp.valid = true;

		Tokens.push_back(Temp);

		wordCounter++;
		Str.clear();
	}
}

/*Keyword map table*/
void init_keymap()
{
	key_map["auto"] = true;
	key_map["break"] = true;
	key_map["case"] = true;
	key_map["char"] = true;
	key_map["const"] = true;
	key_map["continue"] = true;
	key_map["default"] = true;
	key_map["do"] = true;
	key_map["double"] = true;
	key_map["else"] = true;
	key_map["enum"] = true;
	key_map["extern"] = true;
	key_map["float"] = true;
	key_map["for"] = true;
	key_map["goto"] = true;
	key_map["if"] = true;
	key_map["int"] = true;
	key_map["long"] = true;
	key_map["register"] = true;
	key_map["return"] = true;
	key_map["short"] = true;
	key_map["signed"] = true;
	key_map["sizeof"] = true;
	key_map["static"] = true;
	key_map["struct"] = true;
	key_map["switch"] = true;
	key_map["typedef"] = true;
	key_map["union"] = true;
	key_map["unsigned"] = true;
	key_map["void"] = true;
	key_map["volatile"] = true;
	key_map["while"] = true;
}

/*Operator map table*/
void init_oprmap()
{
	opr_map["++"] = true;
	opr_map["--"] = true;
	opr_map["."] = true;
	opr_map["->"] = true;
	opr_map["++"] = true;
	opr_map["--"] = true;
	opr_map["+ "] = true;
	opr_map["-"] = true;
	opr_map["!"] = true;
	opr_map["~"] = true;
	opr_map["*"] = true;
	opr_map["&"] = true;
	opr_map["*"] = true;
	opr_map["/"] = true;
	opr_map["%"] = true;
	opr_map["+"] = true;
	opr_map["-"] = true;
	opr_map["<<"] = true;
	opr_map[">>"] = true;
	opr_map["<"] = true;
	opr_map["<="] = true;
	opr_map[">"] = true;
	opr_map[">="] = true;
	opr_map["=="] = true;
	opr_map["!="] = true;
	opr_map["&"] = true;
	opr_map["^"] = true;
	opr_map["|"] = true;
	opr_map["&&"] = true;
	opr_map["||"] = true;
	opr_map["="] = true;
	opr_map["+="] = true;
	opr_map["-="] = true;
	opr_map["*="] = true;
	opr_map["/="] = true;
	opr_map["%="] = true;
	opr_map["<<="] = true;
	opr_map[">>="] = true;
	opr_map["&="] = true;
	opr_map["^="] = true;
	opr_map["|="] = true;
	opr_map[","] = true;
}

/*is keyword*/
bool is_keyword(string Idt)
{
	return key_map[Idt];
}

/*is operator*/
bool is_operator(string Opr)
{
	return opr_map[Opr];
}

/*is separator*/
bool is_separator(char currentChar)
{
	return (
		currentChar == '{' || currentChar == '}' || currentChar == '[' || 
		currentChar == ']' || currentChar == '(' || currentChar == ')' || 
		currentChar == ';' || currentChar == ','
		);
}

/*is int*/
bool is_int(string Num)
{
	regex r("^[+-]?(?:0|[1-9]\\d*)(?:u|U|l|L|ll|LL)?$");
	smatch m;
	regex_search(Num, m, r);
	return (m.size() > 0);
}

/*is float*/
bool is_float(string Num)
{
	regex r("^[+-]?\\d+(?:[.]\\d+[fFlL]?|[eE][+-]?\\d+)$");
	smatch m;
	regex_search(Num, m, r);
	return (m.size() > 0);
}

/*is oct*/
bool is_oct(string Num)
{
	regex r("^[+-]?0[0-7]+$");
	smatch m;
	regex_search(Num, m, r);
	return (m.size() > 0);
}

/*is hex*/
bool is_hex(string Num)
{
	regex r("^[+-]?0[xX][0-9a-fA-F]+$");
	smatch m;
	regex_search(Num, m, r);
	return (m.size() > 0);
}

/*Print all token*/
void printToken()
{
	int i;
	
	for (i = 0;i < Tokens.size();i++)
	{
		fputs("    <token>\n", TokenF);

		fputs("      <number>", TokenF);
		fputs(to_string(Tokens[i].number).c_str(), TokenF);
		fputs("</number>\n", TokenF);

		fputs("      <value>", TokenF);
		fputs(Tokens[i].value.c_str(), TokenF);
		fputs("</value>\n", TokenF);

		fputs("      <type>", TokenF);
		switch (Tokens[i].type)
		{
		case 0:
			fputs("keyword", TokenF);
			break;
		case 1:
			fputs("identifier", TokenF);
			break;
		case 2:
			fputs("operator", TokenF);
			break;
		case 3:
			fputs("separator", TokenF);
			break;
		case 4:
			fputs("const_int", TokenF);
			break;
		case 5:
			fputs("string", TokenF);
			break;
		case 6:
			fputs("const_float", TokenF);
			break;
		case 7:
			fputs("const_oct", TokenF);
			break;
		case 8:
			fputs("const_hex", TokenF);
			break;
		}
		fputs("</type>\n", TokenF);

		fputs("      <line>", TokenF);
		fputs(to_string(Tokens[i].line).c_str(), TokenF);
		fputs("</line>\n", TokenF);

		fputs("      <valid>", TokenF);
		if (Tokens[i].valid == true)
		{
			fputs("true", TokenF);
		}
		else
		{
			fputs("false", TokenF);
		}
		fputs("</valid>\n", TokenF);

		fputs("    </token>\n", TokenF);
	}

	/*Last # token*/
	fputs("    <token>\n", TokenF);
	fputs("      <number>", TokenF);
	fputs(to_string(wordCounter).c_str(), TokenF);
	fputs("</number>\n", TokenF);
	fputs("      <value>", TokenF);
	fputs("#", TokenF);
	fputs("</value>\n", TokenF);
	fputs("      <type>", TokenF);
	fputs("#", TokenF);
	fputs("</type>\n", TokenF);
	fputs("      <line>", TokenF);
	fputs(to_string(lineCounter).c_str(), TokenF);
	fputs("</line>\n", TokenF);
	fputs("      <valid>", TokenF);
	fputs("true", TokenF);
	fputs("</valid>\n", TokenF);
	fputs("    </token>\n", TokenF);
}