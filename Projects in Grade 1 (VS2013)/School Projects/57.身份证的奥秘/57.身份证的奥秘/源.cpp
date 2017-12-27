/*背景
18位身份证标准在国家质量技术监督局于1999年7月1日实施的GB11643 - 1999《公民身份号码》中做了明确的规定。 GB11643 - 1999《公民身份号码》为GB11643 - 1989《社会保障号码》的修订版，其中指出将原标准名称"社会保障号码"更名为"公民身份号码"，另外GB11643 - 1999《公民身份号码》从实施之日起代替GB11643 - 1989。GB11643 - 1999《公民身份号码》主要内容如下：

一、范围
该标准规定了公民身份号码的编码对象、号码的结构和表现形式，使每个编码对象获得一个唯一的、不变的法定号码。

二、编码对象
公民身份号码的编码对象是具有中华人民共和国国籍的公民。

三、号码的结构和表示形式
1、号码的结构

公民身份号码是特征组合码，由十七位数字本体码和一位校验码组成。排列顺序从左至右依次为：六位数字地址码，八位数字出生日期码，三位数字顺序码和一位数字校验码。

2、地址码

表示编码对象常住户口所在县(市、旗、区)的行政区划代码，按GB / T2260的规定执行。

3、出生日期码

表示编码对象出生的年、月、日，按GB / T7408的规定执行，年、月、日代码之间不用分隔符。

4、顺序码

表示在同一地址码所标识的区域范围内，对同年、同月、同日出生的人编定的顺序号，顺序码的奇数分配给男性，偶数分配给女性。

5、校验码

（1）十七位数字本体码加权求和公式

S = Sum(Ai * Wi), i = 0, ..., 16 ，先对前17位数字的权求和
Ai : 表示第i位置上的身份证号码数字值
Wi : 表示第i位置上的加权因子
Wi : 7 9 10 5 8 4 2 1 6 3 7 9 10 5 8 4 2
（2）计算模
Y = mod(S, 11)
（3）通过模得到对应的校验码
     Y : 0 1 2 3 4 5 6 7 8 9 10
校验码 : 1 0 X 9 8 7 6 5 4 3 2

四、举例如下：
	 北京市朝阳区 : 11010519491231002X
	 广东省汕头市 : 440524188001010014

15位的身份证号升级办法：

	15位的身份证号：dddddd yymmdd xx p
	18位的身份证号：dddddd yyyymmdd xx p y

				   其中dddddd为地址码（省地县三级）
				   yyyymmdd yymmdd 为出生年月日
				   xx顺号类编码
				   p性别
15 位的 yy 年升为 18 位后，变成 19yy年，但对于百岁以上老人， 则为 18yy 年，此时，他们的最后三位顺序码为996, 997, 998 或 999 来标记。

				   输入
				   输入n组身份证号码，第一行为个数，以后每行为身份证号码。

				   输出
				   如果输入的身份证号码为15位，则将其升级为18位后显示输出；否则判断其是否为合法身份证号，并逐行输出。


				   测试用例 1	
				   以文本方式显示
				   4↵
				   350622197904130331↵
				   11010519491231002X↵
				   110105491231002↵
				   110105491231996↵
				   以文本方式显示
				   Invalid↵
				   Valid↵
				   11010519491231002X↵
				   110105184912319965↵
				   1秒	64M	0*/

#include "stdio.h"
#include "string.h"
#define N 19

int Sum(char *ID, int *Wi);

