---
title: 【基础C语言】一、基础操作 #文章页面上的显示名称，一般是中文
date: 2022-03-07 16:00:00 #文章生成时间，一般不改，当然也可以任意修改
categories: 语言学习 #分类
tags: C #文章标签，可空，多标签请用格式，注意:后面有个空格
description: C语言最基础的操作,包含Hello World , 输出输入 , 判断与循环语句的操作
keywords: #文章关键字
top_img: #文章顶部图片
cover: https://s2.loli.net/2022/03/07/Ncstf6qdIUK9QpL.jpg #【可选】文章缩略图(如果没有设置top_img,文章页顶部将显示缩略图，可设为false/图片地址/留空)    
---
# 一、基础操作
本文包括C语言的基础操作，如果您已经学过其他语言，建议跳过或者迅速浏览即可   

## 起手式Hello World
```C
#include <stdio.h>

int main()
{
	printf("Hello \nWorld!")
	
//  \n是换行符号，注意是\n  不是/n 
	
; return 0;
}
```
所有语言开始的仪式     
在C里面，利用printf打印/输出我们想要的东西 

## 基础运算和输入输出

### 运算
加减乘除和小学数学没什么两样。这里主要讲讲新东西。
```/```：除，得到的a/b的整数，比如5\2=2  
```%```:取余，这家伙得到的就是余数了，比如5%2=1  

```c
#include <stdio.h>

int main()
{
	printf("7/5=%d",7/5) //%d代表输入“”，后面的运算。符号+-*/是加减乘除 %是取余 （）是括号 
    //%取余表示取两个数相除之后的余数，且只会显示余数
	
; return 0;
}
```

```+-*/%运算符```可以和```=```连用，达到复合运算的目的   
```A+= 5``` 实质上是和 ```A= A+5```是相同的，注意前者的+=之间是不能有空格的  
同理，```A*= B+12``` 实质等同于 ```A= A*(B+12)```  

常用的是++和--，```a++```就是```a+=1```也就是```a=a+1``，减法同理  
a++和++a有细微的差别    
```c
#include <stdio.h>

int main()
{
   int a;
   a = 10;
   
   printf(" 这个是a++的式子 %d \n", a++);
   printf("而结果是 a= %d  \n",a);
   
   printf(" 这个是++a的式子 %d \n", ++a); 
   printf("而结果是 a= %d  \n",a); 

   	;return 0;
} 
```

### 用scanf进行输入
```scanf("%d",&price);```   

我们使用 scanf 把一些东西输入，这里表示把```""```中的结果赋值给price变量，注意变量前的&要打
> 至于&是什么呢，这个要到指针部分我们再细说
可以同时定义多个输入量，每一个%d和之后所写的变量的**一一对应**  

```C
#include <stdio.h>

int main()
{
	int price=0; //定义了一个变量，名字是price，类型int，初始值是0
	
	
	printf ("请输入金额");
	scanf("%d",&price);

	// scanf("%d %d",&a,&b); 可以同时定义多个输入量

	int change=100-price;
	//定义了第二个变量，并且还做了计算 
	//100是常量，为了方便修改的话我们也可以给常量整一个名字 const int AMOUNT= 100即可 
	//const为修饰符，加在int前面时代表给变量一个不变的属性，在初始化后，该变量的值便不能修改 
	
	printf("找您%d 元",change)
	
	;return 0 ;
 } 
```  

### 变量、赋值、初始化
变量定义的一般形式是 ```<变量类型><变量名称>;```  如```int price;```    
每一个变量都有一个唯一的标识符，只能由字母、数字、下划线组成，且数字不能在第一个位置。
> 标识符，通俗的说就是变量的名字。关键字不能作为标识符，比如你不能int int = 1

所有变量必须有确定的数据类型，表示变量中可以存放什么类型的数据，运行过程中不能改变类型
>C99可以在变量使用前定义它都可以，而传统的ANSI C只能在代码开头定义变量

```C
#include <stdio.h>

int main()
{
	int price=0; //定义了一个变量，名字是price，类型int，初始值是0
	//int A,B 可以同时定义两个为A,B的变量，类型同为int 

	//C语言的关键字不能做标识符 

	printf ("请输入金额");
	scanf("%d",&price);
	
	int change=100-price;
	//定义了第二个变量，并且还做了计算 
	
	printf("找您%d 元",change)
	
	;return 0 ;
 } 
