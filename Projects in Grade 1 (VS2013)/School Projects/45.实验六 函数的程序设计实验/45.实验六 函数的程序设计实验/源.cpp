/*һ��ʵ��Ŀ��
ͨ���Ժ���������ĳ���ķ������ݹ麯���������պͺ�����ֵ������ϰ����ʶ�������βε�������͵ݹ��ԭ����⺯�����βε���ȷʹ�á��ݹ����ȷʹ�ú͵ݹ����ȱ�㡣

����ʵ������

1����Ŀ���۲�����еĸ������������������βε�������
ʵ���������ʾ��
����Ŀ��ڳ���Ĳ�ͬλ�ó����˲�ͬ�ı�������Щ�����ı�������Ϊx���ڳ���������š�1����2����3��......��������������ÿ������x�ĺ��涼��һ��printf �������Ա���x������Ļ��ʾ�������A��B��C......��printf��������������۲�C�������������������printf����ӡ���Ľ����Ӧ�ĸ�����x���Լ�������x����������д��1��
��ʵ����x�ı������Ͱ�����ȫ�ֱ������ֲ���������̬������*/

/*����һ*/
//
//#include <stdio.h>
//#include <stdlib.h>
//
//void useLocal(void);
//void useStaticLocal(void);
//void useGlobal(void);
//
//int x = 1; /*��1��*/
//int main(void)
//{
//	int x = 5; /*��2��*/
//	printf("local x in outer scope of main is %d\n", x); /*( A )*/
//	{/*start a new scope*/
//		int x = 7; /*��3��*/
//		printf("local x in outer scope of main is %d\n", x); /* ( B )*/
//	}/*end new scope*/
//	useLocal();/*(  C  )*/
//	useStaticLocal();/*( D )*/
//	useGlobal();/*( E )*/
//	useLocal();/*( F )*/
//	useStaticLocal();/*( G )*/
//	useGlobal();/*( H )*/
//	printf("\nlocal x in main is %d\n", x); /*( I )*/
//	system("pause");
//	return 0;
//}
//
//void useLocal(void)
//{
//	int x = 25; /*��4��*/
//		printf("\nlocal x in useLocal is %d after entering useLocal\n", x); /* ( C1,F1 )*/
//	x++;
//	printf("local x in useLocal is %d before exiting useLocal\n", x); /*( C2,F2 )*/
//}
//
//void useStaticLocal(void)
//{
//	static int x = 50; /*��5��*/
//		printf("\nlocal static x is %d on entering useStaticLocal\n", x); /*( D1,G1 )*/
//	x++;
//	printf("local static x is %d on exiting useStaticLocal\n", x); /*( D2,G2 )*/
//}
//
//void useGlobal(void)
//{
//	printf("\nglobal x is %d on entering useGlobal\n", x); /*( E1,H1 )*/
//	x *= 10;
//	printf("global x is %d on exiting useGlobal\n", x); /*( E2,H2 )*/
//}



///*2����Ŀ����ŵ������
//
//�������������ڵ����ӣ����ΪA��B��C��A�����ϴ��µ��ϰ�������״������n����ͬ��С��Բ�̣����ڰ���������һ��һ���ƶ�������C�ϣ�����ÿ���ƶ�ͬһ�������϶����ܳ��ִ�������С�����Ϸ����������������Ҫ���ٴ��ƶ��������ƶ���˳��
//
//����ɳ�����գ���д��2�����۲��������������ɱ�3�����ݱ�2��3��ʵ�������ش��3��������⡣
//
//ʵ���������ʾ��
//���Ȱ�����A����n-1�������ƶ�������B�ϣ�Ȼ�������һ�����C�ϣ�����B�ϵ����������ƶ���C�ϡ�*/
//
///*�����*/
//
//#include<stdio.h>
//#include<stdlib.h>
//
//void hanoi(int n, char A, char B, char C);/*1*/
//void move(char a, char b);/*2*/
//
//int count = 0;/*���㺯��hanoi�ĵ��ô���*/
//void main()
//{
//	int number;/*disk number*/
//	printf("please input the number of discs:\n");
//	scanf("%d", &number);
//	printf("the steps to moving is:\n");
//	hanoi(number, 'A', 'B', 'C');
//	printf("The complexity is %d\n", count);
//	system("pause");
//	return;
//}
//
//void hanoi(int n, char A, char B, char C)/*��n�����Ӵ�����A��������B�ƶ���C*/
//{
//	count++;/*3*/
//	if (n == 1)
//		move(A, C);
//	else  
//	{
//		hanoi(n - 1, A, C, B);/*4*/
//		move(A, C);
//		hanoi(n - 1, B, A, C);/*5*/
//	}
//}
//
//void move(char a, char b)
//{
//	printf("%c-->%c\n", a, b);
//}
//
//
//

///*3����Ŀ��������ֵ����
//�Ӽ������������������������ʵ�ֽ��佻����������������۲����3�����У���¼���н������������3�ܷ�ʵ����һ���ܣ���ɱ�4��*/
//
///*������*/
//
//#include <stdio.h>
//void Swap(int a, int b);
//int main()
//{
//	int a, b;
//	printf("Input a, b:");
//	scanf("%d %d", &a, &b);
//	Swap(&a, &b);
//	printf("In main():a = %d, b = %d\n", a, b);
//	return 0;
//}
//
//void Swap(int *a, int *b)
//{
//	int temp;
//	temp = *a;
//	*a = *b;
//	*b = temp;
//	printf("In Swap():a = %d, b = %d\n", *a, *b);
//}