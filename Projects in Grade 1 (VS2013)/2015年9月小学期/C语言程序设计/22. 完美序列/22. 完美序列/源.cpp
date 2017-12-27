#include "stdio.h"

char S[100005];

int main()
{
	scanf("%s", S);
	
	int LeftBrNum = 0, RightBrNum = 0, SharpNum = 0;
	int scan;

	for (scan = 0; S[scan] != '\0'; scan++)
	{
		if (S[scan] == '(')
		{
			LeftBrNum++;
		}
		if (S[scan] == ')')
		{
			RightBrNum++;
		}
		if (S[scan] == '#')
		{
			SharpNum++;
		}

		if (LeftBrNum < (RightBrNum + SharpNum))
		{
			printf("-1\n");
			return 0;
		}
	}

	if (RightBrNum >= LeftBrNum || (RightBrNum + SharpNum) > LeftBrNum)
	{
		printf("-1\n");
		return 0;
	}
	else
	{
		int searchSharp = 0, searchLBr = 0, searchRBr = 0;
		if (SharpNum >= 1)
		{
			for (scan = 0; S[scan] != '\0'; scan++)
			{

				if (S[scan] == '#')
				{
					searchSharp++;
					searchRBr++;
					if (searchSharp == SharpNum)/*搜索到最后一个#*/
					{
						searchRBr = searchRBr + (LeftBrNum - RightBrNum - (SharpNum - 1)) - 1;
						scan++;
						break;
					}
				}
				if (S[scan] == '(')
				{
					searchLBr++;
				}
				if (S[scan] == ')')
				{
					searchRBr++;
				}
			}
		}
		if (searchRBr > searchLBr)
		{
			printf("-1\n");
			return 0;
		}
		else
		{
			for (; S[scan] != '\0'; scan++)
			{
				if (S[scan] == '(')
				{
					searchLBr++;
				}
				if (S[scan] == ')')
				{
					searchRBr++;
					if (searchRBr > searchLBr)
					{
						printf("-1\n");
						return 0;
					}
				}
			}
		}

		int SharpNumcount = SharpNum;
		int ChangeSharp = LeftBrNum - RightBrNum - (SharpNum - 1);

		for (; SharpNumcount > 1; SharpNumcount--)
		{
			printf("1\n");
		}
		printf("%d\n", ChangeSharp);
	}

	return 0;
}