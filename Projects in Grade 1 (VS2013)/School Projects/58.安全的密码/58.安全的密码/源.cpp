/*随着电子设备的广泛运用，密码也渐渐融入每个人的生活。保护好密码，不仅关系到个人隐私，更关系到个人的财产和安全。一个安全的密码，最好由大小写字母、数字或符号组成。包含越多种类的字符，其安全性就越高。同时密码还需要有一定的长度，通常至少要由六个以上的字符组成。

并不是每个人都喜欢这样复杂的密码，很多人在设置密码的时候，喜欢使用自己的名字或者生日，但这是很大的安全隐患。

任务
林晓炜正在设计一个网络交易系统，为了保证用户的密码安全，他需要一个程序，判断用户自己设置的密码是否安全，如果不安全，则给出提示。现在他向你求助，请你帮忙设计一个程序来解决这个问题。

应当按照以下的规则来判断密码是否安全：

如果密码长度小于 6 位，则不安全
如果组成密码的字符只有一类，则不安全
如果组成密码的字符有两类，则为中度安全
如果组成密码的字符有三类或以上，则为安全
通常，可以认为数字、大写字母、小写字母和其它符号为四类不同的字符。

输入
输入的第一行是一个整数 N，表明后面有多少组密码。随后的 N 行输入包括 N 个密码，每个密码的长度均小于 20 个字符。

输出
针对每一个密码判断并输出它是否安全。对于不安全的密码输出 "Not Safe"，对于中度安全的密码输出 "Medium Safe"，对于安全的密码输出 "Safe"

输入样例

4
1234
abcdef
ABC123
1#c3Gh

输出样例
Not Safe
Not Safe
Medium Safe
Safe


测试用例 1	以文本方式显示
10?
abcDEF?
ABC?
qw?
`?
ABCDEFGHIJKLMNOPQRST?
12345678901234567890?
1aB?
1 B?
a X   ?
qwe123%^&ABC?

以文本方式显示
Medium Safe?
Not Safe?
Not Safe?
Not Safe?
Not Safe?
Not Safe?
Safe?
Not Safe?
Safe?
Safe?
1秒	64M	0*/
#include "stdio.h"
#include "string.h"
int main()
{
	char password[21]/*密码字符数组*/;
	int n/*密码的总组数*/, len = 0/*密码长度*/, smallword = 0, bigword = 0, math = 0, others = 0/*四种字符 只可为0和1  有则1 无则0*/, all = 0/*密码中不同字符总数*/;
	int point/*密码每一位计数器*/;

	scanf("%d", &n);/*输入密码组数*/
	getchar();
	for (; n >= 1;n--)
	{
		smallword = 0;
		bigword = 0;
		math = 0;
		others = 0;
		gets(password);
		len = strlen(password);//取密码长度
		if (len < 6)//当密码位数小于6时 直接判定NOT SAFE 并进行下一个密码的判断
		{
			printf("Not Safe\n");
			continue;
		}
		else//如果密码位数大于等于6
		{
			for (point = 0; password[point] != '\0'; point++)//进行每一位判断
			{
				if (password[point] >= 97 && password[point] <= 122)//是否为小写字母
				{
					smallword = 1;
					continue;
				}
				if (password[point] >= 65 && password[point] <= 90)//是否为大写字母
				{
					bigword = 1;
					continue;
				}
				if (password[point] >= 48 && password[point] <= 57)//是否为数字
				{
					math = 1;
					continue;
				}
				if (1)//若前三个判断都没有进入 则判定为特殊符号
				{
					others = 1;
					continue;
				}
			}
			all = smallword + bigword + math + others;
			if (all == 1)
			{
				printf("Not Safe\n");
			}
			if (all == 2)
			{
				printf("Medium Safe\n");
			}
			if (all >= 3)
			{
				printf("Safe\n");
			}
		}
	}
	return 0;
}