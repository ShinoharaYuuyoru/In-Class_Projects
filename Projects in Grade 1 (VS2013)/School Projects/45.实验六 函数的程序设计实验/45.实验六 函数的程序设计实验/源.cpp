/*一、实验目的
通过对函数作用域的程序的分析、递归函数程序的填空和函数的值传递练习，认识函数中形参的作用域和递归的原理，理解函数中形参的正确使用、递归的正确使用和递归的优缺点。

二、实验内容

1、题目：观察程序中的各变量，分析函数中形参的作用域。
实验分析及提示：
本题目里，在程序的不同位置出现了不同的变量，这些变量的变量名都为x，在程序中用序号【1】【2】【3】......将其逐个标出。在每个变量x的后面都有一个printf 函数，对变量x进行屏幕显示，用序号A、B、C......将printf函数逐个标出。请观察C程序的输出结果，分析各printf语句打印出的结果对应哪个变量x，以及各变量x的作用域，填写表1。
本实验中x的变量类型包括：全局变量、局部变量、静态变量。*/

/*程序一*/
//
//#include <stdio.h>
//#include <stdlib.h>
//
//void useLocal(void);
//void useStaticLocal(void);
//void useGlobal(void);
//
//int x = 1; /*【1】*/
//int main(void)
//{
//	int x = 5; /*【2】*/
//	printf("local x in outer scope of main is %d\n", x); /*( A )*/
//	{/*start a new scope*/
//		int x = 7; /*【3】*/
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
//	int x = 25; /*【4】*/
//		printf("\nlocal x in useLocal is %d after entering useLocal\n", x); /* ( C1,F1 )*/
//	x++;
//	printf("local x in useLocal is %d before exiting useLocal\n", x); /*( C2,F2 )*/
//}
//
//void useStaticLocal(void)
//{
//	static int x = 50; /*【5】*/
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



///*2、题目：汉诺塔程序
//
//现在有三根相邻的柱子，标号为A，B，C，A柱子上从下到上按金字塔状叠放着n个不同大小的圆盘，现在把所有盘子一个一个移动到柱子C上，并且每次移动同一根柱子上都不能出现大盘子在小盘子上方，程序求出至少需要多少次移动和盘子移动的顺序。
//
//请完成程序填空，填写表2，并观察程序输出结果，完成表3。根据表2表3的实验结果，回答表3后面的问题。
//
//实验分析及提示：
//首先把柱子A上面n-1个盘子移动到柱子B上，然后把最大的一块放在C上，最后把B上的所有盘子移动到C上。*/
//
///*程序二*/
//
//#include<stdio.h>
//#include<stdlib.h>
//
//void hanoi(int n, char A, char B, char C);/*1*/
//void move(char a, char b);/*2*/
//
//int count = 0;/*计算函数hanoi的调用次数*/
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
//void hanoi(int n, char A, char B, char C)/*把n个盘子从柱子A借助柱子B移动到C*/
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

///*3、题目：函数的值传递
//从键盘任意输入两个整数，编程实现将其交换后再重新输出。观察程序3并运行，记录运行结果，分析程序3能否实现这一功能，完成表4。*/
//
///*程序三*/
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