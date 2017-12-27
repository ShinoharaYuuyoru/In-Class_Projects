#include "stdio.h"
#include "string.h"
#define N 500

/*���ݽṹ*/
struct NODE
{
	int sb;//��¼���ڵ�(��һ���ڵ�)  sign  back
	int sn;//��¼���ڵ�Ըýڵ�Ĳ������  seperate number

	int i;//��¼A�������ˮ������
	int j;//��¼B�������ˮ������
};
NODE line[1000000];//����

/*���õĺ�������*/
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

bool sign[N][N];//��¼�ڵ��Ƿ�ɷ���
int way[10240];//��¼����

int main()
{
	int YN;//�ж��ܷ�ﵽĿ��ˮ��

	scanf("%d%d%d", &A, &B, &water);
	memset(sign, false, sizeof(sign));//�����нڵ��¼�����ã�Ϊ�ɷ���(�ɷ���Ϊfalse  ���ɷ���Ϊtrue)
	memset(way, 0, sizeof(way));//��������������
	step = 0;//���ò�����

	YN = BFS();//��¼�Ƿ��ܹ�ͨ�������ﵽĿ��  ���� ��Ϊ1  ������ ��Ϊ0

	if (YN == 1)//����
	{
		printf("%d\n", step);//�����Ҫ�Ĳ�����
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
	else//������
	{
		printf("impossible\n");
	}
	return 0;
}

/*����6������Ϊÿһ��״̬�µĲ���*/
void sep1(NODE &s, int b)//����A
{
	s.i = A;//��A����
	s.sb = b;//��¼���׽ڵ��λ��
	s.sn = 1;//��¼�Ӹ��׽ڵ㵽�˵�Ĳ������
}
void sep2(NODE &s, int b)//����B
{
	s.j = B;
	s.sb = b;
	s.sn = 2;
}
void sep3(NODE &s, int b)//����A
{
	s.i = 0;
	s.sb = b;
	s.sn = 3;
}
void sep4(NODE &s, int b)//����B
{
	s.j = 0;
	s.sb = b;
	s.sn = 4;
}
void sep5(NODE &s, int b)//��A����B
{
	if (s.i + s.j <= B)//��A��B�е���Һ���С��B���ݻ�ʱ
	{
		s.j = s.i + s.j;
		s.i = 0;
		s.sb = b;
		s.sn = 5;
	}
	else//����ʱ
	{
		s.i = s.i + s.j - B;//A��ʣ�¶����Һ��
		s.j = B;//B����
		s.sb = b;
		s.sn = 5;
	}
}
void sep6(NODE &s, int b)//��B����A
{
	if (s.i + s.j <= A)//��A��B�е���Һ���С��B���ݻ�ʱ
	{
		s.i = s.j + s.i;
		s.j = 0;
		s.sb = b;
		s.sn = 6;
	}
	else//����ʱ
	{
		s.j = s.j + s.i - A;//A��ʣ�¶����Һ��
		s.i = A;//B����
		s.sb = b;
		s.sn = 6;
	}
}

int findback(NODE x)//�ҵ��������ʱ  ��·������  �����¼
{
	while (1)//������ѭ�� ֱ���ҵ����ڵ�Ϊ0�ĵ���break
	{
		if (x.sn == 0)//�˳�����
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
	int out = 0, in = 1;//�˳�����ͽ������  �ֱ�����Ϊ0 �� 1

	/*��ʼ������*/
	line[0].i = 0;//����A��B�е�ˮΪ0
	line[0].j = 0;
	line[0].sb = 0;//��һ���ڵ�ĸ��ڵ��Ϊ0
	line[0].sn = 0;//�Ӹ��ڵ㵽�˽ڵ�Ĳ�����ż�Ϊ0
	sign[0][0] = true;//�ǳ�ʼ�������������ȫΪ�գ�Ϊ�ѷ���
	/*��ʼ�����*/

	while (out < in)//������ǿ�ʱ
	{
		NODE x;//��¼�����е�ǰ����λ�õ�NODE
		x = line[out];

		if (x.i == water || x.j == water)//����ҵ��������  ������findback����Ѱ�ҷ���·�� ���Ҹ�main����ֵ1
		{
			findback(x);
			return 1;
		}

		if (x.i != A)//��A�е�Һ�岻�����ĵ�ʱ��  ���Խ��в���1
		{
			sep1(x, out);
			if (sign[x.i][x.j] == false)//�����״̬��δ������  �򽫸�״̬���뵽������ ����¼Ϊ������
			{
				line[in] = x;
				in++;
				sign[x.i][x.j] = true;
			}
			x = line[out];//��x����ԭ�����������Ըı���x���������µļ������Ĳ���
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
		if (x.i != 0)//��AΪ�ǿ�ʱ  ���Խ���sep3
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
		if (x.i != 0)//��AΪ�ǿ�ʱ �ɽ���sep5
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
	return 0;//���û�ܴﵽĿ�� �򷵻ظ�main����0
}