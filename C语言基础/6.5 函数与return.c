#include <stdio.h> 、
//当使用void类型的函数时，函数是没有返回值的，也就是可以没有return 
int max (int a,int b)
{//返回值是int类型的函数max 
	int ret ; 
	if(a>b){
		ret = a ; 
	}else {
		ret = b ; 
	}
	return ret ; //返回一个ret的数值，另外在一个函数里面可以有多个return语句，而且return不一定要在尾（不过这不是单一出口，习惯不好） 
}

int main () {
/* return 
1.return 会停止函数的运行，并且返回一个值
2.写法  return <值> ;  或者  return[表达式] ;
 
*/
int a,b,c ; 
c = max(12,10);
printf("%d \n ",c);


return 0 ; 
}

