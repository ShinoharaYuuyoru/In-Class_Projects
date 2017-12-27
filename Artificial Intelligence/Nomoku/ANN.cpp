//输入层(width*height)个神经元
//中间层1/2*(width*height)个神经元
//输出层1个神经元
//一共3/2(width*height)+1个神经元
//一共(1 / 2)*width*height*width*height+(1 / 2)*width*height个权值
#include <cstring>
#include <ctime>
#include <cstdlib>

#ifndef MAX_BOARD
#define MAX_BOARD 100
#endif // !MAX_BOARD


extern int width, height;//借用全局变量宽，高
extern int board[MAX_BOARD][MAX_BOARD];//借用全局变量棋盘状态

//神经元序列[width*height]+(1/2)*width*height+1
int *neure= new int[(3/2)*width*height+1];
//权值序列[width*height][(1/2)*width*height]+(1/2)*width*height
int *weight = new int[(1 / 2)*width*height*width*height + (1 / 2)*width*height];


//特殊情况下可使用以下方式定义神经网络
////神经元序列[width*height]+(1/2)*width*height+1
//int *neure = new int[(int)((3.0 / 2)*MAX_BOARD*MAX_BOARD + 1)];
////权值序列[width*height][(1/2)*width*height]+(1/2)*width*height
//int *weight = new int[(int)((1.0 / 2)*MAX_BOARD*MAX_BOARD*MAX_BOARD*MAX_BOARD + (1.0 / 2)*MAX_BOARD*MAX_BOARD)];


void init_ANN(){//初始化ANN网络获得随机权值，输入神经元赋值，中间及输出神经元置0

	//初始化前width*height个神经元值为棋盘状态
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			neure[i*height + j] = board[i][j];
		}
	}

	memset(&(neure[width*height]), 0, sizeof(int)*((int)((1.0 / 2)*width*height + 1)));
	srand((unsigned)time(NULL));
	for (int i = 0; i < (int)((1.0 / 2)*width*height*width*height + (1.0 / 2)*width*height); i++){
		weight[i] = rand();
	}
}

void Update_ANN(){//根据权值更新中间，输出神经元值
	//整合函数=加权求和g(x)=sum(wi*ai)
	//激活函数=线性函数f(x)=x
	for (int i = 0; i < (int)((1.0 / 2)*width*height); i++){//计算中间层神经元值
		//neure[width*height+i]=sum(wi*ai)
		for (int j = 0; j < width*height; j++){
			//每一个输入神经元J*乘上到中间神经元I的权重
			neure[width*height + i] += neure[j] * weight[(int)(j*(1.0 / 2)*width*height + i)];
		}
	}
	for (int i = 0; i <= (int)((1.0 / 2)*width*height); i++){//计算输出层神经元值
		//neure[(3/2)*width*height]=sum(wi*ai)
		neure[(int)((3.0 / 2)*width*height)] += neure[width*height + i] * weight[(int)((1.0 / 2)*width*height*width*height + i)];
	}
}