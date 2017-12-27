#include "stdio.h"
#include "string.h"
#define N 500

/*数据结构*/
struct NODE
{
	int sb;//记录父节点(上一个节点)  sign  back
	int sn;//记录父节点对该节点的操作编号  seperate number

	int i;//记录A杯子里的水的容量
	int j;//记录B被子里的水的容量
};
NODE line[1000000];//队列

/*调用的函数声明*/
int BFS();
int findback(NODE x);
void sep1(NODE &s, int b);
void sep2(NODE &s, int b);
void sep3(NODE &s, int b);
void sep4(NODE &s, int b);
void sep5(NODE &s, int b);
void sep6(NODE &s, int b);

int A, B, water;//Pot A & B'V *** needed water<=max(A,B)(1-100)
int step = 0;//needed steps

bool sign[N][N];//记录节点是否可访问
int way[10240];//记录操作

int main()
{
	int YN;//判断能否达到目标水量

	scanf("%d%d%d", &A, &B, &water);
	memset(sign, false, sizeof(sign));//将所有节点记录（重置）为可访问(可访问为false  不可访问为true)
	memset(way, 0, sizeof(way));//将操作访问重置
	step = 0;//重置步骤数

	YN = BFS();//记录是否能够通过操作达到目的  若能 则为1  若不能 则为0

	if (YN == 1)//若能
	{
		printf("%d\n", step);//输出需要的步骤数
		step--;
		while (step >= 0)
		{
			if (way[step] == 1)
			{
				printf("FILL(1)\n");
			}
			if (way[step] == 2)
			{
				printf("FILL(2)\n");
			}
			if (way[step] == 3)
			{
				printf("DROP(1)\n");
			}
			if (way[step] == 4)
			{
				printf("DROP(2)\n");
			}
			if (way[step] == 5)
			{
				printf("POUR(1,2)\n");
			}
			if (way[step] == 6)
			{
				printf("POUR(2,1)\n");
			}
			step--;
		}
	}
	else//若不能
	{
		printf("impossible\n");
	}
	return 0;
}

/*以下6个函数为每一个状态下的操作*/
void sep1(NODE &s, int b)//打满A
{
	s.i = A;//把A倒满
	s.sb = b;//记录父亲节点的位置
	s.sn = 1;//记录从父亲节点到此点的操作编号
}
void sep2(NODE &s, int b)//打满B
{
	s.j = B;
	s.sb = b;
	s.sn = 2;
}
void sep3(NODE &s, int b)//倒掉A
{
	s.i = 0;
	s.sb = b;
	s.sn = 3;
}
void sep4(NODE &s, int b)//倒掉B
{
	s.j = 0;
	s.sb = b;
	s.sn = 4;
}
void sep5(NODE &s, int b)//把A倒入B
{
	if (s.i + s.j <= B)//当A和B中的溶液体积小于B的容积时
	{
		s.j = s.i + s.j;
		s.i = 0;
		s.sb = b;
		s.sn = 5;
	}
	else//大于时
	{
		s.i = s.i + s.j - B;//A就剩下多余的液体
		s.j = B;//B倒满
		s.sb = b;
		s.sn = 5;
	}
}
void sep6(NODE &s, int b)//把B倒入A
{
	if (s.i + s.j <= A)//当A和B中的溶液体积小于B的容积时
	{
		s.i = s.j + s.i;
		s.j = 0;
		s.sb = b;
		s.sn = 6;
	}
	else//大于时
	{
		s.j = s.j + s.i - A;//A就剩下多余的液体
		s.i = A;//B倒满
		s.sb = b;
		s.sn = 6;
	}
}

int findback(NODE x)//找到解决方案时  按路径返回  倒序记录
{
	while (1)//进入死循环 直到找到父节点为0的点则break
	{
		if (x.sn == 0)//退出条件
		{
			break;
		}
		way[step++] = x.sn;
		x = line[x.sb];
	}
	return 0;
}

int BFS()
{
	int out = 0, in = 1;//退出队伍和进入队伍  分别重置为0 和 1

	/*初始化条件*/
	line[0].i = 0;//重置A、B中的水为0
	line[0].j = 0;
	line[0].sb = 0;//第一个节点的父节点记为0
	line[0].sn = 0;//从父节点到此节点的操作编号记为0
	sign[0][0] = true;//记初始情况（两个杯子全为空）为已访问
	/*初始化完毕*/

	while (out < in)//当队伍非空时
	{
		NODE x;//记录队列中当前出队位置的NODE
		x = line[out];

		if (x.i == water || x.j == water)//如果找到解决方案  则利用findback函数寻找返回路径 并且给main返回值1
		{
			findback(x);
			return 1;
		}

		if (x.i != A)//当A中的液体不是满的的时候  可以进行操作1
		{
			sep1(x, out);
			if (sign[x.i][x.j] == false)//如果该状态尚未被访问  则将该状态加入到队伍中 并记录为被访问
			{
				line[in] = x;
				in++;
				sign[x.i][x.j] = true;
			}
			x = line[out];//将x给还原回来，以免以改变后的x来进行以下的加入队伍的操作
		}
		if (x.j != B)
		{
			sep2(x,out);
			if (sign[x.i][x.j] == false)
			{
				line[in] = x;
				in++;
				sign[x.i][x.j] = true;
			}
			x = line[out];
		}
		if (x.i != 0)//当A为非空时  可以进行sep3
		{
			sep3(x, out);
			if (sign[x.i][x.j] == false)
			{
				line[in] = x;
				in++;
				sign[x.i][x.j] = true;
			}
			x = line[out];
		}
		if (x.j != 0)
		{
			sep4(x, out);
			if (sign[x.i][x.j] == false)
			{
				line[in] = x;
				in++;
				sign[x.i][x.j] = true;
			}
			x = line[out];
		}
		if (x.i != 0)//当A为非空时 可进行sep5
		{
			sep5(x, out);
			if (sign[x.i][x.j] == false)
			{
				line[in] = x;
				in++;
				sign[x.i][x.j] = true;
			}
			x = line[out];
		}
		if (x.j != 0)
		{
			sep6(x, out);
			if (sign[x.i][x.j] == false)
			{
				line[in] = x;
				in++;
				sign[x.i][x.j] = true;
			}
			x = line[out];
		}
		out++;
	}
	return 0;//如果没能达到目标 则返回给main函数0
}