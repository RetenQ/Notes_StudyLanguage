#include <stdio.h>
//C的编译器是由上而下来分析代码的，和eclipse不一样，这导致你要用的函数需要在前面先写出来
//这个在各编译器是不一样的，不过还是建议用的先写在前面

//但是可以把函数头加上分号放在前面，其它部分放在后面，这样就可以了。这个做法叫做  原型声明 
void sum (int a , int b);  //声明 

int main ()
{
	sum(1,10);
	; return 0 ; 
}

void sum (int a, int b){  //定义 
	int i ; 
	int sum = 0 ; 
	for (i =a ; i <=b ; i ++){
		sum +=1 ;  
	}
}

//另外，原型声明里面可以只给参数类型，不给参数名字。因为原型声明的意义就是让编译器知道有这个东西 