```

### 浮点数
我们使用整型int进行运算时，结果只会是**整数**  
想要得到小数部分，我们需要浮点数  

这里先介绍两种浮点数已经符号：  
float:单精度浮点数，使用float时，用%f     
double:双精度浮点数，使用double时，用%lf     

```C
#include <stdio.h>

int main()
{
	printf("第一行整数的测试%d     ",10/3);
	
	printf("第二行浮点数的测试%f",10.0/3); 
	//此时的%f与10.0一起表示出了浮点数。让计算可以延续至小数 
	//当浮点数和整数放到一起运算的时候，C会把整数转化成浮点数，然后进行浮点数的运算 
	
	;return 0;
 }
 
 //double“双”是“双精度浮点数”的第一个单词，另外float（浮点）表示单精度浮点数 
 //使用double时，用%lf 

```

double可表示的范围比float更大，吃的内存也比它多
各个变量范围的区别和用法之后再提   

### 小结：一个使用输入框和结果的例子
```C
#include <stdio.h>

int main()
{
// 运算符是指进行运算的的动作，比如加法运算符是 +，另外=也是运算符 
//算子是指参与运算的值，可能是常数、变量、一个方法的返回值 

int hour1,minute1;
int hour2,minute2;

printf("请输入“第一个小时的时分”如一点三十为 1 30  "); 
scanf(" %d %d",&hour1,&minute1);
printf("请输入“第二个小时的时分”如三点三十为 3 30  "); 
scanf(" %d %d",&hour2,&minute2);
	
int time1=hour1*60+minute1;
int time2=hour2*60+minute2;
int t=time2-time1;
printf("时间差是%d小时%d分钟。",t/60,t%60);
	;return 0 ;
 } 
```  

## 判断语句与循环语句
了解了判断语句和循环语句，再加上输入输出，差不多已经完成最最基础的入门了    

### 判断语句
#### 基础
我们利用if语句进行判断      
if语句的标准写法：  
```C
if(条件成立){
    ... 
    }    
```  

判断条件：
判断的条件的符号如下:    
	== 相等   
    ！=不相等 
	> 大于    
    >= 大于或等于 
	<小于     
    <= 小于或等于   

注意，在C里面，判断的结果并不是布尔值(true,false)，而是1和0  

我们使用```else语句```，表示除了if条件之外的情况下所做的操作  

**代码实例**:  
```C
#include <stdio.h>
int main()
{
int price=0;
int bill =0;

printf("请输入金额 ");
scanf("%d",&price); 
printf("请输入票面 ");
scanf("%d",&bill); 

if(bill>=price)     //注意了，if和else的分号;不写在小括号后面，因为这不是他们真正“结束”的地方 
{
	printf("应该找您： %d \n", bill-price);
}

/*当判断运算符输出不为0时，会执行大括号内的语句，否则执行else语句。
if+else判断完之后，之后的语句照常进行 */
 
else {
	printf("你的钱不够  \n"); 
}

printf("执行结束"); 

; return 0 ;
}
```  

if和else有另外一种不用大括号的写法，但是为了可读性一般不建议使用  
```C
	if(hours>STANDARD)
	  pay=STANDARD*RATE+(hours-STANDARD)*(RATE*1.5);
	
	else
	pay=hours*RATE;
```

#### 嵌套
不管是if语句还是if-else语句，我们都可以进行嵌套  
什么是嵌套呢，见到来说就是一个判断语句中再次使用判断语句

```C
#include <stdio.h>
int main()
{
	int a,b,c;
	printf("请输入三个数字") ;
	scanf("%d %d %d",&a,&b,&c) ;	
	int max=0;
    //当if的条件满足或不满足时，执行的语句可以是一条if或者一套if-else语句，这就是嵌套的if语句 
	if(a>b)	{
		if(a>c){
			max=a;
		}else {
			max=c;
		}
    }else{
			if(b>c){
				max=b;
			}
		else{
		max=c;
		}
	}
	// !!! 简洁版的else总是和最近的if相匹配！而完整版的（有大括号）是根据大括号的划分的范围匹配的！
	//在C中缩进格式并不能暗示else的匹配
	printf("The max is %d \n",max);
	; return 0 ;
}
```

#### 级联
if 后的else语句可以直接再接if语句，就是```else if语句```  
```else if()```表示，在第一句条件不成立的情况下，再次进行判断   
```C
#include <stdio.h>

