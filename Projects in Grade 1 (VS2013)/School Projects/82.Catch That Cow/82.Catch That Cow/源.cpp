#include "stdio.h"
#include "string.h"
#define N 150000

int FJ, C;//farmer jack & cow����ʼȷ��λ��
int queue[N], in, out;//���� ���ָ��  ����ָ��
bool sign[N];//������� ֵֻ��0&1  1���ɷ��� 0�����ɷ��ʣ�������ϣ�
int minute[N];//�����Ӧ�� ����ʼλ�õ��˴���������ʱ���¼
int step;//farmer��λ�ü�¼��

int main()
{
	
	scanf("%d%d", &FJ, &C);

	in = out = 0;//��ʼ����ӳ���
	queue[0] = FJ;//��һ�������

	for (int x = 0; x < N; x++)//����������ȫ�����Ϊ�ɷ���
	{
		sign[x] = 1;
	}
	sign[FJ] = 0;//��farmer jack��λ�ñ��Ϊ�ѷ���

	minute[FJ] = 0;//����ʼλ�õ�ʱ���Ϊ0����

	while (out <= in)//������Ϊ�ǿ�  ������ָ��һֱ�����ָ��֮��  �����ж�
	{
		step = queue[out];//�����ӵ�λ�ü�¼����
		out++;//����ָ��ǰ��һ��λ

		/*����Ϊ���ӵ��ƶ���ĵ���ж�*/
		if (step == C)//�����ӵĵ��Ѿ�����ţ��λ��  �����Ӧʱ�� ���˳�
		{
			printf("%d\n", minute[step]);
			break;
		}
		if ((step - 1) >= 0 && sign[step - 1])//�����ӵ��ǰһ��λ���ڷ�Χ���ҿɷ��� ����������
		{
			in++;
			queue[in] = step - 1;
			minute[step - 1] = minute[step] + 1;//��ʱ����� �ƶ���ĵ���ƶ�ǰ��������ĵ㣩��һ����
			sign[step - 1] = 0;//���ƶ���ļ������ĵ���Ϊ���ɷ���
		}
		if ((step + 1) <= N && sign[step + 1])//�����ӵ�ĺ�һ��λ���ڷ�Χ���ҿɷ��� ����������
		{
			in++;
			queue[in] = step + 1;
			minute[step + 1] = minute[step] + 1;//��ʱ����� �ƶ���ĵ���ƶ�ǰ��������ĵ㣩��һ����
			sign[step + 1] = 0;//���ƶ���ļ������ĵ���Ϊ���ɷ���
		}
		if ((2 * step) <= N && sign[2 * step])//�����ӵ��2*λ���ڷ�Χ���ҿɷ��� ����������
		{
			in++;
			queue[in] = 2 * step;
			minute[2 * step] = minute[step] + 1;//��ʱ����� �ƶ���ĵ���ƶ�ǰ��������ĵ㣩��һ����
			sign[2 * step] = 0;//���ƶ���ļ������ĵ���Ϊ���ɷ���
		}
	}
	return 0;
}