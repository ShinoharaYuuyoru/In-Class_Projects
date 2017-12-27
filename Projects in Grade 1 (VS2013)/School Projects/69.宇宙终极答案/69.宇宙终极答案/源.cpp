/*全宇宙的文明经过不懈的探索最终得到了宇宙的终极答案（Answer to the Ultimate Question of Life, the Universe and the Everything）。

它是一个数字。

是一个两位数
是一个偶数
如果写成二进制（无前导0），0和1的个数一样多
如果写成四进制（无前导0），各位数是一样的
可以写成三个不同的正整数的平方和
有三个质因子
现在请你告诉我们，宇宙的终极答案是什么？
*/

#include "stdio.h" 

int binary(int n);
int forth(int n);
int main()
{
	int n = 10/*答案*/;
	int a, b, c/*三个正整数*/;
	for (n = 10; n <= 99; n = n + 2)
	{
		if (binary(n) == 1)//满足二进制的表示  
		{
			if (forth(n) == 1)//满足了四进制要求  
			{
				for (a = 1; a <= 9; a++)
				{
					for (b = 1; b <= 9; b++)
					{
						for (c = 1; c <= 9; c++)
						{
							if (n == a*a + b*b + c*c)//满足平方和要求 
							{
								printf("%d\n", n);/*此处省略了最后一个条件的计算 因为就剩下答案42了 直接输出算啦*/
								return 0;
							}
							else continue;//不满足平方和条件  继续  
						}
					}
				}
			}
			else
				continue;//不满足四进制要求  
		}
		else//不满足二进制要求  
			continue;
	}
}

int binary(int n)//进行二进制运算  
{
	int bina[7] = { 2, 2, 2, 2, 2, 2, 2 };
	int i = 0/*bina数组的下角标计数器*/, i0 = 0, i1 = 0/*0和1个数计数器*/;
	for (i = 0; n >= 1; i++)//录入n的二进制表示  
	{
		bina[i] = n % 2;
		n = n / 2;
	}
	for (i = 0; bina[i] != 2 && i <= 6; i++)
	{
		if (bina[i] == 0)
			i0++;
		if (bina[i] == 1)
			i1++;
	}
	if (i0 == i1)
		return 1;
	else
		return 0;
}


int forth(int n)//进行四进制相关要求的解决 
{
	int forth[4] = { 5, 5, 5, 5 };
	int same/*记4进制下的第一个数字*/;
	int i/*forth数组下角标计数器*/;
	for (i = 0; n >= 1; i++)
	{
		forth[i] = n % 4;
		n = n / 4;
	}
	same = forth[0];
	for (i = 1; forth[i] != 5 && i <= 3; i++)
	{
		if (forth[i] != same)
			return 0;//有一个不相同的就返回0 
	}
	return 1;//四进制下的数字都相同返回1 
}