int main()
{
	int n/*输入身份证号的个数*/,len/*输入的身份证号码长度*/;
	int Y/*取模后的值*/;
	char JYnumber[12] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2','\0' }/*对应校验码*/;
	int W[17] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 }/*前17位权*/;
	int IDcount/*输入身份证号码个数计数器*/,savecount/*15位身份证号码信息临时存储计数器*/,savecpycount/*15位身份证号码复制信息时用计数器*/;
	char IDnumber[1000][N] = { { '\0' } }/*身份证号码*/, save100[10] = {'\0'}/*15位身份证号码信息临时存储*/;

	scanf("%d", &n);
	for (IDcount = 1; IDcount <= n; IDcount++)
	{
		scanf("%s", IDnumber[IDcount]);
	}//输入完毕
	for (IDcount = 1; IDcount <= n; IDcount++)
	{
		len = strlen(IDnumber[IDcount]);
		if (len == 15)//如果输入的身份证号码位数为15位
		{
			if (IDnumber[IDcount][12] == '9'&&IDnumber[IDcount][13] == '9' && (IDnumber[IDcount][14] == '6' || IDnumber[IDcount][14] == '7' || IDnumber[IDcount][14] == '8' || IDnumber[IDcount][14] == '9'))//如果为百岁老人
			{
				for (savecount = 6, savecpycount = 0; savecount <= 14; savecount++, savecpycount++)//保存前六位后边的字符
				{
					save100[savecpycount] = IDnumber[IDcount][savecount];
				}
				IDnumber[IDcount][6] = '1';
				IDnumber[IDcount][7] = '8';//插入'1'和'8'
				for (savecpycount = 8; savecpycount <= 14; savecpycount++)
					IDnumber[IDcount][savecpycount] = '\0';//将18后的所有字符变'\0'
				strcat(IDnumber[IDcount], save100);//百岁老人17位身份证号码完成
			}
			else//如果不是百岁老人
			{
				for (savecount = 6, savecpycount = 0; savecount <= 14; savecount++, savecpycount++)//保存前六位后边的字符
				{
					save100[savecpycount] = IDnumber[IDcount][savecount];
				}
				IDnumber[IDcount][6] = '1';
				IDnumber[IDcount][7] = '9';//插入'1'和'9'
				for (savecpycount = 8; savecpycount <= 14; savecpycount++)
					IDnumber[IDcount][savecpycount] = '\0';//将18后的所有字符变'\0'
				strcat(IDnumber[IDcount], save100);//非百岁老人17位身份证号码完成
			}
			Y=Sum(IDnumber[IDcount], W);//进行取权+校验码位确定
			IDnumber[IDcount][17] = JYnumber[Y];
			printf("%s\n", IDnumber[IDcount]);
		}
		else//如果为18位身份证号码 直接进入合法判断
		{
			if (len != 18)
			{
				printf("Invalid\n");
			}
			else
			{
				Y = Sum(IDnumber[IDcount], W);
				if (IDnumber[IDcount][17] == JYnumber[Y])
				{
					printf("Valid\n");
				}
				else
				{
					printf("Invalid\n");
				}
			}
		}
	}
}

int Sum(char *ID, int *Wi)//取权+取模
{
	int n/*取位计数器*/, sum = 0/*权和*/, Y/*校验码*/;
	for (n = 0; n <= 16; n++)
	{
		sum = sum + (ID[n] - 48)*Wi[n];
	}
	Y = sum % 11;
	return Y;
}

/*以下为网络答案*/
//#include <stdio.h>
//#include <string.h>
//bool fun(char *a)//判断百岁老人
//{
//	if (strcmp(&a[14], "996") == 0 ||strcmp(&a[14], "997") == 0 ||strcmp(&a[14], "998") == 0 ||strcmp(&a[14], "999") == 0)
//		return 1;
//	else return 0;
//}
//char fun2(char *a)//计算检验码
//{
//	int t1[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
//	char t2[] = "10X98765432";
//	int sum = 0;
//	for (int i = 0; i<17; i++)
//		sum += (a[i] - '0')*t1[i];
//	return t2[sum % 11];
//}
//int main()
//{
//	int n, i;
//	char a[20];
//	scanf("%d", &n);
//	while (n--)
//	{
//		scanf("%s", a);
//		int len = strlen(a);
//		if (len == 15)
//		{
//			for (i = 17; i >= 8; i--)
//				a[i] = a[i - 2];
//			a[6] = '1';
//			if (fun(a))
//				a[7] = '8';
//			else 
//				a[7] = '9';
//			a[17] = fun2(a);
//			a[18] = 0;
//			printf("%s\n", a);
//		}
//		else
//		{
//			if (fun2(a) == a[17])
//				printf("Valid\n");
//			else 
//				printf("Invalid\n");
//		}
//	}
//	return 0;
//}