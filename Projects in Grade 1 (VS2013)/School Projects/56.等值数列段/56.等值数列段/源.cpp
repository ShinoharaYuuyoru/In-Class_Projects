/*如果一个数列中的某一段（至少有两个元素）的各元素值均相同，则称之为等值数列段。等值数列段中元素的个数叫做等值数列段的长度。

输入：
        由N个元素组成的整数数列A（其中N<=50)

输出：
        A中长度最大的所有等值数列段的始末位置，如果没有等值数列段，则输出No equal number list.

说明：
        始末位置是指数组下标，即0表示第一个元素。
        如果有多个同等长度的等值数列，只输出第一个等值数列的起始位置。即：当在一个LIST中出现两个等长的连续串时，答案应该是第一个等长串。

测试用例 1	
以文本方式显示
5↵
1 2 3 4 5↵
以文本方式显示
No equal number list.↵
1秒	64M	0

测试用例 2	
以文本方式显示
6↵
1 0 1 1 1 0↵
以文本方式显示
The longest equal number list is from 2 to 4.↵
1秒	64M	0

测试用例 3	
以文本方式显示
10↵
1 1 1 0 1 1 1 1 1 1↵
以文本方式显示
The longest equal number list is from 4 to 9.↵
1秒	64M	0

测试用例 4	
以文本方式显示
10↵
1 4 4 4 5 6 6 6 5 6↵
以文本方式显示
The longest equal number list is from 1 to 3.↵
1秒	64M	0*/

#include "stdio.h"
#define N 1000
int main()
{
	int n/*输入的元素个数*/, line[N] = { 0 }/*录入的数组*/, min = 0/*记录开始相同的元素的下角标*/, max = 0/*记录最后一个相同元素的下角标*/, len[2] = { 0 }/*记录相同的总长度*/,maxc,minc/*输出用*/;
	int scancount/*输入元素个数计数器(记录下角标)*/, count/*开始位*/, countsame/*检索相同元素*/, lencount = 0/*len数组下角标计数器*/;
	scanf("%d", &n);//录入元素个数n
	for (scancount = 0; scancount < n; scancount++)//录入数组
	{
		scanf("%d", &line[scancount]);
	}
	scancount--;//定位到数组最后一个元素
	for (count = 0; count <= scancount; count++)//开始检索
	{
		min = count;//min定位到检索的第一个元素
		countsame = count + 1;
		max = countsame;
		for (; line[count] == line[countsame] && countsame <= scancount; countsame++)//向下检索 并记录相同元素最大角标给max
		{
			max = countsame;
		}
		if (max - min == 1)//如果没有相同元素 进行下一个元素的检索
			continue;
		else//如果有至少2位相同  进入长度判断
		{
			if (lencount == 0)//第一组相同的元素长度录入给len[0]
			{
				len[lencount] = max - min + 1;
				lencount++;
				maxc = max;
				minc = min;
			}
			else//第二组开始 先录入给len[1]  然后进行len[1]与len[0]的大小判断  
			{
				len[lencount] = max - min + 1;
				if (len[1] <= len[0])//若len[1]小于等于len[0]   则进行下一个元素的检索
					continue;
				else//如果大于len[0]  将信息录入到len[0](刷新)
				{
					len[0] = len[1];
					len[1] = 0;
					maxc = max;
					minc = min;
				}
			}
		}
	}
	if (len[0] == 0)
		printf("No equal number list.\n");
	else
		printf("The longest equal number list is from %d to %d.\n", minc, maxc);
}