#include "stdio.h"
#include "string.h"
#define N 150000

int FJ, C;//farmer jack & cow的起始确定位置
int queue[N], in, out;//队列 入队指针  出队指针
bool sign[N];//标记数列 值只有0&1  1：可访问 0：不可访问（访问完毕）
int minute[N];//区域对应的 从起始位置到此处的所花的时间记录
int step;//farmer的位置记录器

int main()
{
	
	scanf("%d%d", &FJ, &C);

	in = out = 0;//初始化入队出队
	queue[0] = FJ;//第一个点入队

	for (int x = 0; x < N; x++)//将整个区域全部标记为可访问
	{
		sign[x] = 1;
	}
	sign[FJ] = 0;//将farmer jack的位置标记为已访问

	minute[FJ] = 0;//将起始位置的时间记为0分钟

	while (out <= in)//当队列为非空  即出队指针一直在入队指针之后  进入判断
	{
		step = queue[out];//将出队的位置记录下来
		out++;//出队指针前进一单位

		/*以下为出队点移动后的点的判断*/
		if (step == C)//当出队的点已经到达牛的位置  输出对应时间 并退出
		{
			printf("%d\n", minute[step]);
			break;
		}
		if ((step - 1) >= 0 && sign[step - 1])//当出队点的前一个位置在范围内且可访问 则将其加入队伍
		{
			in++;
			queue[in] = step - 1;
			minute[step - 1] = minute[step] + 1;//在时间表上 移动后的点比移动前（出队伍的点）加一分钟
			sign[step - 1] = 0;//将移动后的加入队伍的点标记为不可访问
		}
		if ((step + 1) <= N && sign[step + 1])//当出队点的后一个位置在范围内且可访问 则将其加入队伍
		{
			in++;
			queue[in] = step + 1;
			minute[step + 1] = minute[step] + 1;//在时间表上 移动后的点比移动前（出队伍的点）加一分钟
			sign[step + 1] = 0;//将移动后的加入队伍的点标记为不可访问
		}
		if ((2 * step) <= N && sign[2 * step])//当出队点的2*位置在范围内且可访问 则将其加入队伍
		{
			in++;
			queue[in] = 2 * step;
			minute[2 * step] = minute[step] + 1;//在时间表上 移动后的点比移动前（出队伍的点）加一分钟
			sign[2 * step] = 0;//将移动后的加入队伍的点标记为不可访问
		}
	}
	return 0;
}