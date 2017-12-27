#include <iostream>
#include <string>
#include <map>
using namespace std;

FILE *SrcCodeF;
FILE *PPCodeF;
string SrcCode = "";

void ReadSrctoStr();
void PreProcess();
void commentProcess();
void includeProcess();
void defineProcess();
void spaceDelete();
void WritetoPPCodeF();

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Error: argc error." << endl;

		exit(1);
	}

	SrcCodeF = fopen(argv[1], "rt");
	PPCodeF = fopen(argv[2], "wt");
	if (SrcCodeF == NULL)
	{
		cout << "Error: Source code file not exists." << endl;

		exit(1);
	}
	if (PPCodeF == NULL)
	{
		cout << "Error: Open/Create PreProcess code file error." << endl;

		exit(1);
	}

	ReadSrctoStr();
	fclose(SrcCodeF);

	PreProcess();

	WritetoPPCodeF();
	fclose(PPCodeF);

	cout << "1. PreProcessor finished!" << endl;
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

	SrcCode.push_back('\n');	//Add an extra ENTER at the end.
}

/*PreProcess*/
void PreProcess()
{
	spaceDelete();

	commentProcess();
	spaceDelete();

	includeProcess();
	spaceDelete();

	defineProcess();
	spaceDelete();
}

/*Comment process*/
void commentProcess()
{
	/*Block Comment Delete*/
	string::size_type BCStart;
	string::size_type BCEnd;

	while (1)
	{
		BCStart = SrcCode.find("/*", 0);
		if (BCStart != string::npos)
		{
			while (1)
			{
				BCEnd = SrcCode.find("*/", 0);
				if (BCEnd != string::npos)
				{
					int BCDeleteLength = BCEnd + 2 - BCStart;
					SrcCode.erase(BCStart, BCDeleteLength);

					break;
				}
				else
				{
					cout << "Block Comment Delete Error!" << endl;

					exit(1);
				}
			}
		}
		else
		{
			break;
		}
	}

	/*Line Comment Delete*/
	string::size_type LCStart;
	string::size_type LCEnd;

	while (1)
	{
		LCStart = SrcCode.find("//", 0);
		if (LCStart != string::npos)
		{
			while (1)
			{
				LCEnd = SrcCode.find('\n', LCStart);
				if (LCEnd != string::npos)
				{
					int LCDeleteLength = LCEnd - LCStart;
					SrcCode.erase(LCStart, LCDeleteLength);

					break;
				}
				else
				{
					cout << "Line Comment Delete Error!" << endl;

					exit(1);
				}
			}
		}
		else
		{
			break;
		}
	}
}

/*Process the include file(nowtime is just delete)*/
void includeProcess()
{
	string::size_type includeStart;
	string::size_type includeEnd;

	while (1)
	{
		includeStart = SrcCode.find("#include", 0);
		if (includeStart != string::npos)
		{
			while (1)
			{
				includeEnd = SrcCode.find('\n', includeStart);
				if (includeEnd != string::npos)
				{
					int icdDeleteLength = includeEnd - includeStart;	//#include line delete length.
					SrcCode.erase(includeStart, icdDeleteLength);

					break;
				}
				else
				{
					cout << "#include line Delete Error!" << endl;

					exit(1);
				}
			}
		}
		else
		{
			break;
		}
	}
}

/*Replace the define line*/
void defineProcess()
{
	map<string, string> defineMap;
	string::size_type defineStart;
	string::size_type defineEnd;

	while (1)
	{
		defineStart = SrcCode.find("#define", 0);
		if (defineStart != string::npos)
		{
			while (1)
			{
				defineEnd = SrcCode.find('\n', defineStart);
				if (defineEnd != string::npos)
				{
					string::size_type defineSep1;	//define's identifier seperator(the space)'s position.
					defineSep1 = SrcCode.find(' ', defineStart);
					if (defineSep1 != string::npos)
					{
						if (defineSep1 == defineStart + 7)	//"#define " leagal.
						{
							string::size_type defineSep2;
							defineSep2 = SrcCode.find(' ', defineSep1 + 1);	//define's token seperator's position.
							if (defineSep2 < defineEnd)
							{
								/*Push into map*/
								string dfnIdentifier = "";
								string dfnToken = "";

								dfnIdentifier.assign(SrcCode, defineSep1 + 1, defineSep2 - defineSep1 - 1);
								dfnToken.assign(SrcCode, defineSep2 + 1, defineEnd - defineSep2 - 1);
								defineMap.insert(pair<string, string>(dfnIdentifier, dfnToken));

								/*Delete #define line*/
								SrcCode.erase(defineStart, defineEnd - defineStart);

								break;
							}
							else//Just defined identifier, no use.
							{
								/*Delete #define line*/
								SrcCode.erase(defineStart, defineEnd - defineStart);

								break;
							}
						}
						else
						{
							if (SrcCode[defineStart + 7] == '\n')	//Nothing defined.
							{
								/*Delete #define line*/
								SrcCode.erase(defineStart, defineEnd - defineStart);

								break;
							}
							else
							{
								cout << "#define format error!" << endl;

								exit(1);
							}
						}
					}
					else
					{
						cout << "#define format error!" << endl;

						exit(1);
					}
				}
				else
				{
					cout << "#define line process error!" << endl;

					exit(1);
				}
			}
		}
		else
		{
			break;
		}
	}

	/*Exchange define*/
	map<string, string>::iterator ite;
	for (ite = defineMap.begin();ite != defineMap.end();ite++)
	{
		string::size_type defineExchange;
		while (1)
		{
			defineExchange = SrcCode.find(ite->first, 0);
			if (defineExchange != string::npos)
			{
				string tempIdentifier = ite->first;
				int IdentifierSize = tempIdentifier.size();
				string tempToken = ite->second;

				SrcCode.replace(defineExchange, IdentifierSize, tempToken);
			}
			else
			{
				break;
			}
		}
	}
}

/*Delete extra space*/
void spaceDelete()
{
	/*Delete all space, \t, and \n at the head*/
	string::size_type deleteHeadSpace = 0;
	while (1)
	{
		if (SrcCode[deleteHeadSpace] == ' ' || SrcCode[deleteHeadSpace] == '\t' || SrcCode[deleteHeadSpace] == '\n')
		{
			SrcCode.erase(deleteHeadSpace, 1);
			deleteHeadSpace = 0;
		}
		else
		{
			break;
		}
	}

	/*Delete extra space, \t and \n before a \n*/
	string::size_type Scanner = SrcCode.size() - 1;
	while (Scanner > 0)
	{
		if (SrcCode[Scanner] == '\n')
		{
			if (SrcCode[Scanner - 1] == ' ' || SrcCode[Scanner - 1] == '\t' || SrcCode[Scanner - 1] == '\n')
			{
				SrcCode.erase(Scanner - 1, 1);
			}
		}

		Scanner--;
	}

	/*Delete extra space and \t before a space or \t*/
	Scanner = SrcCode.size() - 1;
	while (Scanner > 0)
	{
		if (SrcCode[Scanner] == ' ' || SrcCode[Scanner] == '\t')
		{
			if (SrcCode[Scanner - 1] == ' ' || SrcCode[Scanner - 1] == '\t')
			{
				SrcCode.erase(Scanner - 1, 1);
			}
		}

		Scanner--;
	}
}

/*Write the PreProcess code to target file.*/
void WritetoPPCodeF()
{
	string::size_type i = 0;
	char temp;

	for (i = 0;i < SrcCode.size();i++)
	{
		temp = SrcCode[i];

		fputc(temp, PPCodeF);
	}
}