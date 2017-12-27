#include "stdio.h"
int main()
{
	char cha/*输入的首字母*/,chaplus/*每一行的字母*/;
	int n/*输入的“边长”*/, line/*行*/,spacehead/*每一行开始时的空格总数*/,spacemid/*每一行中间的空格总数*/;
	int linecount/*行计数器*/,chacount/*字母计数器*/,spaceheadcount/*每一行开始时的空格计数器*/,spacemidcount/*每一行中间的空格计数器*/;
	scanf("%d %c", &n, &cha);
	if (cha<'A' || cha>'Z')
	{
		printf("input error.\n");
		return 0;
	}
	line = n - 1;//确定额外行数
	for (chaplus = cha, chacount = 1; chacount <= line;chacount++)//确定第一行的输出字母
	{
		chaplus++;
		if (chaplus == '[')
			chaplus = 'A';
	}
	for (linecount = 1; linecount <= line; linecount++, chaplus--)//确定第linecount行的输出字母
	{
		if (chaplus == '@')
			chaplus = 'Z';
		spacehead = linecount - 1;//确定每一行的前置空格数
		spacemid = (line - linecount) * 2 + 1;//确定每一行的中间空格数
		for (spaceheadcount = 1; spaceheadcount <= spacehead; spaceheadcount++)//输出前置空格
			printf(" ");
		printf("%c", chaplus);//输出第一个字母
		for (spacemidcount = 1; spacemidcount <= spacemid; spacemidcount++)//输出中间空格
			printf(" ");
		printf("%c\n", chaplus);//输出第二个字母并换行
	}
	for (spaceheadcount = 1; spaceheadcount <= line; spaceheadcount++)//输出第n(边长)行的前置空格
		printf(" ");
	printf("%c\n", cha);
	chaplus = cha;
	for (linecount = 1; linecount <= line; linecount++)//确定第linecount行的输出字母
	{
		chaplus--;
		if (chaplus == '@')
			chaplus = 'Z';
		spacehead = line - linecount;//确定每一行的前置空格数
		spacemid = linecount * 2 - 1;//确定每一行的中间空格数
		for (spaceheadcount = 1; spaceheadcount <= spacehead; spaceheadcount++)//输出前置空格
			printf(" ");
		printf("%c", chaplus);//输出第一个字母
		for (spacemidcount = 1; spacemidcount <= spacemid; spacemidcount++)//输出中间空格
			printf(" ");
		printf("%c\n", chaplus);//输出第二个字母并换行
	}
}