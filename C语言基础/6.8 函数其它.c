#include <stdio.h>
void swap(); //原型声明

int main(void){
	int a = 5 ; 
	int b = 6 ; 
	
	//原型声明的时候外面没有指定参数，在这里外面尝试传入两个int
	swap(a,b); //而事实上，我们的函数会对两个double进行处理，因此结果会出错（但是运行是正常的）
	printf("a = %d , b = %d \n",a,b);
	
	
	;return 0 ; 
}

//注意这里给的是double
void swap (double a , double b){
	int t = a ; 
	printf("IN SWAP,a = %f , b = %f  \n",a,b);
	a = b ; 
	
	b = t ; 
}

/*  其它
	1.
	void f(void) 表示f函数没有参数
	void f()      表示f函数的参数表未知（传统C） 
	
	2.
	逗号在圆括号内算作标点符号，而不是运算符。
	f(a,b) 传入a,b
	f((a,b))  传入(a,b)，此时我们要的是(a,b)而非a,b。因此逗号会被当作运算符被使用
	
	3.C语言不允许在函数里面定义函数

*/
