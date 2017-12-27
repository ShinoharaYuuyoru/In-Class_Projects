#ifndef MAX_BOARD
#define	MAX_BOARD 100
#endif // !MAX_BOARD

#include "iostream"
#include "cstring"
#include "ctime"
#include "cstdlib"
#include "vector"
using namespace std;

int width = 5, height = 5; //Extern
int board[MAX_BOARD][MAX_BOARD];	//board[width][height]

									//神经元序列[width*height]+(1/2)*width*height+1
int *neure = new int[(int)((3.0 / 2)*MAX_BOARD*MAX_BOARD + 1)];
//权值序列[width*height][(1/2)*width*height]+(1/2)*width*height
int *weight = new int[(int)((1.0 / 2)*MAX_BOARD*MAX_BOARD*MAX_BOARD*MAX_BOARD + (1.0 / 2)*MAX_BOARD*MAX_BOARD)];

/*GA DATA*/
#define individualNum 32	//Number of individuals.
#define interationNum 256	//Number of interation times.
const int inputLevelNum = width * height;
const int middleLevelNum = (int)((1.0 / 2)*inputLevelNum);
const int outputLevelNum = 1;
const int weightNum = inputLevelNum*middleLevelNum + middleLevelNum*outputLevelNum;	//Number of weight.
vector<vector<short> > population(individualNum);	//Population: individualNum * (100*100*(1/2)*100*100 + (1/2)100*100)
vector<short> bestIndividual;	//Best one. The first time is nowtime weight.
vector<vector<short> > fatherPopulation(individualNum);
double bestValue;	//Best one's winrate.
double individualValue[individualNum];	//All individuals winrate.
double recombinantProb = 0.9;	//Recombinant Probablity
double mutateProb = 0.05;	//Mutate Probablity
/*GD END*/

void init_ANN();
void Update_ANN();

/*GA FUNC*/
void resizeVector_GA();	//Resize all vector
void init_GA();	//Initial.
void getValue_GA();	//Get individual's value.
void getBest_GA();	//Get the best individual.
void choose_GA();	//Spin table choose.
void recombine_GA();	//Recombine
void mutate_GA();	//Mutate

extern void FINANN(std::vector<short> *nowWeight);		//extern
extern void FOutANN(std::vector<short> *nowWeight);		//extern
double winrateCalc(vector<short> *nowWeight);	//extern********
/*GAFC END*/

int main()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cin >> board[j][i];
		}
	}
	init_ANN();
	Update_ANN();

	/*GA*/
	resizeVector_GA();
	init_GA();
	int interCounter = 0;	//interarion Counter.
	for (interCounter = 0;interCounter < interationNum;interCounter++)
	{
		getValue_GA();	//get all individual's value.
		getBest_GA();	//Get nowtime the best one.
		choose_GA();	//Spin table choose.
		recombine_GA();	//Recombine.
		mutate_GA();	//Mutate.
	}
}

void init_ANN() {//初始化

				 //初始化前width*height个神经元值为棋盘状态
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			neure[i*height + j] = board[i][j];
		}
	}

	memset(&(neure[width*height]), 0, sizeof(int)*((int)((1.0 / 2)*width*height + 1)));
	srand((unsigned)time(NULL));
	for (int i = 0; i < (int)((1.0 / 2)*width*height*width*height + (1.0 / 2)*width*height); i++) {
		weight[i] = rand();
	}
}

void Update_ANN() {
	//整合函数=加权求和g(x)=sum(wi*ai)
	//激活函数=线性函数f(x)=x
	for (int i = 0; i < (int)((1.0 / 2)*width*height); i++) {//计算中间层神经元值
															 //neure[width*height+i]=sum(wi*ai)
		for (int j = 0; j < width*height; j++) {
			//每一个输入神经元J*乘上到中间神经元I的权重
			neure[width*height + i] += neure[j] * weight[(int)(j*(1.0 / 2)*width*height + i)];
		}
	}
	for (int i = 0; i <= (int)((1.0 / 2)*width*height); i++) {//计算输出层神经元值
															  //neure[(3/2)*width*height]=sum(wi*ai)
		neure[(int)((3.0 / 2)*width*height)] += neure[width*height + i] * weight[(int)((1.0 / 2)*width*height*width*height + i)];
	}
}

