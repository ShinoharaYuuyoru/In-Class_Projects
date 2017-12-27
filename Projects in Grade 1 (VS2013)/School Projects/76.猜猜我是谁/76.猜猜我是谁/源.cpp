#include "stdio.h"
#include "stdlib.h"

int main()
{
	FILE *file;
	int line;
	int linecount = 1;
	char filename[50],ch,str[1000];

	scanf("%s", &filename);
	scanf("%d", &line);
	file = fopen(filename, "r");
	
	if (file == NULL)
	{
		printf("File Name Error.\n");
		exit(0);
	}
	else
	{
		while ((ch=fgetc(file)) != EOF)
		{
			if (line == linecount)
			{
				printf("%c", ch);
				printf("%s", fgets(str,1000,file));
				exit(0);
			}
			if (ch == '\n')
				linecount++;
		}
		printf("Line No Error.\n");
		exit(0);
	}
	fclose(file);
}