int main(void)
{ 
int x ;
int f = 0;
scanf("%d",&x);
    if(x<0) {
    	f = -1;
	}else if (x==0){
		f = 0;
	}else if (x>5){
		f=2*x;
	}else {
		f=3*x;
		
	}
	
	printf("%d",f)
	;return 0 ;
 }
```  

#### switch case 多路分支
可以使用swtich case 来减少一些if else的工作量  
这里的工作量指的是你复制粘贴的工作量  
在很多时候，```switch case```开销略大，且有很多要注意的细节，因此反而比```if-else```少用

```C
switch( type ){
    ...
}
```

type表示的是当前判断的变量的值

```C
case <常量> ： 常量可以是常数，也可以是只含常数运算的表达式） 
语句...（一般以break结尾）
break; 
```
利用case来对各种情况进行分析

一个switch-case的使用实例如下:
```C
#include <stdio.h>
int main (void){
	int type;
	scanf("%d",&type);
	 
	switch( type ){
		//根据switch(控制表达式子)，控制表达式只能是整数型的结果！ 
		//括号中的值判定接下来的语句，括号中可以是变量，可以是式子。都不符合就输出default。 
		case 1: 
			printf("这是case 1");
			break ; 
		case 2:
			printf("这是case 2");
			break ; 
		case 3:
			printf("这是case 3");
			//break ; 注意这个break被注释删掉了，case=3时会执行3然后到执行case4后停止！ 
		case 4:
			printf("这是case 4");
			break ; 
	
	default:
		printf("阿这，这不是case1234");
		//最后以default结尾来对应其他情况。 
			}
	
	;return 0 ;
}
```
>case只是一个路标，并不会自动停止。甚至会运行到下一条case里面去执行句子（按排序的顺序）
>这个动作会直到遇到一个break或者到达switch结束，才会停止下来。

### 循环语句
#### while循环  
最最基本的循环，生动形象地表现了“当...时，一直...”的思想  

```C
while(条件){
    执行的语句
}
```
在执行语句中要有改变条件的语句，不然就是死循环  

#### do-while 循环
和上面那位没什么区别，主要在于：
while是先判断条件，在决定要不要执行语句  
do-while是**无论怎样先执行一次**，执行完再判断  
```C
	do{
	   循环体语句 
	}while (循环条件);
```

#### for循环 
for循环和while循环是等价互通的  

```C
for(初始条件;继续循环的条件;参数更新){
    执行语句
}
```
比如：
```C
for (i=1;i<=10;i++){
    printf("123");
}
```
#### 循环嵌套
和判断语句一样，循环是可以嵌套使用的  

#### 小结与实例  
```C
#include <stdio.h>
int main (void)
{
int count = 100;
while (count > 0) {
	printf("%d  \n",count);// a
	count--;               //b
}	
	printf("发射！\n"); 
//当我们想要模拟测试一个比较大的循环时，可以采用一个小的数进行实验。 
//比如我们想要知道ab顺序带来的不同时，可以先用count = 3 进行测试。 
	;return 0;
 } 
```

#### 循环中的break与continue
这是两个可以表示结束循环的句子  
**break**:表示结束循环，直接结束循环跳出循环  
**continue**：结束本次循环，不执行接下来的语句直接进行下一次循环  

实例：  
```C
#include  <stdio.h>
int main (void){
	int x ; 
	scanf ("%d",&x) ; 
	
	int i ;
	int k =0 ;//设置一个数值k来勇于判断最后的文字输出 
	if(x ==1){
		printf("1就是1");//1的情况 
	}else if (x<1){
		printf("EOORO"); //错误的情况 
	}else{
	
		for(i=2;i<x;i++){ //从2开始到x-1 
			if(x%i == 0) {
			k =1;	
			break; //!!在循环里面，运行至break时，结束该次循环（在这里加入是为了防止重复运算） 
			//continue :跳过循环这一轮剩下的语句进入下一轮（不做接下来的语句，回到循环开头） 	
			}
			printf("%d \n",i);
	} 
	if (k==1) printf("不是素数");
	else printf("是素数") ;
    }
	
	;return 0 ;
} 
```