void resizeVector_GA()	//Resize all vectors to arrays.
{
	bestIndividual.resize(weightNum);
	int x = 0;
	for (x = 0;x < individualNum;x++)
	{
		population[x].resize(weightNum);
	}
	for (x = 0;x < individualNum;x++)
	{
		fatherPopulation[x].resize(weightNum);
	}
}

void init_GA()
{
	//srand((unsigned)time(NULL));
	int x = 0;
	//for (x = 0;x < weightNum;x++)	//The first time, bestIndividual is nowtime weight.
	//{
	//	bestIndividual[x] = (short)weight[x];
	//}
	FINANN(&bestIndividual);	//Invoke Liu's code, get now board's best neure network.

	int y = 0;
	for (y = 0;y < individualNum;y++)
	{
		for (x = 0;x < weightNum;x++)	//Initial population.
		{
			population[y][x] = rand();
		}
	}
}

void getValue_GA()	//Get Value(winrate)
{
	int x = 0;
	bestValue = winrateCalc(&bestIndividual);
	for (x = 0;x < individualNum;x++)
	{
		individualValue[x] = winrateCalc(&population[x]);
	}
}

void getBest_GA()
{
	int x = 0;
	for (x = 0;x < individualNum;x++)
	{
		if (individualValue[x] > bestValue)
		{
			int y = 0;
			for (y = 0;y < weightNum;y++)
			{
				bestIndividual[y] = population[x][y];
			}

			bestValue = individualValue[x];

			FOutANN(&bestIndividual);	//Invoke Liu's code, output the best neure network which was got in one time's iteration.
		}
	}
}

void choose_GA()
{
	double winrateSum = 0;
	double occupyRate[individualNum];

	int x = 0;
	for (x = 0;x < individualNum;x++)	//Get winrateSum.
	{
		winrateSum = winrateSum + individualValue[x];
	}

	for (x = 0;x < individualNum;x++)	//Get every individual's occupation of the winrateSum.
	{
		occupyRate[x] = individualValue[x] / winrateSum;
	}

	for (x = 0;x < individualNum;x++)	//Get individualNum fathers.
	{
		//srand((unsigned)time(NULL));
		double randTemp = (double)rand() / RAND_MAX;	//Get random number between 0 and 1.

		double flag1 = 0;
		double flag2 = occupyRate[0];
		int y = 0;
		for (y = 0;y < individualNum;y++)	//Compare the occupy rate, and choose the father.
		{
			if (randTemp >= flag1&&randTemp < flag2)
			{
				//Push into fatherPopulation
				int z = 0;
				for (z = 0;z < weightNum;z++)
				{
					fatherPopulation[x][z] = population[y][z];
				}

				break;
			}
			else
			{
				flag1 = flag1 + occupyRate[y];
				flag2 = flag2 + occupyRate[y + 1];
			}
		}
	}
}

void recombine_GA()
{
	int x = 0;
	for (x = 0;x < individualNum;x = x + 2)
	{
		//srand((unsigned)time(NULL));
		double randTemp = (double)rand() / RAND_MAX;	//Get random number between 0 and 1.

		if (randTemp <= recombinantProb)
		{
			//srand((unsigned)time(NULL));
			int recombinePoint = (rand()*rand()) % weightNum;

			int y = 0;
			for (y = 0;y < weightNum;y++)	//Recombinant.
			{
				if (y < recombinePoint)
				{
					population[x][y] = fatherPopulation[x][y];
					population[x + 1][y] = fatherPopulation[x + 1][y];
				}
				else
				{
					population[x][y] = fatherPopulation[x + 1][y];
					population[x + 1][y] = fatherPopulation[x][y];
				}
			}
		}
		else
		{
			int y = 0;
			for (y = 0;y < weightNum;y++)
			{
				population[x][y] = fatherPopulation[x][y];
				population[x + 1][y] = fatherPopulation[x + 1][y];
			}
		}
	}
}

void mutate_GA()
{
	int x = 0;
	for (x = 0;x < individualNum;x++)
	{
		//srand((unsigned)time(NULL));
		double randTemp = (double)rand() / RAND_MAX;
		if (randTemp <= mutateProb)
		{
			//srand((unsigned)time(NULL));
			int mutatePoint = (rand()*rand()) % weightNum;

			//srand((unsigned)time(NULL));
			population[x][mutatePoint] = rand() % RAND_MAX;
		}
	}
}

double winrateCalc(vector<short> *nowWeight)
{
	//srand((unsigned)time(NULL));
	return (double)rand() / RAND_MAX;
}