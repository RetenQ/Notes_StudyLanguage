# 顺序表(线性) 
## List模板 
```c
# define MAXSIZE 100    
typedef struct {
    ElemType elem [MAXSIZE] ; // 真正存数据的数组   
    int length ;// 存储当前长度 
}
``` 

类似的，也可以使用动态数组的方式来动态分配内存  
```c
# define MAXSIZE 100    

typedef struct{
    ElemType *elem ; 
    int length ; 
}SqList ; 

SqList L ; 
L.elem = (ElemType*)malloc(sizeof(ElemType)*MAXSIZE) ;
```

## 预定义常量   
```c
// 预定义结果状态代码   
#define TRUE 1 
#define FALSE 0 
#define OK 1 
#define ERROR 1 
#define INFEASIBLE -1 
#define OVERFLOW -2 

// Status 是函数的类型，其值是函数结果状态代码  
typedef int Status ;
typedef char ElemType ; 
``` 

> C语言实现见相关c文件

## 实现(陈越版，且1为下标)
```c
# include <stdio.h>
# include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define ERRORPOS NULL ;
#define NOFIND NULL ;
#define INFEASIBLE -1
#define OVERFLOW -2
#define bool int ;

// Status 是函数的类型，其值是函数结果状态代码
typedef int Status ;
typedef int ElementType  ;

# define MAXSIZE 100

// 以1为下标的版本
typedef int Position ; 
typedef struct LNode * PtrToLNode ; // 
typedef PtrToLNode List ; // 定义为一个指向结构的结构指针，方便后续使用

struct LNode
{
    ElementType Data[MAXSIZE] ; 
    Position Last ; // 最后的下标，Length = Last - 1 
};

List InitList(){
    List l ; 

    l = (List)malloc(sizeof(struct LNode)) ; 
    l -> Last = -1 ;  // 初始下标是-1，因为该部分也不会放入数组
    return l  ;
}

Position Find(List L , ElementType X){
    // 按照元素查找
    Position i = 0 ; 
    while (i <= L->Last  && L->Data[i] !=X)
    {
        // 首先要找到，其次找到了就跳出来
        i++ ; 
    }
    
    // 通过实际情况返回
    if(i > L->Last) {
        // 越界了就是没找到了
        printf("没有找到") ; 
        return -1 ; 
    }else{
        return i ; //返回存储位置   
    }
}

// 插入
// 插入是指在表的第i个位次上加入一个新元素，或者说在第i个元素之前插入新元素
// 1.将第i到n个元素顺序后移， 2.将X元素插入第i个次序  ， 3.修改Last

bool Insert(List L  , ElementType x , int i ){
    Position j ; 
    if(L->Last == MAXSIZE -1 ){
        // 表空间已经满了
        printf("表空间已满");
        return FALSE ; 
    }

    if(i<1 || i > L->Last+2){
        printf("插入位次不合法"); // 注意，这是插入0也是不合法的。因为是从1开始算的（数组是从0开始算的）
        return FALSE ; 
    }

    for(j = L->Last ; j >= i-1 ; j--){
        L->Data[j+1] = L->Data[j] ; // 开始移动，方式是将j的元素移到j+1,知道i-1为止（此时把i-1移动到了i）
    }

    // 进行插入操作 
    L->Data[i-1] = x ; 
    L->Last++ ; 
    return TRUE ; 
}

// 删除 
// 设在i位置的元素被删除 1.把i+1 - n 的元素向前移动， 2. ai被ai+1覆盖 ， 3.修改Last

int Delete(List L ,int i ){
    Position j ;

    if(i <1 || i > L->Last+1){
        printf("位次错误");
        return FALSE ;
    }

    for(j = i ; j <= L->Last ; j++){
        L->Data[j-1]  = L->Data[j] ; 
    }

    L->Last -- ; 

    return TRUE; 
}

// 带取出
int Delete(List L ,int i ,int* data){
    // 这里还附带一个取出
    Position j ;

    if(i <1 || i > L->Last+1){
        printf("位次错误");
        return FALSE ;
    }

    data = L->Data[i] ; 

    for(j = i ; j <= L->Last ; j++){
        L->Data[j-1]  = L->Data[j] ; 
    }

    L->Last -- ; 

    return TRUE; 
}

int main(){
    List l = InitList() ; 

    return 0 ;

}

```

## 实现(0为下标) 
```c
# include <stdio.h>
# include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 1
#define INFEASIBLE -1
#define OVERFLOW -2

// Status 是函数的类型，其值是函数结果状态代码
typedef int Status ;
typedef int ElemType ;

# define MAXSIZE 100

typedef struct{
    ElemType elem[MAXSIZE] ;
    int length ;
}SqList ;

// 基础操作=================================
// 线性表初始化
Status InitList_Sq(SqList *L){

    // int temp [MAXSIZE] ;
    // L->elem = temp ;
    // if(!L->elem) {
    //     exit(OVERFLOW) ;
    // }


    L->length  = 0 ;

    return OK ;
}

// 销毁
void DestoryList(SqList *L){
    if(L->elem) {
        free(L->elem) ;
    }
}

// 清空
void ClearList(SqList *L){
    L->length = 0 ;
}

int GetLength(SqList *L){
    return L->length ;
}

int isEmpty(SqList *L){
    // return (L->length == 0) ;

    if(L->length == 0){
        return 1 ;
    }else{
        return 0 ;
    }
}

// 基本操作=================================
// 取值
int GetElem(SqList L , int i , ElemType *e){
    if(i < 0 || i >=  L.length )  {
        printf("ERROR !");
        return ERROR ; //如果越界
    }
    // 这里认为下标都是由0算起

    // printf("get : %d" ,L.elem[i] );
    *e = L.elem[i] ; // 获得元素，通过指针放到e里面去
    return OK ;
}

// 查找
int LocateElem(SqList L ,ElemType e){
    int i ;
    for(i = 0 ; i < L.length ; i++){
        if(L.elem[i] == e) return i ; // 这里因为都是按0作为下标，因此返回i即可
    }

    return -1 ; // 查找失败返回-1
}

// 插入有不同的情况，包括在最后，在中间，在最前面
// 第二是表已经满了，这时候要考虑溢出情况
// 1.插入的位置是否合法  2.判断空间是否已经已满 3.插入到i，将n到i位的元素都依次向后移动一个位置，然后放入并让length+1

Status ListInsert_Sq(SqList *L , int i , ElemType e){

    // 这里要用指针引用SqList以改变其内部情况


    if(i < 0 || i >= L->length+1 ) return ERROR ;

    if(L->length == MAXSIZE) return ERROR ;
    int j ;

    for(j = L->length -1 ; j >= i ;j--){
        L->elem[j+1] = L->elem[j] ;

    }


    L->elem[i] = e ;

    L->length++;

    return OK;
}

// 线性表删除
// 删除指的就是把第i个结点删除，使长度为n的线性表变成长度为n-1的表
// 1.判断删除位置是否合法  2.将删除的元素保留到e中(可选) 3.将i+1到n的元素全向前移动一个单位，length--
Status ListDelete_Sq(SqList *L , int i){
    printf("DL : %d , length : %d \n" , i , L->length) ;
    if(i < 0 || i >= L->length ) {
         // 都是从下标0开始记的，所以最大删除第length-1位
        printf("Error!");
        return ERROR ;
    }
    int j ;
    int length = L->length ;
    int theMin = length -1 ;
    for(j = i ; j<= theMin ; j++){
        L->elem[j] = L->elem[j+1] ;
    }


    L->length--; // length--就相当于处理掉最后一位了

    printf("删除后的length: %d \n" , L->length) ;

    return OK ;
}


// ============================
// 这是写的测试遍历的函数
void TestList(SqList *L){
    int i ;
    int length = L->length ;
    int temp = 0 ;
    for(i = 0 ; i < length ; i++){
        GetElem(*L,i,&temp);
        printf("%d ",temp);
    }

    printf("\n  Now Length : %d  \n" , length);

}

/*遍历操作*/
void PrintList(SqList *l)
{
	for (int i = 0; i < l->length; i++)
		printf("%d ", (l->elem[i]));
}

int main(){
    int i ;
    SqList L ;
    InitList_Sq(&L) ;  // 初始化
    //TestList(&L);
    for(i = 0 ; i <= 10 ; i++){
         ListInsert_Sq(&L , i , i) ; //插入
    }

    TestList(&L);

    printf("测试把-1插入到下标为1的位置 \n");

    ListInsert_Sq(&L , 1 , -1);
    TestList(&L);

    printf("测试把-2插入到下标为3的位置 \n");
    ListInsert_Sq(&L , 3 , -2);
    TestList(&L);

    printf("\n");

    printf("删除第0位，第3位的元素，最后一位（依次） \n");

    ListDelete_Sq(&L , 0);
    TestList(&L);
    ListDelete_Sq(&L , 3);
    TestList(&L);
    ListDelete_Sq(&L , L.length-1);
    TestList(&L);


     //PrintList(&L);


    return 0 ;

}
``` 

## 小结 
查找、插入、删除算法的平均时间复杂度是O(n)  
顺序表操作算法的空间复杂度S(n) = O(1),其没有占用辅助空间    

优点:   
1.存储密度大 （结点本身所占存储量 / 结点结构所占存储量）    
2.可以随机存取表中任一元素  

缺点：  
1.插入、删除某一元素时，需要移动大量元素    
2.浪费存储空间  
3.属于静态存储形式，数据元素的个数不能自由扩充  

# 顺序表（链式）  
用一组物理位置任意的存储单元来存放线性表的数据元素  
这组存储单元既可以是连续的，也可以是不连续的，甚至是零散分布在内存的任意位置上的    
链表元素的逻辑次序和物理次序不一定相同  

各个结点由两个域组成：  
1.数据域：存储元素数值数据  
2.指针域：存储直接后继结点的存储位置    

结点只有一个指针域，称为单链表；有存前后两个指针域的，称为双链表；首尾相接的链表尾循环链表  

无头结点时，头指针为空时表示空表；有头结点时，当头结点指针域为空时表示空表  

## 实现 
注：该实现中默认第一位为空的头结点0 

```c
# include <stdio.h>
# include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 1
#define ERRORPOS NULL ;
#define NOFIND NULL ;
#define INFEASIBLE -1
#define OVERFLOW -2
#define bool int ;

// Status 是函数的类型，其值是函数结果状态代码
typedef int Status ;
typedef int ElementType  ;

# define MAXSIZE 100

typedef struct LNode * PtrToLNode ;

struct LNode
{
    ElementType Data ;
    PtrToLNode  Next ;
};

typedef PtrToLNode Position ; // 结点的地址
typedef PtrToLNode List; //

// 基础操作
List InitList(){
    List tmpL = (PtrToLNode)malloc(sizeof(PtrToLNode)) ;
    tmpL->Next = NULL ;// 最开始的“下一个”是NULL
    return tmpL ;
}

// 求表长
int getLength(List L){
    Position p ;
    // ! 注意，List L是头指针，是不可以动的，因此需要另外一个指针来协助进行遍历
    int cnt = 0 ;
    p = L ; // 利用一个指针p进行遍历

    while (p)
    {
        p = p->Next;
        cnt++ ;
    }

    return cnt;

}

// 序号查找(获得元素)
ElementType FindKthEle(List L , int k){
    Position p ;
    int cnt = 1 ; // 位序从1开始
    p = L ;  // p指向L的第1个节点

    while (p && cnt < k)
    {
        p = p->Next;
        cnt ++ ;
        // 一直向前计直到到达第k个
    }

    if((cnt == k) && p ){
        return p->Data ; // 返回数据
    }else{
        return FALSE ;
    }

}

// 序号查找(获得地址)
Position FindKthPos(List L , int k){
    Position p ;
    int cnt = 1 ; // 位序从1开始
    p = L ;  // p指向L的第1个节点

    while (p && cnt < k)
    {
        p = p->Next;
        cnt ++ ;
        // 一直向前计直到到达第k个
    }

    if((cnt == k) && p ){
        return p ; // 返回数据
    }else{
        printf("该地址查找失败");
        return NOFIND ;
    }

}


// 按值查找(获得地址)
Position FindElem(List L , ElementType X){
    Position P = L ;

    while (P && P->Data != X)
    {
        P = P->Next ;
    }

    // 跳出循环有两个情况，一是到头了，二是找到了
    if(P && P->Data == X){
        // P还有指向，那就是找到了
        return P;
    }else{
        return NOFIND ; //没找到，就返回NULL
    }

}

// 插入和删除

// 插入操作
// 1.构造应该新结点，用S指向 2.找到链表的第i-1个结点，用P指向 3.修改指针（利用P指针），完成插入

List InsertSelf (List L , ElementType X , int i ){
    // 这里是不使用“Findkth”的查找法
    Position tmp , pre ;

    // 准备新结点
    tmp = (Position)malloc(sizeof(struct LNode)) ;
    // 这里要拿到的空间是结点，不是数据元素，注意了
    tmp->Data = X ;

    // 表头插入，插表头，返回新表头的Node
    if(i == 1 ){
        tmp->Next = L ; // 指向原表头
        return tmp ;  // 插入的元素成为了新表头
    }else{
        // 查找i-1位置的结点，即FindKth(i-1 , L) ;
        int cnt = 1  ; pre = L ;
        while (pre && cnt < i -1 )
        {
            pre = pre -> Next ;
            cnt++ ;
        }

        if(pre == NULL || cnt != i-1){
            printf("查找失败") ;
            free(tmp) ;
            return NULL ;
        }
        //==============================================
        else{
            // 成功查找到，按计划进行插入
            tmp -> Next = pre -> Next ;
            pre -> Next = tmp ;

            return L ; //
        }
    }
}

// 调用了FindKth的插入算法
List InsertKth (List L , ElementType X , int i ){
    // 这里是不使用“Findkth”的查找法
    Position tmp , pre ;

    pre = L ; // 设置pre为表头（如果tmp）

    // 准备新结点
    tmp = (Position)malloc(sizeof(struct LNode)) ;
    // 这里要拿到的空间是结点，不是数据元素，注意了
    tmp->Data = X ;

    // 表头插入，插表头，返回新表头的Node
    if(i == 1 ){
        tmp->Next = L ; // 指向原表头
        return tmp ;  // 插入的元素成为了新表头
    }else{
        pre = FindKthPos(L , i-1) ;
        if(pre == NULL){
            return NULL ; //查找失败
        }
        else{
            // 成功查找到，按计划进行插入
            tmp -> Next = pre -> Next ;
            pre -> Next = tmp ;

            return L ; //
        }
    }
}

// 带头结点的插入方式
// 这种插入方式可以保证无论在哪里插入或者删除，L的值一直有指向固定的空的结点
int Insert(List L , ElementType X , int i){
    // 默认头结点是已经被初始化过的
    Position tmp,pre ;

    // 查找i-1结点
    pre = FindKthPos(L , i-1) ;

    if(pre == NULL){
        //没有找到
        printf("插入位置参数错误\n") ;
        return FALSE ;
    }else{
        // 找到的情况
        tmp = (Position)malloc(sizeof(struct LNode)) ;
        tmp->Data  = X ;
        tmp->Next = pre->Next ;
        pre->Next = tmp ;

        return TRUE ;
    }
}


// 删除操作
// 1. 找到链表的第i-1个结点，用p指向  2.再用一个辅助指针s指向要删除的结点  3.修改指针完成删除操作  4.释放s所指结点的空间（也就是释放被删除掉的结点的空间）
int Delete(List L , int i){
    // 这里是默认有头结点的
    Position s , pre ;

    /* 查找位序为i-1的结点 */
    pre = FindKthPos(L , i-1) ; //

    if(pre == NULL || pre->Next == NULL){
        // 如果删除的结点没找到（pre的next是NULL，也是代表没找到要删的东西）
        // 这个比插入的时候多了一个条件判断
        printf("删除位置参数错误") ;
        return FALSE ;
    }else{
        // 找到
        s = pre->Next ; //用s指向要删除的地方，为了之后可以free
        pre->Next = s->Next ; // 将删除元素的后面的元素连在它前面的元素上
        free(s) ; //free删除的元素
        return TRUE ;
    }
}


void ShowList(List L ){
    Position p = L  ;
    printf("===================================== \n");

    while(p){
        int tmp = p->Data ;
        printf("%d -> " , tmp );
        p = p->Next ;
    }

    printf("\n===================================== \n");

}


int main(){
    List l = InitList();

    printf("t") ;
    l->Data = 0 ;

    printf("测试初始长度: N1 : %d （含头结点） \n" , getLength(l));
    ShowList(l);

    printf("测试插入(都以带头结点的插入删除为准)");
    InsertSelf(l,123,2); //
    ShowList(l);
    InsertKth(l,456,3);
    ShowList(l);
    Insert(l,789,4);
    ShowList(l);
    Insert(l,1357,5);
    ShowList(l);
    Insert(l,2468,6);
    ShowList(l);
    printf("额外测试：在第3位插入333 \n");
    Insert(l,333,3);
    ShowList(l);
    printf("测试初始长度: N1 : %d （含头结点） \n" , getLength(l));
    printf("依次删除第二位，第四位 \n");
    Delete(l,2);    ShowList(l);
    Delete(l,4);    ShowList(l);

    return 0 ;
}

```

# 广义表    
是线性表的一种推广  
可以理解为一个既可以存储元素（原子），也可以存储另外一个表（子表）的特殊的表    
通常用链式表的结构来实现广义表  

## 概念 
广义表通常记成 LS = (a1,a2,...,an) ;    
LS是**表名**,n是表的长度，每一个ai为表的元素    
**表头：**若LS非空，那么第一个元素a1是表头（表头可以是原子，也可以是子表）
**表尾：**除表头以外，其它元素组成的一个表  
> 也就是说，表尾不是最后一个元素，而是一个子表  

**长度：**最外层所包含的元素的个数  
**深度：**广义表展开后所含括号的重数【B=((b,c),d)，深度为2】    
原子的深度为0，空表的深度为1，长度为0   
广义表可以是一个递归的表，比如F=(a,c,F) ,递归表的深度是无穷值，长度是有限值 


其结构类似于：  
```c
typedef struct GNode * PtrToGNode ; 
typedef PtrToGNode GList ; 

struct GNode
{
    int Tag ; //0表示是单元素，1表示是表

    union 
    {
        ElementType Data ; 
        GList SubList ; 
    } URegion;

    PtrToGNode Next ; //指向后继结点    
};
```

# 多重链表  
存在“链表中的结点可能同时于多个链”的情况的结点链表是多重链表    
多重链表中结点的指针域会有多个，但是包含了两个指针域的链表不一定是多重链表      

多重链表有广泛的用途，比如树、图等，这个见相关的笔记部分    

# 栈    
Stack:有一定操作约束的线性表    
插入数据是Push，弹出数据是Pop   
是一种后入先出LIFO的数据结构    

栈的存储结构可以采用顺序和链表两种形式：顺序存储的栈是**顺序栈**，链式存储的栈是**链栈**    

## 顺序栈   
顺序栈主要依靠一个一维数组和一个记录栈顶元素的下标值决定    

```c
# include <stdio.h>
# include <stdlib.h>

#define FALSE -1 ;
#define TRUE 1   ;
#define ERROR -1 ;

typedef int ElementType ;
typedef int bool ;

typedef int Position ;
typedef struct SNode * PtrToSNode ;

struct SNode
{
    ElementType* Data ; // 一个存储元素的数组
    Position Top ; //指向栈顶的指针（注意它的作用就是指向栈顶，而非表示长度
    int MaxSize ; //最大容量

};
typedef PtrToSNode Stack ; //之后可以直接用Stack

// 初始化
Stack InitStack(int MaxSize){
    Stack s = (Stack)malloc(sizeof(struct SNode)) ; // 这个只是为了创建Stack本体，因此不用*MaxSize ;
    s->Data = (ElementType*)malloc(sizeof(ElementType) * MaxSize) ;// 创建数组
    s->Top = -1;
    s->MaxSize = MaxSize ;

    return s ;
}


// 检查函数
bool isFull(Stack S){
    return (S->Top >= S->MaxSize -1 ) ;
}

bool isEmpty(Stack S){
    return (S->Top == -1);
}

// Push
bool Push(Stack S , ElementType x){
    if(isFull(S)){
        printf("栈满\n");
        return FALSE ;
    }else{
        S->Data[++(S->Top)] = x ;
        /*
            S->Top++ ;
            S->Data[s->Top] = x  ;
        */
        return TRUE ;
    }
}

// Pop
ElementType Pop(Stack S){
    if(isEmpty(S)){
        printf("堆栈空\n") ;
        return ERROR;
    }else{
        return S->Data[(S->Top)--] ; // 记住要先return后--
        /*
            ElementType tmp = S->Data[S->Top] ;
            S->Top-- ;
            return tmp ;
        */
    }
}

// 测试函数
int main(){
    Stack S = InitStack(1000) ;
    printf("进行01234插入操作\n");
    int k = 0 ;
    for(k = 0 ; k < 5 ; k++){
        Push(S,k) ;
    }

    printf("进行Push六次\n");
    for(k = 0 ; k < 6 ; k++){
        int tmp = Pop(S) ;
        if(tmp == -1){
            printf("取出失败");
        }else{
            printf("此次取出： %d \n" , tmp);
        }
    }

    return 0 ;
}

```

## 链式表   
链式存储的栈，其实就是一个单链表，只是插入和删除的操作受到了限制    
这里的实现默认第一个结点即为栈顶    
(如果使用链尾作为top，因为这是个单向链表，所以无法在删除的时候正确找到求一个结点，所以用第一个结点作为top)  

实现如下：  
```c
# include <stdio.h>
# include <stdlib.h>

#define FALSE -1 ;
#define TRUE 1   ;
#define ERROR -1 ;

typedef int ElementType ;
typedef int bool ;

typedef struct SNode * PtrToSNode ;
struct SNode
{
    ElementType Data ;
    PtrToSNode Next ;
};

typedef PtrToSNode Stack ;

// 生成
Stack InitStack(){
    Stack S ;
    S = (Stack)malloc(sizeof(struct SNode)) ;
    S -> Next = NULL ;  // 头结点指向空代表链表此时为空

    return S ;
}

// 判断是否为空（链式栈没有满的情况
bool isEmpty(Stack S){
    return S->Next == NULL ;
}

// Push 默认第一个结点是栈顶,也就是头结点的Next的元素的顶部的元素
bool Push(Stack S , ElementType x){
    PtrToSNode tmp = (PtrToSNode)malloc(sizeof(struct SNode)) ;
    tmp->Data = x ;
    tmp->Next = S->Next ;
    S->Next = tmp ;

    return TRUE ;
}

// Pop
ElementType Pop(Stack S){
    PtrToSNode FirstCell ;
    ElementType TopEle ;

    if(isEmpty(S)){
        printf("栈为空,POP失败\n");
        return ERROR ;
    }else{
        // 得到数值
        FirstCell = S->Next ;
        TopEle = FirstCell->Data ;

        // 处理栈
        S->Next = FirstCell->Next ; //将S的Next指向原本First的下一个元素即可
        free(FirstCell );//释放空间

        return TopEle ;
    }
}

// 测试函数
int main(){
    Stack S = InitStack() ;
    printf("进行01234插入操作\n");
    int k = 0 ;
    for(k = 0 ; k < 5 ; k++){
        Push(S,k) ;
    }

    printf("进行Push六次\n");
    for(k = 0 ; k < 6 ; k++){
        int tmp = Pop(S) ;
        if(tmp == -1){
            printf("取出失败");
        }else{
            printf("此次取出： %d \n" , tmp);
        }
    }

    return 0 ;
}
```


# 队列  
队列是具有一定操作约束的线性表  
具体一点，就是遵循FIFO，只能在一端插入，而在另外一端删除    

队列也有两种存储方式，分别是顺序存储和链式存储  

## 顺序存储 
由一维数组负责元素记录，配合一个记录队列头元素位置的front和一个记录尾元素位置的rear组成     

同时，如果我们采用普通的顺序存储，会浪费很多空间，这是我们不希望看到的，所以可以采用一个**循环队列存储**，到头后折返到首位  
但是，如果不做处理的话，front和rear下标关系如下：   
1.front = rear 为空，比如初始化的时候二战都为0  
2.其他情况，正常运行    
3.队列满时，这时候rear从front"后面的位置"到达了front所在的位置。也就是说队列满时仍然是front = rear ; 
所以无法正常表示所有情况。本质是因为只有n个插值情况，但是有n+1个情况    

因此有两种解决方案：    
1.使用一个额外参数。比如使用size实时记录大小，或者使用flag标记上一个操作是入队还是出队以判断情况    
2.只使用n-1个空间，即在```(rear+1)%Maxsize == front```的时候就判断队列满    

根据第二种方案，实现如下：  
```c
# include <stdio.h>
# include <stdlib.h>

#define FALSE 0;
#define TRUE 1   ;
#define ERROR -1 ;

typedef int ElementType ;
typedef int bool ;

typedef int Position ;
typedef struct QNode * PtrToQNode ;
struct QNode
{
    ElementType * Data ; //存储元素的数组
    Position Front , Rear ; //头尾指针
    int MaxSize ; //队列最大容量
};
typedef PtrToQNode Queue ;

// 创建队列与基本操作
Queue CreateQueue(int MaxSize){
    Queue Q = (Queue)malloc(sizeof(struct QNode)) ;
    Q->Data = (ElementType*)malloc(MaxSize * sizeof(ElementType)) ;
    Q->Front = Q->Rear = 0 ; // 两个位置初始化都为0
    Q->MaxSize = MaxSize ;
}

bool IsFull(Queue Q){
    return ((Q->Rear + 1) % (Q->MaxSize) == Q->Front) ;
    // 核心是尾指针+1后会不会和头指针重叠，利用MaxSize计算余数情况
}

bool isEmpty(Queue Q){
    return (Q->Front == Q->Rear) ;
}

// 操作和删除
bool AddQ(Queue Q , ElementType X){
    printf("尝试加入 %d \n" , X);
    if(IsFull(Q)){
        printf("队伍满, %d 加入失败 \n " ,X ) ;
        return FALSE ;
    }else{
        Q->Rear = (Q->Rear + 1) % Q->MaxSize ; // 移动尾部
        Q->Data[Q->Rear] = X ; //增加元素
    }
}

ElementType DeleteQ(Queue Q){
    if(isEmpty(Q)){
        printf("队列空\n") ;
        return ERROR ;
    }else{
        Q->Front = (Q->Front + 1) % Q->MaxSize ; //移动头
        return Q->Data[Q->Front] ; //得到元素
    }
}

// 测试函数
int main(){
    printf("\n生成Size为5的表格（在这个实现中实际只可以存4个）\n");
    Queue Q = CreateQueue(5) ; //最大为5
    printf("\n加入五个元素\n");
    int k = 0 ;
    for(k = 1 ; k <= 5 ;k++){
        AddQ(Q,k) ;
    }
    printf("POP两个元素\n");
    int tmp =0 ;
    tmp = DeleteQ(Q) ;
    printf("弹出： %d \n" , tmp) ;
    tmp = DeleteQ(Q) ;
    printf("弹出： %d \n" , tmp) ;
    printf("\n加入两个元素\n");
    AddQ(Q,77) ;AddQ(Q,88) ;
    printf("\n尝试再加入一个元素\n");
    AddQ(Q,99);



    return 0 ;
}

```

## 链式存储 
队列的链式结构同样可以用一个单链表来实现    
插入和删除操作分别在链表的两天进行  
**将链表头做Front,尾做rear**,因为在单向链表中，只有头的部分知道“删除之后的下一个元素是什么”，因此只能按这个模式分析 

### 不带头结点的一个实例
下面是不带头结点的链式结构的一个示例：  
```c
# include <stdio.h>
# include <stdlib.h>

#define FALSE 0;
#define TRUE 1   ;
#define ERROR -1 ;

typedef int ElementType ;
typedef int bool ;

typedef struct Node * PtrToNode ;
struct Node
{
    ElementType Data ;
    PtrToNode Next ;
};

typedef PtrToNode Position ;

typedef struct QNode * PtrToQNode ;

struct QNode
{
    Position Front , Rear ; //分别指向头和尾的指针
    int Size ; //维护一个容量
};

typedef PtrToQNode Queue;

// 创建队列与基本操作
Queue CreateQueue(){
    Queue Q ;
    Q = (PtrToQNode)malloc(sizeof(struct QNode));
    Q->Front = NULL ;
    Q->Rear = NULL;
    Q->Size = 0 ;

    return Q ;
}

bool isEmpty(Queue Q){
    return (Q->Front == NULL) ; // 头结点的next是空
}

int getSize(Queue Q){
    return Q->Size ;
}

// 操作和删除
bool AddQ(Queue Q , ElementType X){
    Position tmp ;
    tmp = (PtrToNode)malloc(sizeof(struct Node)) ;
    tmp->Data = X ;
    tmp->Next = NULL ;

    if(Q->Front == NULL){
        // 插入的是第一个结点
        // ! 注意，这一步无论"带不带头结点"都需要判断是不是第一个插入进去的指针，否则会造成结点直接连接失败（Front会一直指向NULL）
        Q->Front = tmp ;
        Q->Rear = tmp ;
    }else{
        // 非第一个结点
        Q->Rear->Next = tmp ; //更新tmp的插入位置
        Q->Rear = tmp ; // 尾指针指向tmp
    }

    Q->Size++ ;
    printf("成功加入 %d , 当前size为%d \n" , Q->Rear->Data , Q->Size);

}

ElementType DeleteQ(Queue Q){
    Position FrontCell ;//一个存储当前头结点的指针
    ElementType FrontEle ; // 头部数据

    if(isEmpty(Q)){
        printf("队列空，删除失败 \n") ;
        return ERROR ;
    }else{
        // 获取所要的元素
        FrontCell = Q->Front ;
        FrontEle = FrontCell->Data ;
        // 处理队列
        if(Q->Front == Q->Rear){
            //如果队列只有一个元素
            Q->Front = Q->Rear = NULL; // 直接置空队列就是删除
        }else{
            Q->Front = FrontCell->Next ; // Front直接指向下一位就完成了操作
        }

        // 释放空间
        free(FrontCell) ;
        Q->Size--;
        printf("完成出队，当前size为 %d \n" , Q->Size) ;

        return FrontEle ;
    }
}

// 测试函数
int main(){
    printf("\n生成表格\n");
    Queue Q = CreateQueue() ; //最大为5
    printf("\n加入五个元素\n");
    int k = 0 ;
    for(k = 1 ; k <= 5 ;k++){
        AddQ(Q,k) ;
    }
    printf("POP两个元素\n");
    int tmp =0 ;
    tmp = DeleteQ(Q) ;
    printf("出队： %d \n" , tmp) ;
    tmp = DeleteQ(Q) ;
    printf("出队： %d \n" , tmp) ;
    printf("\n加入两个元素\n");
    AddQ(Q,77) ;AddQ(Q,88) ;
    printf("\n尝试再加入一个元素\n");
    AddQ(Q,99);

    printf("按顺序进行出队直到队列空\n");
    while(Q->Size > 0){
    tmp = DeleteQ(Q) ;
        printf("出队： %d \n" , tmp) ;
    }
    return 0 ;
}

```

### 带头结点的一个实例  
个人认为本质上并没有区别，只是无论如何都不会造成最初的链表头指针改变    

```c
# include <stdio.h>
# include <stdlib.h>

#define FALSE 0;
#define TRUE 1   ;
#define ERROR -1 ;

typedef int ElementType ;
typedef int bool ;

typedef struct Node * PtrToNode ;
struct Node
{
    ElementType Data ;
    PtrToNode Next ;
};

typedef PtrToNode Position ;

typedef struct QNode * PtrToQNode ;

struct QNode
{
    Position Front , Rear ; //分别指向头和尾的指针
    int Size ; //维护一个最大值
};

typedef PtrToQNode Queue;

// 创建队列与基本操作
Queue CreateQueue(){
    Queue Q ;
    Q = (PtrToQNode)malloc(sizeof(PtrToQNode));

    // 创建头结点
    Position _head ;
    _head = (Position)malloc(sizeof(struct Node));
    _head->Data = 0 ;
    _head->Next = NULL ;

    // 将头尾的指针都指向头结点
    Q->Front = Q->Rear = _head ; //先把头尾都定义为空的头结点

    Q->Size = 0 ;

    return Q ;
}

bool isEmpty(Queue Q){
    return (Q->Front == Q->Rear) ;
    // 若头尾指向了同一处，则是空
}

// 操作和删除
bool AddQ(Queue Q , ElementType X){
    Position tmp ;
    tmp = (PtrToNode)malloc(sizeof(struct Node)) ;
    tmp->Data = X ;
    tmp->Next = NULL ;

    if(Q->Front == NULL){
        // 插入的是第一个结点
        // ! 注意，这一步无论"带不带头结点"都需要判断是不是第一个插入进去的指针，否则会造成结点直接连接失败（Front会一直指向NULL）
        Q->Front = tmp ;
        Q->Rear = tmp ;
    }else{
        // 非第一个结点
        Q->Rear->Next = tmp ; //更新tmp的插入位置
        Q->Rear = tmp ; // 尾指针指向tmp
    }
    Q->Size++;

    printf("成功加入 %d , 当前size为%d \n" , Q->Rear->Data , Q->Size);


    return TRUE ;
}

ElementType DeleteQ(Queue Q){
    // 首先判断空
    if(isEmpty(Q)) {
        printf("空队列，出队失败 \n") ;
        return ERROR ;
    }else{

        // 先获取对应元素

        Position frontP = Q->Front->Next ; //要得到Front的Next结点才对，相当于顺序表里面先进行++
        ElementType ElementP = frontP ->Data ;

        if( frontP == Q->Rear){
            // 最后一个元素出队，直接将队列归0
            Q->Rear = Q->Front ;
        }else{
            Q->Front->Next = frontP->Next ; //头指针指向的Next重定义为原本P的下一个元素，达到删除P的目的
        }

        // 执行操作
        // 进行释放操作与size修改
        Q->Size-- ;

        free(frontP) ;

        printf("完成出队 %d，当前size为 %d \n" ,ElementP, Q->Size) ;
        return ElementP ;
    }
}

// 测试函数
int main(){
    printf("\n生成表格\n");
    Queue Q = CreateQueue() ; //最大为5
    printf("\n加入五个元素\n");
    int k = 0 ;
    for(k = 1 ; k <= 5 ;k++){
        AddQ(Q,k) ;
    }
    printf("出队两个元素\n");
    int tmp =0 ;
    tmp = DeleteQ(Q) ;
    printf("出队： %d \n" , tmp) ;
    tmp = DeleteQ(Q) ;
    printf("出队： %d \n" , tmp) ;
    printf("\n加入两个元素\n");
    AddQ(Q,77) ;AddQ(Q,88) ;
    printf("\n尝试再加入一个元素\n");
    AddQ(Q,99);

    printf("按顺序进行出队直到队列空\n");
    while(Q->Size > 0){
        tmp = DeleteQ(Q) ;
        printf("出队： %d \n" , tmp) ;
    }
    return 0 ;
}

```


# 堆    
结构性：用数组表示的完全二叉树  
有序性：任一结点的关键字是其子树所有结点的最大值(或最小值)  
> 从根结点到任意结点路径上结点序列都存在有序性  


## 最大堆的建立 
实际上就是一个二叉树结构的变体  
这里利用数组来实现树    
```c
# include <stdio.h>
# include <stdlib.h>

#define FALSE 0;
#define TRUE 1   ;
#define ERROR -1 ;

typedef int ElementType ;
typedef int bool ;


#define MAXDATA 9999 ; //设定一个哨兵作为最大堆的顶点   
#define MINDATA -9999 ; //设定一个哨兵作为最大堆的顶点   

// 建立堆   
typedef struct HNode* Heap ; 
struct HNode{
    ElementType *Data ;  // 数组
    int Size ;  // 当前元素个数
    int Capacity ;  // 最大容量    
};


typedef Heap MaxHeap ; 
typedef Heap MinHeap ; 

// 最大堆的建立 
MaxHeap CreateHeap(int MaxSize)
{
    // 申请空间
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode)) ; 
    H->Data = (ElementType*)malloc((MaxSize+1) * sizeof(ElementType)) ; 
    // 这里使用MaxSize+1是因为下标为0的区域要存放哨兵   
    H->Size = 0 ; 
    H->Capacity = MaxSize ; 
    H->Data[0] = MAXDATA ; //设置哨兵，这里是最大堆的哨兵
    // H->Data[0] = MINDATA

    return H ; 
}
``` 

## 最大堆的插入 
插入和删除的核心就是**保证完成插入之后还是堆**  
一般而言，插入的步骤就是直接插在树的尾部（即目前size+1的地方）  
然后再通过循环操作，不断置换位置到达合适的位置  
（最大堆里，父要比子大，则一直/2(因为是数组存的树)，直到位置合适）  
```c
// 最大堆的插入 
bool IsFull(MaxHeap H){
    return (H->Size == H->Capacity) ; 
}

// 插入操作 
bool Insert(MaxHeap H , ElementType X){
    int i ; 

    if(IsFull(H)){
        // 如果最大堆已满，插入失败
        printf("堆满 \n") ; 
        return FALSE ; 
    }

    i = ++H->Size ; 
    /*
    H->Size++;
    i = H->Size ; 
    */
    // i指向下一位位置

    // 进行调整
    for(   ; H->Data[i/2] < X ; i/=2)
        H->Data[i] = H->Data[i/2] ; // 将父节点的位置赋给当前位置，实质上就是在不断上移
        // H->Data[i/2] < X 根节点小于插入元素时，一直向上寻找（即i/2）
        // 直到找到“根节点大于插入点”，此时跳出
    
    // 跳出后进行X的重赋值操作  
    H->Data[i] = X ; //此时找到了合适的位置插入


    return TRUE ;
}
```

## 最大堆的删除 
删除操作和插入类似但相反    
1.取出最大元素，就是下标为1的元素   
2.把末端元素拷贝到下标为1的位置，然后删除末端   
3.进行调整，不断过滤下层结点    

```c
// 删除 
#define ERROR -1 ; 
bool IsEmpty(MaxHeap H){
    return (H->Size == 0) ; 
}

ElementType DeleteMax(MaxHeap H){
    // 基础定义 
    int Parent , Child ; 
    ElementType  MaxItem , X ; 

    if(IsEmpty(H)){
        printf("空堆\n") ; 
        return ERROR ; 
    }

    // 主要算法 
    MaxItem = H->Data[1] ; //取出最大值，这个是我们要返回的东西 

    // 用最大堆的最后一个元素从根结点开始向上过滤下层结点   
    X = H->Data[H->Size--] ;  // X是最后一个元素的大小
    // 先到达H->Size , 然后Size--来更新规模 

    // 进行过滤 
    for(Parent = 1 ; Parent*2 <= H->Size ; Parent = Child){
        //从1开始，对每一个父结点（都是2的倍数）进行遍历
        // Parent 指示了将来要换的位置
        // 关于 Parent = Child的操作见跳出循环时

        Child = Parent * 2 ;// 得到Child 
        // 进行判断 ，要从Child里面选出一个较大的
        if((Child != H->Size) && (H->Data[Child] < H->Data[Child+1])){
            Child++ ;//右结点
            // 这里的判断基于两个部分 1.不断超过大小（Szie) 2.不符合要求，即它是比较小的点
        }

        // 找到合适位置时   
        if(X>=H->Data[Child]) break;  // 位置合适。X比左右儿子都大，break
        else {
            H->Data[Parent] = H->Data[Child] ; //向下过滤。即把左右儿子中大这设置为Parent，然后继续执行
        }
    }

    // 跳出循环时，会执行Parent = Child
    H->Data[Parent] = X ; 
    // 配合Parent = Child相当于执行了正确的位置替换 

    return MaxItem ; 
}
``` 

## 堆的建立 
堆的建立有两种方式：    
1.N次插入操作，这样耗时会比较多 
2.先满足完全二叉树的要求，然后再调整结点位置    

这里提供第二种方式的实现：  
```c
// 建立最大堆
void PercDown(MaxHeap H , int p){
    // 下滤：将H中以H->DATA[p] 为根的子堆调整为最大堆   
    int Parent , Child ; 
    ElementType X ; 

    X=H->Data[p] ; //取出根结点存放的值 
    // 下面操作和删除的下滤类似 

    for(Parent = p ; Parent *2 <= H->Size ; Parent = Child){
        Child = Parent*2 ; 
        if((Child!=H->Size) && (H->Data[Child] < H->Data[Child+1])){
            Child++ ; 
        }

        if(X >= H->Data[Child]) break; 
        else H->Data[Parent] = H->Data[Child] ; 
    }

    H->Data[Parent] = X ; 
}

void BuildHeap(MaxHeap H){
    // 调整在 H->Data[] 中的元素，使其满足最大堆的有序性    

    int i ; 
    for(i = H->Size/2 ; i>0;i--){
        // 从下往上进行调整
        PercDown(H , i)  ;
    }
}
```

## 堆：实现合集 
```c
# include <stdio.h>
# include <stdlib.h>

#define FALSE 0;
#define TRUE 1   ;
#define ERROR -1 ;

typedef int ElementType ;
typedef int bool ;


#define MAXDATA 9999 ; //设定一个哨兵作为最大堆的顶点   
#define MINDATA -9999 ; //设定一个哨兵作为最大堆的顶点   

// 建立堆   
typedef struct HNode* Heap ; 
struct HNode{
    ElementType *Data ;  // 数组
    int Size ;  // 当前元素个数
    int Capacity ;  // 最大容量    
};


typedef Heap MaxHeap ; 
typedef Heap MinHeap ; 

// 最大堆的建立 
MaxHeap CreateHeap(int MaxSize)
{
    // 申请空间
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode)) ; 
    H->Data = (ElementType*)malloc((MaxSize+1) * sizeof(ElementType)) ; 
    // 这里使用MaxSize+1是因为下标为0的区域要存放哨兵   
    H->Size = 0 ; 
    H->Capacity = MaxSize ; 
    H->Data[0] = MAXDATA ; //设置哨兵，这里是最大堆的哨兵
    // H->Data[0] = MINDATA

    return H ; 
}

// 最大堆的插入 
bool IsFull(MaxHeap H){
    return (H->Size == H->Capacity) ; 
}

// 插入操作 
bool Insert(MaxHeap H , ElementType X){
    int i ; 

    if(IsFull(H)){
        // 如果最大堆已满，插入失败
        printf("堆满 \n") ; 
        return FALSE ; 
    }

    i = ++H->Size ; 
    /*
    H->Size++;
    i = H->Size ; 
    */
    // i指向下一位位置

    // 进行调整
    for(   ; H->Data[i/2] < X ; i/=2)
        H->Data[i] = H->Data[i/2] ; // 将父节点的位置赋给当前位置，实质上就是在不断上移
        // H->Data[i/2] < X 根节点小于插入元素时，一直向上寻找（即i/2）
        // 直到找到“根节点大于插入点”，此时跳出
    
    // 跳出后进行X的重赋值操作  
    H->Data[i] = X ; //此时找到了合适的位置插入


    return TRUE ;
}


// 删除 
#define ERROR -1 ; 
bool IsEmpty(MaxHeap H){
    return (H->Size == 0) ; 
}

ElementType DeleteMax(MaxHeap H){
    // 基础定义 
    int Parent , Child ; 
    ElementType  MaxItem , X ; 

    if(IsEmpty(H)){
        printf("空堆\n") ; 
        return ERROR ; 
    }

    // 主要算法 
    MaxItem = H->Data[1] ; //取出最大值，这个是我们要返回的东西 

    // 用最大堆的最后一个元素从根结点开始向上过滤下层结点   
    X = H->Data[H->Size--] ;  // X是最后一个元素的大小
    // 先到达H->Size , 然后Size--来更新规模 

    // 进行过滤 
    for(Parent = 1 ; Parent*2 <= H->Size ; Parent = Child){
        //从1开始，对每一个父结点（都是2的倍数）进行遍历
        // Parent 指示了将来要换的位置
        // 关于 Parent = Child的操作见跳出循环时

        Child = Parent * 2 ;// 得到Child 
        // 进行判断 ，要从Child里面选出一个较大的
        if((Child != H->Size) && (H->Data[Child] < H->Data[Child+1])){
            Child++ ;//右结点
            // 这里的判断基于两个部分 1.不断超过大小（Szie) 2.不符合要求，即它是比较小的点
        }

        // 找到合适位置时   
        if(X>=H->Data[Child]) break;  // 位置合适。X比左右儿子都大，break
        else {
            H->Data[Parent] = H->Data[Child] ; //向下过滤。即把左右儿子中大这设置为Parent，然后继续执行
        }
    }

    // 跳出循环时，会执行Parent = Child
    H->Data[Parent] = X ; 
    // 配合Parent = Child相当于执行了正确的位置替换 

    return MaxItem ; 
}


// 建立最大堆
void PercDown(MaxHeap H , int p){
    // 下滤：将H中以H->DATA[p] 为根的子堆调整为最大堆   
    int Parent , Child ; 
    ElementType X ; 

    X=H->Data[p] ; //取出根结点存放的值 
    // 下面操作和删除的下滤类似 

    for(Parent = p ; Parent *2 <= H->Size ; Parent = Child){
        Child = Parent*2 ; 
        if((Child!=H->Size) && (H->Data[Child] < H->Data[Child+1])){
            Child++ ; 
        }

        if(X >= H->Data[Child]) break; 
        else H->Data[Parent] = H->Data[Child] ; 
    }

    H->Data[Parent] = X ; 
}

void BuildHeap(MaxHeap H){
    // 调整在 H->Data[] 中的元素，使其满足最大堆的有序性    

    int i ; 
    for(i = H->Size/2 ; i>0;i--){
        // 从下往上进行调整
        PercDown(H , i)  ;
    }
}
```


# 哈希表    
散列查找的核心就在于**计算元素的位置**，然后直接在查找和插入的时候去对应的位置上寻找即可    
其有两项基本工作为：1.计算位置  2.解决冲突    
哈希表/散列查找的优势在于，查找时间和问题规模无关   

> 以关键字key为自变量，通过一个确定的函数h(即散列函数)，计算出对应的函数值h(key)，作为数据对象的存储地址；同时还需要想办法解决冲突问题      

装填因子 Loading Factor: 设散列表的空间大小为m，填入表中的数据个数是n，则称a = n/m 就是散列表的装填因子 

散列查找以较小的a为前提，实际上是一个以空间换时间的查找方式 
散列查找不适用顺序查找、范围查找、最大最小值查找    

## 构造方式 
**数字常见构造法：**    
1.直接定值法 ： h(key) = a * key + b 

2.除留余数法 ： h(key) = key % p ,一般把p取为素数   

3.数值分析法 : 分析数字关键字在各位上的变化情况，取比较随机的位作为散列地址 
> 比如11位的手机号码key就取后4位作为地址    

4.折叠法：把关键词分割为位数相同的几个部分，然后叠加    

5.平方取中法 ： 把数据作平方运算，然后取中间的数字作为key   

**字符关键词常见构造法：**    
1.ASCII码加和法 ： 相加各字符的ASCII码，然后和表大小取余    
一种简单的改进法，是把前三个字符进行一个移位，一般使用27    

2.移位法 ： 同ASCII码加和的优化方案，但这次将所有涉及的n个字符都进行移位    
```c
Index Hash(const char *Key , int TableSize){
    unsigned int h = 0 ; 
    while(*Key != '\0') {
        h = (h << 5) + *Key++ ; 
    }

    return h % TableSize ; 
}
```

## 冲突解决 
有两种常见的思路解决冲突    
1.开放地址法：换个位置重新插入(包括线性探测，平方探测，双散列)    
> 有定理显示，当表长size是某个4k+3形式的素数的时候，平方探测法就可以探查到整个散列表的空间

> 经验证明，被设计为 h2(key) = p -(key mod p) 的二次散列的效果是比较好的    

> 再散列：当散列表元素太多时，查找效率会下降。一般而言，实用最大装填因子一般取0.5~0.85。当装填因子过大时，解决的办法是加倍扩大散列表，这个过程叫再散列,(Rehashing)，此时也要重新计算各元素的新位置        

2.链地址法 ： 把同一位置的冲突对象组织在一起（存储在同一个index）   
也叫分离链接法 Separate Chaining    
将相应位置上冲突的所有key存储在一个单链表中 

## 实现示例 
### 平方探测的Hash  
```C
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

#define FALSE 0
#define TRUE 1   
#define ERROR -1 

typedef int ElementType ;
typedef int bool ;


#define MAXDATA 9999  //设定一个哨兵作为最大堆的顶点   
#define MINDATA -9999  //设定一个哨兵作为最大堆的顶点   

void Swap(ElementType *a , ElementType *b){
    ElementType t = *a ; 
    *a = *b ; 
    *b = t ; 
}

// 开放地址法   

#define MAXTABLESIZE 100000 
typedef int Index ; //存储下标  
typedef Index Postion ; 

typedef enum {Legitimate , Empty , Deleted} EntryType ; 
// 合法元素，空单元，已删除 

typedef struct HashEntry Cell ;  // 散列表单元类型  
struct HashEntry
{
    ElementType Data ;  // 存储内容 
    EntryType Info ; //单元状态
};

typedef struct TBLNode * HashTable ; // 散列表类型  
struct TBLNode
{
    int TableSize ; // 最大长度 
    Cell *Cells ; //存放数组    
};

// 辅助函数，用于得到一个可用的素数 
int NextPrime(int N){
    // 返回大于N且不超过MAXTABLESIZE的最小素数  
    int i , p = (N%2) ? N+2 : N+1 ; //从奇数开始    

    while (p <= MAXTABLESIZE)
    {
        for(i = (int)sqrt(p) ;  i > 2 ; i--){
            if(!(p%i))  break;  // p不是素数    
        }
        if(i==2) break; // for正常结束，说明p是素数 
        else p+=2 ; 
    }
    return p ; 
}

// 位移映射函数Hash
int Hash(const char *Key , int TableSize){
    unsigned int H = 0 ; 
    while(*Key != '\0') {
        H = (H<<5) + *Key++ ; 
    }

    return H%TableSize ; 
}

int IntHash(int Key , int TableSize){

    return Key%TableSize ; 
}

// 正式的创建表 
HashTable CreateTable(int TableSize)
{
    HashTable H ; 
    int i ; 
    // 初始化与申请空间 
    // 初始化表 
    H = (HashTable)malloc(sizeof(struct TBLNode)) ;
    H->TableSize = NextPrime(TableSize) ; 

    // 初始化单元数组
    H->Cells = (Cell*)malloc(H->TableSize * sizeof(Cell)) ; 

    // 初始化各个单元为空单元,即标记其Info为Empty      
    for(i=0 ; i <H->TableSize ; i++){
        H->Cells[i].Info = Empty ; 
    }

    return H ; 
}

// 平方探测法的查找与插入
// 查找
Postion Find (HashTable H ,ElementType Key){
    Postion CurrentPos , NewPos ; 
    int CNum = 0 ; // 冲突次数记录  

    NewPos = CurrentPos = IntHash(Key , H->TableSize) ; 

    // 如果该位置的单元非空，而且不是要找的元素时，认为发生冲突 
    while(H->Cells[NewPos].Info != Empty
        && H->Cells[NewPos].Data != Key){

        //统计冲突并判断奇偶
        if(++CNum % 2){
            // 奇数
            NewPos = CurrentPos + (CNum+1)*(CNum+1) / 4 ;
            //因为增量为((CNum+1)/2)^2

            //调整为合法位置
            if(NewPos >= H->TableSize)  NewPos = NewPos % H->TableSize ; 
        }else{
            // CNum为偶数
            // 此时增量为-((CNum/2)^2)  
            NewPos = CurrentPos - CNum*CNum/4 ; 
            while(NewPos < 0)   NewPos+= H->TableSize ;//位置调整   
        }
    }

    return NewPos ; //
    // 如果return是正常位置，则成功。否则会return一个空单元的位置，那么就是找不到对应key
}


// 插入 
bool Insert(HashTable H , ElementType Key){
    Postion Pos = Find(H,Key);

    if(H->Cells[Pos].Info != Legitimate){
        //如果没有被占则可以使用
        H->Cells[Pos].Info = Legitimate ; 
        H->Cells[Pos].Data = Key ; 

        //
        return TRUE ;
    }else{
        printf("键值存在\n") ; 
        return FALSE ; 
    }
}


int main(){

    return 0  ;
}

```

### 分离链接的Hash  
```c
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

#define FALSE 0
#define TRUE 1   
#define ERROR -1 

// typedef int ElementType ;
typedef int bool ;


#define MAXDATA 9999  //设定一个哨兵作为最大堆的顶点   
#define MINDATA -9999  //设定一个哨兵作为最大堆的顶点   

// 开放地址法   

// 分离链接 
#define MAXTABLESIZE 100000 

// 辅助函数，用于得到一个可用的素数 
int NextPrime(int N){
    // 返回大于N且不超过MAXTABLESIZE的最小素数  
    int i , p = (N%2) ? N+2 : N+1 ; //从奇数开始    

    while (p <= MAXTABLESIZE)
    {
        for(i = (int)sqrt(p) ;  i > 2 ; i--){
            if(!(p%i))  break;  // p不是素数    
        }
        if(i==2) break; // for正常结束，说明p是素数 
        else p+=2 ; 
    }
    return p ; 
}

// 位移映射函数 
int Hash(const char *Key , int TableSize){
    unsigned int H = 0 ; 
    while(*Key != '\0') {
        H = (H<<5) + *Key++ ; 
    }

    return H%TableSize ; 
}

// 结构声明 
#define KEYLENGTH 15 
typedef char ElementType[KEYLENGTH+1] ;  // 使用字符串当关键字  
typedef int Index ;

typedef struct LNode * PtrToLNode ; 
struct LNode
{
    ElementType Data ; 
    PtrToLNode Next ; 
};

typedef PtrToLNode Position ; 
typedef PtrToLNode List ; 

typedef struct TBLNode * HashTable ; 
struct TBLNode{
    int TableSize ; 
    List Heads ; 
};

HashTable CreateTable(int TabelSize){
    HashTable H ; 
    int i ;

    // 初始化表
    H = (HashTable)malloc(sizeof(struct TBLNode)) ; 
    H->TableSize = NextPrime(TabelSize) ; 

    // 分配表头
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode)) ; 

    for(i = 0 ; i < H->TableSize ; i++){
        H->Heads[i].Data[0] = '\0' ; 
        H->Heads[i].Next = NULL ; 
    }

    return H ;
}

// 查找 
Position Find(HashTable H , ElementType Key){
    Position P ;
    Index Pos ; 

    Pos = Hash(Key , H->TableSize) ; 
    P = H->Heads[Pos].Next ; 

    // 开始逐个寻找 
    while (P && strcmp(P->Data , Key))
    {
        P = P->Next ; // 不断前移 
    }

    // 找到之后跳出，或者没找到跳出（没找到时返回NULL）
    return P ;
}

// 插入 
bool Insert(HashTable H , ElementType Key){
    Position P , NewCell ; 
    Index Pos ;

    P = Find(H,Key) ; 
    if(!P){
        // 关键词未找到,则可以插入 
        NewCell = (Position)malloc(sizeof(struct LNode)); 
        strcpy(NewCell->Data , Key) ; // 将关键词写入   

        Pos = Hash(Key,H->TableSize); // 初始散列位置   

        // 将NewCell插入为H->Heads[Pos]链表的第一个结点 
        NewCell ->Next = H->Heads[Pos].Next ; 
        H ->Heads[Pos].Next = NewCell ; 
        return TRUE ;
    }else{
        // 关键词存在
        printf("关键词已存在 \n") ;
        return FALSE ; 
    }
}

// 释放散列表   
void DestoryTable(HashTable H){
    int i ;
    Position P,Tmp ; 

    // 释放每一个结点   
    for(i=0 ; i <H ->TableSize ;i++){
        P= H->Heads[i].Next ; 
        while(P){
            Tmp = P->Next ; 
            free(P) ;
            P = Tmp ; 
        }
    }

    free(H->Heads);
    free(H);
}

int main(){

    return 0  ;
}

```


# 插入排序  
最好情况 ： O(N)  , 均是顺位    
最好情况 ： O(N^2)  , 均是逆序  

插入排序是比较稳定的一种排序方式    

## 简单插入排序
简单插入排序的核心思想是：将待排序的一组序列分为已排好序的和未排好序的两部分    


```c
# include <stdio.h>
# include <stdlib.h>

#define FALSE 0;
#define TRUE 1   ;
#define ERROR -1 ;

typedef int ElementType ;
typedef int bool ;

// 插入排序 
void InserionSort(ElementType A[] , int N){
    // 认为结果数组是从小到大排序的

    int P , i ;
    ElementType tmp ; 

    // 逐步遍历未排序序列的元素
    for(P=1;P<N;P++){
        tmp = A[P] ; // 取出未排序数组的第一个元素  

        for(i=P ; i>0 && A[i-1]>tmp ; i--)
        {
            // 从尾部开始，直到找到一个"tmp比它大"的位置插入
            // 因此比tmp大的部分都需要后移
            A[i] = A[i-1] ; 
        }

        A[i] = tmp ; // 放入合适位置    
    }
}
```

## 希尔排序
希尔排序的核心则在于加入了**间隔**，即改成对每D个元素进行排序，然后递减D    
简易的希尔排序D_k = (D_k+1) / 2 。有的时候它并不理想    

这里的代码实现使用了SedgeWick增量序列来进行希尔排序 

```c
void ShellSort(ElementType A[] , int N){
    int Si , D, P , i ; 

    ElementType Tmp ; 

    // 定义SedgeWick增量序列（这里只使用一部分）    
    int SedgeWick[]={929,505,209,109,41,19,5,1,0};
    for(Si = 0 ; SedgeWick[Si] >= N ; Si++); //设定初始增量的长度   

    for(D=SedgeWick[Si] ; D>0 ; D= SedgeWick[++Si])
        for(P = D ; P< N ;P++){
            Tmp = A[P] ; 
            for(i = P ; i>=D && A[i-D] > Tmp ; i-=D)
                A[i] = A[i-D] ; 

            A[i] = Tmp ; 
        }
}
```

# 选择排序  
## 简单选择排序 
简单选择排序就是最基本的做法，找到最小值，然后交换，一直持续下去    
**找到最小值**的部分直接使用遍历查找    
其实现如下: 
```C
void Swap(ElementType *a , ElementType *b){
    ElementType t = *a ; 
    *a = *b ; 
    *b = t ; 
}

// 简单选择排序 
void SimpleSelectionSort(ElementType A[] , int N){
    int i ,j ,min ; 

    for(i = 0 ; i <N-1 ; i++){
        min = i ; 
        for(j = i+1 ; j <N;j++)
            if(A[j] < A[min])   min = j ; // 不断记录最小元素的位置

        
        Swap(&A[i] , &A[min]) ; 
    }
}
``` 

## 堆排序   
! 注意之前生成最大堆的代码不能直接调用，但是核心思路是一样的    
因为这里的数据在第0个单元开始存放   

```c
void Swap(ElementType *a , ElementType *b){
    ElementType t = *a ; 
    *a = *b ; 
    *b = t ; 
}

void PercDown(ElementType A [] , int p , int N){
    // 将N个元素的数组中，以A[p]为根的子堆调整为最大堆
    int Parent , Child ; 
    ElementType X  ;

    X = A[p] ; //取出根结点存放的数值   

    for(Parent = p ; (Parent*2 + 1) < N ; Parent  =Child) {
        // 因为初始下标为0，所以更新的Parent都是2t+1了
        Child = Parent *2 + 1 ;
        if((Child != N-1) && (A[Child] < A[Child+1]))
            Child++ ; 
        
        if(X >= A[Child])   break; 
        else A[Parent] = A[Child] ; 
    }

    A[Parent] = X ; 
}


void HeapSort(ElementType A[] , int N){
    int i ;

    for(i = N-1 ; i>0;i--){
        Swap(&A[0] , &A[i]) ; 
        PercDown(A,0,i) ; 
    }
}
``` 
# 冒泡排序  
经典排序方法，不赘述 
```C
void Swap(ElementType *a , ElementType *b){
    ElementType t = *a ; 
    *a = *b ; 
    *b = t ; 
}

// 冒泡排序 
void BubbleSort(ElementType A[] , int N){
    int P , i ; 
    bool flag ; 

    for(P = N-1 ; P >= 0 ; P--){
        flag = FALSE ;  // 每次开始都置为FALSE 

        for(i = 0 ; i < P ; i++){
            // 一趟趟进行，每次找出一个最大元素就交换到最右端   
            if(A[i] > A[i+1]){
                Swap(&A[i] , &A[i+1]) ; 
                flag = TRUE ;  // 标记发生了交换
            }
        }

        // 全程无交换就代表完成，跳出
        if(flag == TRUE ) break; 
    }
}
```

# 快速排序  
快速排序也是交换排序的一种  
它的核心在于选择一个pivot(主元)，根据主元将数组划分为两个子序列，一个大，一个小 
在不断的分治中，问题的规模变小，最终得到处理    
> pivot的选取有很多种方式，甚至有专门的算法。这里就先默认第一个下标的值是pivot了

```c

void Swap(ElementType *a , ElementType *b){
    ElementType t = *a ;
    *a = *b ;
    *b = t ;
}

// 快速排序

// 核心排序函数，用于递归
void Qsort(ElementType A[] , int Left , int Right){
    int Pivot  , Low , High ;
    // int Cutoff ; //可以设置Cutoff来决定是否快排，这里不设置了
    // Low从最小的下标开始，High则最大的下标开始

        Pivot = A[0] ;
        Low = Left ;
        High = Right -1 ;

        // 移动。大的放右边，小的放左边
        while (1)
        {
            // 移动脚本
            while(A[++Low] < Pivot) ;
            while(A[--High] > Pivot) ;

            // 上面两个while结束，代表Low指向了一个比P大的点，High指向了一下小的点
            // 如果还没遍历完（Low和High还未交叉）
            if(Low < High) Swap(&A[Low] , &A[High]) ;
            else break;
        }

        Swap(&A[Low] , &A[Right-1]) ; // 将基准换到正确的位置

        // 递归调用左右两块
        Qsort(A,Left , Low-1) ;
        Qsort(A,Low+1 , Right) ;

}

// 一个统一的调用函数
void QuickSort(ElementType A[] , int N){
    Qsort(A,0,N-1);
}
```

# 归并排序  
归并是一种经典的分治，将数组分为两块不断计算顺序，然后合并  
C语言实现中，我们将Merge的部分和Sort的部分分开，然后用一个接口调用  
其如下：    
```c
// 归并排序 

// L左边起始位置  ， R 右边起始位置 ， End终点位置（右侧    
void Merge(ElementType A[] , ElementType TmpA[] , int L ,int R ,int End){
    // 将有序的A[L] -> A[R-1]和 A[R]->A[End] 归并为一个有序序列 
    int leftEnd , NumElements , Tmp ; 
    int i ; 

    leftEnd = R-1 ; //左侧终点  
    Tmp = L ;  // 起始位置  

    NumElements = End-L+1 ; //计算数组总数

    // 归并
    while(L <= leftEnd && R <= End){
        if(A[L] <= A[R])    TmpA[Tmp++] = A[L++] ; 
        else                TmpA[Tmp++] = A[R++] ; 
    }

    // 对于剩下的进行处理   
    while(L <= leftEnd) TmpA[Tmp++] = A[L++] ; 
    while(R <= End)     TmpA[Tmp++] = A[R++] ; 

    for(i=0 ; i<NumElements ; i++,End--){
        // 复制回原数组 
        A[End] = TmpA[End] ;
    }
}

// 归并函数的核心递归排序
void M_Sort(ElementType A [] , ElementType TmpA[] , int L ,int End){
    int Center ; 

    if(L < End){
        Center = (L+End) / 2 ;
        M_Sort(A,TmpA,L,Center); // 递归解决左边
        M_Sort(A,TmpA,Center+1,End);// 递归解决右边

        // 进行合并操作
        Merge(A,TmpA,L,Center,End); //这里是Merge
    }
}

// 统一调用函数 
void MergeSort(ElementType A[] , int N){
    ElementType *TmpA ; 
    // 生成临时数组 
    TmpA = (ElementType *)malloc(N * sizeof(ElementType)); 

    if(TmpA != NULL ){
        M_Sort(A,TmpA,0,N-1);
        // 调用结束记得释放空间
        free(TmpA );
    }else{
        printf("空间不足，失败 \n") ; 
    }
}
```

# 基数排序  

## 桶排序   
当数据量小时，直接用一个记录“数据”次数的组，比如G[1]就代表数字"1"的出现次数 
然后遍历原数组，计数，最后将得到的G数组依次输出即可     
伪代码：    
```c
void BucketSort(ElementType A [] , int N){
    count[] 初始化

    while(依次读入数值num){
        将其加入count[num]链表
    }

    for(遍历count[]链表){
        if(count[i]){
            输出
        }
    }
}
```

## 基数排序 


# 查找  
**查找表**是由同一类型的数据元素/记录 构成的集合    
只做查找操作的查找表，被称为**静态查找表**      
在查找同时还进行增删操作的，是**动态查找表**    

## 静态查找表   
在静态查找表中，操作和遍历类似，只是多加了比较数值的部分    
一般而言，可以设置一个哨兵在数据组开头，然后从后往前进行查找    

### 二分搜索    
这里以在顺序存储的表Tb中寻找元素X为例：    

```c
// 二分查找 
#define NotFound 0 /* 找不到就返回 0 */ 

Position BinarySearch(List Tb , ElementType K){
    Position left , right , mid ; 

    left = 1 ;//设左边起点是1
    right = Tb->Last ; //右端则是Tb的最后一部分 

    while(left <= right){
        // 两个端点不交叉就一直进行 
        mid = (left + right)/2 ; 
        if(K < Tb->Data[mid])   right = mid-1 ; // 调整右边界   
        else if(K->Tb->Data[mid])   left = mid+1 ; // 调整左边界    
        else return mid ; //查找成功的情况
    }

    return NotFound ; // 如果while结束还没有找到，那么说明查找不成功    
}

```

## 动态查找表       

### 二叉树/平衡二叉树   
见**树**的相关部分  

### B-树和B+树  

### 键树/数字查找树     

## 哈希表   

# 树    
查找：给定某个关键词K，从集合R中找出和K相同的记录   
静态查找：记录一直是固定的  
动态查找：记录是动态变化的，比如有插入和删除操作    

树的核心是二叉树，二叉树可以使用顺序或者链式的存储方式  
二叉树各种算法的核心是遍历算法，包括中序，前序，后续遍历，已经层级遍历（从上到下，从左往右）    

更多概念性的东西见参考书，这里只提供实现代码    

## 遍历算法实现 
```c
// 中序遍历 
void InorderTraversal_Mid(BinTree BT){
    if(BT){
        // 搜索的顺序即 ： 左，中，右   
        InorderTraversal_Mid(BT->Left);
        printf("%d " , BT->Data);
        InorderTraversal_Mid(BT->Right);
    }
}

// 先序遍历 
void InorderTraversal_Front(BinTree BT){
    if(BT){
        // 搜索的顺序即 ： 中，左，右   
        printf("%d " , BT->Data);
        InorderTraversal_Front(BT->Left);
        InorderTraversal_Front(BT->Right);
    }
}

// 后序遍历 
void InorderTraversal_Back(BinTree BT){
    if(BT){
        // 搜索的顺序即 ： 左，右, 中   
        InorderTraversal_Back(BT->Left);
        InorderTraversal_Back(BT->Right);
        printf("%d " , BT->Data);
    }
}

// 层序遍历 
void LevelTraversal(BinTree BT){
    Queue Q ; // 利用队列   
    BinTree T ; //存储从队列头得到的元素
    if(!BT) return ; 

    Q = CreateQueue();
    AddQ(Q,BT);

    while (!isEmpty(Q))
    {
        // 当Q存在元素  
        T =  DeleteQ(Q) ; //取出头
        printf("%d " , T->Data) ; 
        if(T->Left) AddQ(Q,T->Left);
        if(T->Right) AddQ(Q,T->Right);
        
    }
    
}

// 非递归算法的中序遍历 
void InorderTraversal(BinTree BT){
    BinTree T ;
    Stack S = CreatStack() ; // 使用堆栈结构来进行存储  

    T = BT ;
    while(T || !IsEmpty(S)){
        while(T){
            push(S,T) ; 
            T = T->Left ; 
        }
        T = Pop(S) ; 
        printf("%d" , T->Data) ;
        T = T -> Right ; 
    }
}
/*
    沿左子树不断深入，然后返回，然后进行右子树
    在沿左子树深入时，进行一个结点就将其压入堆栈；当左分支无法深入时，则返回，弹出结点。此时：
    先序遍历：在入栈之前就进行访问
    中序遍历：在弹出时进行访问，然后向右深入
    后序遍历：将结点二次入栈，然后从该结点的右子树继续深入，依旧进入一个结点入栈一个结点；深入不下去再返回，直到第二次从栈中弹出结点再访问  
    > 详见书    
*/
``` 

## 二叉搜索树   

### 查找    
因为二叉树本身的结构性质，因此搜索查找的方式和二分法类似    
```c
// 递归实现：   
Position IterFind(ElementType X , BinTree BST){
    if(!BST)  return NULL ;  //最后一圈下来没找到就是没了   
    if(X > BST->Data){
        return Find(X , BST->Right) ; //X更大，向右递归 
    }else if ( X < BST->Data){
        return Find(X , BST->Left) ; //X更大，向右递归 
    }else{
        return BST ; //找到 
    }
}


// 迭代实现： 
Position IterFind(ElementType X , BinTree BST){
    while(BST){
        if(X > BST->Data){
            BST = BST->Right ; // 过大则向右移动
        }else if(X < BST->Data){
            BST = BSR -> Left ; //否则向左移动  
        }else{
            // 相等的时候则是找到了
            return BST ; 
        }
    }

    return NULL; // 循环结束还没有找到就是没有
}
```

最大元素一定是在树的最右分支的端结点上      
最小元素一定是在树的最左分支的端结点上  

```c
// 查找最小值
Position FindMin(BinTree BST){
    if(!BST) return NULL ;
    else if(!BST) {
        return BST ; 
    }else{
        return FindMin(BST -> Left) ; 
    }
}

// 查找最大值
Position FindMax(BinTree BST){
    if(BST)
        while(BST->Right) BST = BST->Right ; //持续向右搜索 

    return BST ; 
}
``` 

### 插入    
核心思路如下：  
函数会有一个带结点的返回值，指示插入方向，比如：    
大的情况：  
NodeA ->Right = Insert() ; 
这种情况，如果不是新加入的位置，即NodeA->Right本来就有合适值，那么实质上对树不会有影响  
而如果是(!BST)的情况，那么则说明找到了相应的位置    
这时候生成结点并且返回，然后又前一个结点则可以按要求将它成功插入    
```c
BinTree Insert(ElementType X , BinTree BST){
    if(!BST){
        // 生成一个头结点   
        BST = malloc(sizeof(sturct TreeNode)) ; 
        BST->Data = X ; 
        BST->Left = BST->Right  = NULL ; 
    }else{
        //寻找插入位置  
        if(X < BST->Data)   BST->Left = Insert(X , BST->Left) ;
        else if(X > BST->Data)  BST->Right = Insert(X , BST->Right) ; 
    }

    return BST  ;

}
``` 

### 删除    
叶结点：直接删除，删掉然后把父结点指向它的指针设为NULL  
要删除的结点只有一个子结点：将其父结点的指针指向要删除的结点的孩子结点      
左右结点均有：用另外的结点代替删除结点，右子树的最小元素或者左子树的最大元素    

```c
BinTree Delete(ElementType X , BinTree BST){
    Position Tmp ; 
    if(!BST) printf("未找到要删除的元素 \n") ; 

    else if(X < BST->Data)  BST->Left = Delete(X,BST->Left) ; //递归向左
    else if(X > BST->Data)  BST->Right = Delete(X,BST->Right) ; //递归向右
    else{
        //找到了要删除的结点    
        if(BST -> Left && BST->Right){
            // 左右两个结点都在 
            Tmp = FindMin(BST->Right) ; //找右子树最小值    
            BST-> Data = Tmp->Data ; 
            BST-> Right = Delete(BST->Data , BST->Right) ; //在删除的结点的右子树中删除最小元素 

        }else{
            // 被删除结点有一个结点或者没有子结点   
            Tmp = BST ; 
            if(!BST->Left){
                // 有右子结点或者无子结点 
                BST = BST->Right ; 
            }else if(!BST -> Right){
                // 有左子结点或者无子结点 
                BST = BST->Left ; 
            }

            free(Tmp) ; //释放
        }
    }

    return BST; 
}
``` 
### 生成    
二叉树的创建有先序创建和层序创建两种方法。这里，所使用的是层序创建的方式    
层序创建所用的结点输入序列是按树的**从上到下，从左到右**的顺序形成的，以0来代表空结点（这里设树寸的数据是int），在此过程中，设有一个队列暂时存储各结点的地址    

实现如下：  
```c
BinTree CreateBintree(){
    Element Data ; 
    BinTree BT , T  ; 
    Queue Q = CreateQueue();// 创建空队列   

    int NoInfo = 0 ;  // 此处认为0是存储空的意思  

    /* 建立根结点 */
    scanf("%d" , &Data) ; 
    if(Data != NoInfo){
        // 此处认为0是存储空的意思  
        BT = (BinTree)malloc(sizeof(struct Node)) ;
        BT->Data = Data ; 
        BT->Right = BT->Left = NULL; 

        AddQ(Q,BT) ; // 入队，准备开始创建一整棵树
    }

    // 接下来按照“取出结点->建立左右子树->读数据->入队相应数据”的方式不断创建结点   

    while (!isEmpty(Q))
    {
        T = DeleteQ(Q) ;
        // 检查左子结点
        scanf("%d" , &Data) ; 
        if(Data == NoInfo)  T->Left = NULL ; 

        else{
            // 分配新的结点(左子结点)
            T->Left = (BinTree)malloc(sizeof(struct Node)) ; 
            T->Left->Data = Data ;
            // 定义其子树(先置为空)
            T->Left->Left = T->Left->Right = NULL ; 
            AddQ(Q,T->Left);
        }
        // 检查右子结点
        scanf("%d" , &Data) ;
        if(Data == NoInfo)  T->Right = NULL ; 

        else{
            // 分配新的结点(右子结点)
            T->Right = (BinTree)malloc(sizeof(struct Node)) ; 
            T->Right->Data = Data ;
            // 定义其子树(先置为空)
            T->Right->Left = T->Right->Right = NULL ; 
            AddQ(Q,T->Right);
        }
    }// 结束创建
    
    return BT ; // 返回创建的根结点
}
```

## 平衡树AVL        
平衡树是一种**维持某种状态**（主要是高度）的二叉搜索树  
由于其重要性，特别拿出一节来写  

平衡因子BF(T)：对于结点T，BF(T) = 左子树高度-右子树高度 

平衡二叉树AVL树：空树，或者任一结点左、右子树高度差的绝对值不超过1  

维护平衡的情况详见书或者：  
https://www.bilibili.com/video/BV1H4411N7oD?p=45&spm_id_from=pageDriver&vd_source=a23924f530b04d473aede41031674a4c  

这里不好描述，因此就只提供实现代码 ：   

### 旋转调整代码    
```c
// 左单旋算法   
AVLTree SingLL(AVLTree A){
    // 发生了LL不平衡
    // 最终返回的是B    
    /*
        1.设置B，B是原本A的左子树   
        2.将A的左子树更新设为B的右子树  
        3.将A自身设置为B的左子树    
    */
    AVLTree B = A->Left ; 
    A->Left = B->Right ; 
    B->Right = A ; 

    // 更新高度 
    A->Height = Max(GetHeight(A->Left) , GetHeight(A->Right)) +1 ;
    B->Height = Max(GetHeight(B->Left) , GetHeight(B->Right)) +1  ; 
    //B->Height = Max(GetHeight(B->Left) , A->Height) +1  ; 

    return B ; 
}


// 右单旋算法   
AVLTree SingRR(AVLTree A){
    // 和左单旋类似，用于发生了RR不平衡的情况   
    /*
        1.设置B，B是A的右子树   
        2.将A的右子树更新为B的左子树    
        3.将A自身设置为B的左子树    
    */
    AVLTree B = A->Right ; 
    A->Right = B->Left ; 
    B->Left = A  ;

    // 更新高度 
    A->Height = Max(GetHeight(A->Left) , GetHeight(A->Right)) +1 ;
    B->Height = Max(GetHeight(B->Left) , GetHeight(B->Right)) +1  ; 
}

// 左右双旋 
// 适用于LR不平衡 
// 注意，因为数据的问题，应该先对A的子树操作，再操作A。
// 实质上是先对A的子树用了RR旋转，然后对A自己做LL旋转   

AVLTree DoubleLR(AVLTree A){
    // 对A的左子树做右旋    
    // 然后对A自己做左旋    
    A->Left = SingRR(A->Left) ; 
    return SingLL(A) ;
} 

// 右左双旋 
// 适用于RL不平衡   
AVLTree DoubleRL(AVLTree A){
    A->Right = SingLL(A->Right) ; 
    return SingRR(A) ;
}
```

### 插入代码    
```c
AVLTree Insert(AVLTree T , ElementType X){
    // 插入空树的情况   
    if(!T){
        T = (AVLTree)malloc(sizeof(struct AVLNode)) ; 
        T->Data = X ; 
        T->Height = 1 ; 
        T->Left = T->Right = NULL ; 
    }

    else if(X < T->Data){
        // 插入左子树的情况 
        T->Left = Insert(T->Left , X);
        // 此时只可能发生左旋的情况或者LR情况   
        if(GetHeight(T->Left) - GetHeight(T->Right) == 2){
            // 大于2的插值就是发生不平衡了
            // 下面通过插入位置来判断是哪种不平衡   
            if(X < T->Left ->Data){
                T = SingLL(T) ; //插在左边
            }else{
                T = DoubleLR(T) ; 
            }
        }
    }
    else if(X > T->Data){
        // 插在右子树的情况 
        T->Right = Insert(T->Right , X) ; 
        // 如果需要右旋 
        if(GetHeight(T->Left) - GetHeight(T->Right) == -2){
            // 同上文的判断方式 
            if(X > T->Right->Data){
                T = SingRR(T);
            }else{
                T= DoubleRL(T);
            }
        }
    }

        // 更新树高度   
    T->Height = Max(GetHeight(T->Left) ,GetHeight(T->Right)) + 1 ; 
    
    return T ; 
}
```


# 哈夫曼树  
带权路径长度WPL：设二叉树有n个叶子结点，每个叶子结点有权重w，根结点到每个叶子结点的长度是l。则这些每个的叶子结点的带权路径长度之和就是WPL   

哈夫曼树：WPL最小的树   

## 哈夫曼树的构造   
核心：**每次把权值最小的两棵二叉树合并**    

实例代码如下：  
```c

```

## 哈夫曼树的特点   
1.没有度为1的结点   
2.n个叶子结点的哈夫曼树共有2n-1个结点   
3.哈夫曼树的任意非叶节的左右子树交换后仍是哈夫曼树  
4.对同一组权值，可能有两课不同构的哈夫曼树  

## 哈夫曼编码   
详见书本部分    
或者视频部分：  
https://www.bilibili.com/video/BV1H4411N7oD?p=58&spm_id_from=pageDriver&vd_source=a23924f530b04d473aede41031674a4c  


# 图的表示  
图表示了**多对多**的关系    
图包含一组顶点，一组边来表示边的集合    

度：从该点发出的边数叫“出度”，指向该点的边数为“入度”    

## 数组/邻接矩阵    
使用```G[N][N]```来表示 
比如```G[i][j] = 1 ```就是i->j的距离是1，或者存在。如果是0则不可达  
用这种方法可以表示图    

### 实现    
```c
#include <stdio.h> 
#include <stdlib.h>

#define MaxVertexNum 100  //定义最大有100个顶点    
#define INFINITY 65535  //最大值，表示无限即两个点不相连   
#define TRUE 1 
#define FALSE 0  

typedef int Vertex ; // 顶点下标表示顶点    
typedef int WeightType ; // 权重    
typedef int DataType ;  // 存储的数据    
typedef int bool ;  

//===================
// 队列
# include <stdio.h>
# include <stdlib.h>

#define FALSE 0;
#define TRUE 1   ;
#define ERROR -1 ;

typedef int ElementType ;
typedef int bool ;

typedef struct Node * PtrToNode ;
struct Node
{
    ElementType Data ;
    PtrToNode Next ;
};

typedef PtrToNode Position ;

typedef struct QNode * PtrToQNode ;

struct QNode
{
    Position Front , Rear ; //分别指向头和尾的指针
    int Size ; //维护一个容量
};

typedef PtrToQNode Queue;

// 创建队列与基本操作
Queue CreateQueue(){
    Queue Q ;
    Q = (PtrToQNode)malloc(sizeof(struct QNode));
    Q->Front = NULL ;
    Q->Rear = NULL;
    Q->Size = 0 ;

    return Q ;
}

bool isEmpty(Queue Q){
    return (Q->Front == NULL) ; // 头结点的next是空
}

int getSize(Queue Q){
    return Q->Size ;
}

// 操作和删除
bool AddQ(Queue Q , ElementType X){
    Position tmp ;
    tmp = (PtrToNode)malloc(sizeof(struct Node)) ;
    tmp->Data = X ;
    tmp->Next = NULL ;

    if(Q->Front == NULL){
        // 插入的是第一个结点
        // ! 注意，这一步无论"带不带头结点"都需要判断是不是第一个插入进去的指针，否则会造成结点直接连接失败（Front会一直指向NULL）
        Q->Front = tmp ;
        Q->Rear = tmp ;
    }else{
        // 非第一个结点
        Q->Rear->Next = tmp ; //更新tmp的插入位置
        Q->Rear = tmp ; // 尾指针指向tmp
    }

    Q->Size++ ;
    printf("成功加入 %d , 当前size为%d \n" , Q->Rear->Data , Q->Size);

}

ElementType DeleteQ(Queue Q){
    Position FrontCell ;//一个存储当前头结点的指针
    ElementType FrontEle ; // 头部数据

    if(isEmpty(Q)){
        printf("队列空，删除失败 \n") ;
        return ERROR ;
    }else{
        // 获取所要的元素
        FrontCell = Q->Front ;
        FrontEle = FrontCell->Data ;
        // 处理队列
        if(Q->Front == Q->Rear){
            //如果队列只有一个元素
            Q->Front = Q->Rear = NULL; // 直接置空队列就是删除
        }else{
            Q->Front = FrontCell->Next ; // Front直接指向下一位就完成了操作
        }

        // 释放空间
        free(FrontCell) ;
        Q->Size--;
        printf("完成出队，当前size为 %d \n" , Q->Size) ;

        return FrontEle ;
    }
}


//


/* 定义图的结点 */  
typedef struct GNode *PtrToGNode ; 

struct GNode
{
    int Nv ; //顶点数   
    int Ne ; //边数 

    WeightType G [MaxVertexNum][MaxVertexNum]; 
    DataType Data [MaxVertexNum] ; // 顶点数据，没有则可以省略   

};

typedef PtrToGNode MGraph ; 

// 然后设计边   
typedef struct ENode * PtrToENode ; 

struct ENode{
    Vertex V1,V2 ; 
    WeightType Weight ; /* 权重 */  
};
typedef PtrToENode Edge ; 

MGraph  CreateGraph(int VertexNum){
    // 初始化一个有VertexNum个顶点但是没有边的图    
    Vertex V,W ;
    MGraph  Graph ;

    // 建立图
    Graph = (MGraph)malloc(sizeof(struct GNode)) ; 
    Graph->Nv = VertexNum ;//有VertexNum个顶点
    Graph->Ne = 0 ; 

    // 初始化矩阵   
    // 默认顶点编号从0开始，到 Nv-1 结束

    for(V = 0 ; V < Graph->Nv ; V++)    
        for(W = 0 ;W < Graph->Nv ; W++)
            Graph->G[V][W] = INFINITY ; 

    return Graph ; 
}

void InsertEdge(MGraph Graph , Edge E){
    // 插入边   
    Graph->G[E->V1][E->V2] = E->Weight ; //写入边的两个点和权重 

    Graph->G[E->V2][E->V1] = E->Weight ; 
}

// 创建图
MGraph BuildGraph(){
    // 初始化各参数
    MGraph Graph ;
    Edge E ;
    Vertex V; 
    int Nv  , i ; 
    printf("读入顶点数\n");
    scanf("%d" , &Nv) ; 
    printf("读入顶点数成功\n");


    Graph = CreateGraph(Nv) ; // 创建图 
    printf("创建图成功\n");
    
    printf("\n读入边数 \n");
    scanf("%d" , &(Graph->Ne)) ; //读入边数 
    printf("读入边成功 \n === \n 边：%d 顶点: %d  \n" ,Graph->Nv , Graph->Ne);
    if(Graph->Ne != 0){
        /* 如果有边 */
        E = (Edge)malloc(sizeof(struct ENode)) ; 

        // 读入并接入   
        for(i = 0 ; i < Graph ->Ne ; i++){
            scanf("%d %d %d",&E->V1,&E->V2,&E->Weight) ; 
            printf("读入 ： %d 到 %d , 权重 %d",E->V1,E->V2,E->Weight);
            // 这里要按情况写读入

            InsertEdge(Graph,E) ;
            printf("读入 ： %d 到 %d , 权重 %d  \n",E->V1,E->V2,E->Weight);

        }
    }

    printf("\n 读入结束 \n") ; 

    // 如果有读入数据的要求的话，读入数据   
    // for(V = 0 ; V < Graph->Nv ; V++)
    //     scanf("%d" , &(Graph ->Data[V]));

    return Graph ; 
}

void printGraph(MGraph M){
    int l = M->Nv ; 
    int i , j ; 

    for(i = 0 ; i <l ; i++){
        for(j = 0 ; j < l ;j++){
            printf("%d " , M->G[i][j]) ; 
        }
            printf("\n") ;
    }
}

void Visit(Vertex V){
    printf("正在访问顶点 %d \n" , V) ; 
}

// BFS进行遍历  
bool IsEdge(MGraph Graph , Vertex V , Vertex W){
    return Graph->G[V][W] < INFINITY ? 1:0 ; 
}

void BFS(MGraph Graph , Vertex S ,int* Visited, void(*Visit)(Vertex)){
    // Visited是外部给予的（可以是全局变量或者遍历的时候给的）的数组，记录到达与否
    Queue Q ; 
    Vertex V,W ; 

    Q=CreateQueue(999) ;//创建并设置队列最大值为999
    Visit(S) ; 
    AddQ(Q,S) ; // S和Q入队列   

    while(!isEmpty(Q)){
        V = DeleteQ(Q) ; // 弹出V 
        for(W = 0 ; W < Graph->Nv ; W++){
            if(!Visited[W] && IsEdge(Graph , V , W)){
                Visit(W) ; 
                Visited[W] = TRUE ; 
                AddQ(Q,W) ; 
            }
        }
    }
}

int main(){
    MGraph  M ;
    M = BuildGraph();
    printGraph(M) ;

    return 0 ;
}
```

## 邻接表   
```G[N]```为指针数组，对应矩阵每行一个链表，只存非0元素 
主要使用一个数组来存表头（及其指针），然后链接各点来达到目的

### 实现
```c
#include <stdio.h> 
#include <stdlib.h>

#define MaxVertexNum 100  //定义最大有100个顶点    
#define INFINITY 65535  //最大值，表示无限即两个点不相连   
#define TRUE 1 
#define FALSE 0 

typedef int Vertex ; // 顶点下标表示顶点    
typedef int WeightType ; // 权重    
typedef int DataType ;  // 存储的数据    

// 然后设计边   
typedef struct ENode * PtrToENode ; 

struct ENode{
    Vertex V1,V2 ; 
    WeightType Weight ; /* 权重 */  
};
typedef PtrToENode Edge ; 

/* 邻接点定义 */    
typedef struct AdjVNode *PtrToAdjVNode ; 
struct AdjVNode{
    Vertex AdjV ;
    WeightType Weight ;
    PtrToAdjVNode Next ;
};

// 顶点表头结点 
typedef struct Vnode{
    PtrToAdjVNode FirstEdge ;
    DataType Data ;
} AdjList [MaxVertexNum] ; 

// 图结点   
typedef struct GNode *PtrToGNode ; 
struct GNode
{
    int Nv ; // 顶点
    int Ne ; // 边数
    AdjList G ; // 邻接表   
};
typedef PtrToGNode LGraph ; 

//初始化
LGraph CreateGraph(int length){
    Vertex V ; 
    LGraph Graph ; 

    Graph = (LGraph)malloc(sizeof(struct GNode)) ; 
    Graph->Nv = length ; // 顶点数  
    Graph->Ne = 0  ;

    //初始化邻接表表头指针
    for(V=0 ; V<Graph->Nv ; V++){
        Graph->G[V].FirstEdge = NULL ; //
    }

    return Graph ; 
}

void InsertEdge(LGraph Graph , Edge E){
    // 插入边<V1,V2>
    
    PtrToAdjVNode NewNode ; //建立新结点  
    // 初始化新结点 , 为V2建立新的邻接点    
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode)) ; 
    NewNode ->AdjV = E->V2 ; 
    NewNode ->Weight = E->Weight; 

    // 将V2插入V1的表头 
    NewNode->Next = Graph->G[E->V1].FirstEdge ; 
    Graph->G[E->V1].FirstEdge = NewNode ; 

    // 如果是无向图，还要顺带插入<V2,V1>
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode)) ; 
    NewNode ->AdjV = E->V1 ; 
    NewNode ->Weight = E->Weight; 
    // 将V1插入V2的表头 
    NewNode->Next = Graph->G[E->V2].FirstEdge ; 
    Graph->G[E->V2].FirstEdge = NewNode ; 

    // Graph->Ne的数值这里在BuildGraph中进行了指定  
}

LGraph BuildGraph(){
    LGraph Graph ; 
    Edge E ; 
    Vertex V ; 
    int Nv,i ; 
    printf("读入顶点数\n");
    scanf("%d" , &Nv) ; 
    printf("读入顶点数成功\n");

    Graph = CreateGraph(Nv);
    printf("创建图成功\n");
    
    printf("\n读入边数 \n");
    scanf("%d",&(Graph->Ne)) ; //边数   

    printf("读入边成功 \n === \n 边：%d 顶点: %d  \n" ,Graph->Nv , Graph->Ne);
    if(Graph->Ne != 0){
        // 读边
        E = (Edge)malloc(sizeof(struct ENode)) ; 

        for(i=0;i<Graph->Ne;i++){
            scanf("%d %d %d",&E->V1 , &E->V2,&E->Weight) ;

            printf("读入 ： %d 到 %d , 权重 %d \n",E->V1,E->V2,E->Weight);

            InsertEdge(Graph,E) ; 
        }
    }

    //如果有读入数据的要求的话，还需读入数据    
    // for(V=0;V<Graph->Nv;V++)    scanf("%d",&(Graph->G[V].Data)) ; 

    return Graph ; 
}

// 遍历 
void Visit(Vertex V){
    printf("正在访问顶点 %d \n" , V) ; 
}

void DFS(LGraph Graph , Vertex V ,int* Visited ,  void(*Visit)(Vertex)){
    // 以V为出发s点进行DFS
    PtrToAdjVNode W ; 
    Visit(V) ;
    Visited[V] = TRUE ;

    for(W = Graph->G[V].FirstEdge ; W ; W=W->Next){
        if(!Visited[W->AdjV]){
            DFS(Graph , W->AdjV,Visited , Visit) ; 
        }
    } 
}

int main(){
    LGraph g ; 
    g = BuildGraph() ; 
    int Visited [999] ; 
    int i ; 
    for(i =0 ; i < 999 ; i++)   Visited[i] = 0 ;
    DFS(g , 0 ,Visited, Visit);

    return 0 ; 
}
```

## 十字链表     

## 邻接多重表   

# DFS   
这里以邻接表为例    
```c
// dfs
void Visit(Vertex V){
    printf(" 访问顶点： %d \n",V);
}

void DFS(LGraph Graph , Vertex V , void(*Visit)(Vertex)){
    // 从V出发对Graph进行搜索   
    PtrToAdjVNode w ; 

    Visit(V) ; Visited[V] = TRUE ; 

    for(w = Graph->G[V].FirstEdge ; w ;w=w->Next){
        if(!Visited[w->AdjV]){
            DFS(Graph,w->AdjV,Visit);
        }
    }
}
```

# BFS   
这里以邻接矩阵为例  
```c
// bfs
void Visit(Vertex V){
    printf(" 访问顶点： %d \n",V);
}

bool IsEdge(MGraph Graph , Vertex V , Vertex W){
    return Graph->G[V][W] < INFINITY ? TRUE : FALSE ; 
}


void BFS (MGraph Graph , Vertex S , void(*Visit)(Vertex)){
    Queue Q ; 
    Vertex V, W ;

    Q = CreateQueue(MaxSize) ; // 创建一个空队列预备

    // 开始搜索并入队
    Visit(S);
    Visitrd[S] = TRUE ; 
    AddQ(Q,S); 

    while(!IsEmpty(Q)){
        V = DeleteQ(Q) ; 
        for(W=0 ; W<Grapg->Nv;W++){
            if(!Visited[W] && IsEdge(Graph,V,W)){
                // 访问顶点 
                Visit(W) ; 
                Visited[W] = TRUE ; 
                AddQ(Q,W);
            }
        }
    }
}
```


# 连通性问题    

# 最小生成树    
最小生成树存在，图一定连通  

> 没必要专门使用树的结构来存，使用一个数组来存每一个点的parent即可  

## Prim算法 
一步步生成最小生成树    

```c
#define ERROR -1    
#define INFINITY 65535  //最大值，表示无限即两个点不相连   

// 寻找最短Dist
Vertex FindMinDist(MGrapg Graph , WeightType dist[]){
    Vertex MinV , V ; 
    WeightType MinDist = INFINITY ; 

    for(V = 0 ;V < Graph->Nv ; V++){
        if(dist[V] != 0 && dist[V] <MinDist){
            MinDist = dist[V] ; 
            MinV = V ; 
        }
    }

    if(MinDist < INFINITY){
        return MinV ; 
    }else{
        return ERROR ; 
    }
}

int Prim(MGraph Graph , LGraph MST){
    // 将最小生成树保存为邻接表存储的图MST  
    WeightType dist[MaxVertexNum] , TotalWeight ; 
    Vertex parent[MaxVertexNum] , V,M ;
    int Vcount ; 
    Edge E ; 

    // 初始化
    for(V = 0 ; V <Graph->Nv ; V++){
        dist[V] = Graph->G[0][V] ; 
        parent[V] = 0 ; 
    }

    TotalWeight = 0 ; 
    VCount = 0 ; 

    // 创建图
    MST= CreateGraph(Graph->Nv) ; 
    E = (Edge)malloc(sizeof(struct ENode));
    
    // 收录初始点
    dist[0] = 0 ; 
    Vcount++ ; 
    parent[0] = -1 ; 

    while(1){
        V = FindMindDist(Graph, dist) ;  // 得到最小边的顶点V

        if(V == ERROR)  break ; 

        // 设置加入的边 VParent->V ,权重为Weight
        E->V1 = parent[V] ;  //
        E->V2 = V ; 
        E->Weight =dist[V] ; 
        InsertEdge(MST , E) ;
        TotalWeight += dist[V] ; 
        dist[V] = 0 ; VCount++ ;

        for(W = 0 ; W < Graph->Nv ; W++){
            if(dist[W]!=0 && Graph->G[V][W] < INFINITY){
                // 开始遍历V的每个邻接点并判断  
                if(Graph->G[V][W]  < dist[W]){
                    dist[W] = Graph->G[V][W] ; //更新dist 
                    parent[W] = V  ; //更新距离
                }
            }
        }
    } 

    // while结束代表从起始点开始的尝试结束  
    // 此时检查是否得到了最小生成树

    if(VCount  < Graph ->Nv)    TotalWeight = ERROR ; 

    return TotalWeight ; 
}

```

## Kruskal算法  
将森林合并成树  
在Kruskal里面，MST收集的是边而非顶点    
由于Kruskal所要的前置数据结构过多，这里（和书里）只提供伪代码   

```c
int Kruskal(LGtaph Graph , LGraph MST){
    //
    MST = {包含所以顶点但没有边的图} ; 
    while(MST中收集的边不到Graph->Nv-1  && 原图的边集合E != NULL){
        1.从E中选择最小代价边(使用最小堆)   
        2.从E中删除此边

        if((V,W)的选取不在MST中构成回路){
            (V,W)加入MST； 
            // 判断“构成回路”使用并查集的FIND，加入MST使用并查集的Union 
        }else{
            丢弃(V,W);
        }

        // 同样进行检查 
        if(MST中收集的边不到Graph->Nv-1) return ERROR ; 
        else return MinWeight ;
    }
}
```


# 最短路径  

## 单源最短路径 
### 无权
无权图的单源最短路径根据BFS魔改一下即可，其伪代码类似： 
```c
void UnWeighted_Find(Vertex S){
    EnQueue(S,Q) ; 
    while(!IsEmpty(Q)){
        V = Dequeue(Q) ; 

        for(V的每个邻接点W){
            // 一般采用邻接链表存储 
            if(dist[w] == -1){
                //dist是w点到源点的距离
                // 在无权图中我们用一个特殊的数值表示其未访问过即可 
                dist[w] = dist[v]+1 ; 
                path[w] = v ; 
                //path记录“到达w的必经点”也就是w的上一个顶点
                // 需要输出路径的情况下，可以利用一个Stack来输出结果
                Enqueue(W,Q) ;
            }
        }
    }
}
```

### 有权
采用dijkstra算法计算有权图的单源最短路径    
核心：```dist[w] = min{dist[w] , dist[v] + <v,w>}```    
```c
// 浙大版   
Vertex FinMinDist(MGraph Graph , int dist[] , int collected[]){
    // 用于返回“未收录顶点”的最小者 
    Vertex MinV , V ; 
    int MinDist  = INFINITY ; 

    for(V=0 ; V < Graph->Nv ; V++){
        // 遍历V并寻找
        if(collected[V]==FALSE && dist[V] < MinDist){
            // 记录最小距离和对应的点
            MinDist = dist[V] ; 
            MinV = V ;
        }
    }

    if(MinDist <INFINITY)   return MinV ; //还能找到最小值  
    else return ERROR ; // 返回错误标记 
}

bool Dijkstra(MGraph Graph, int dist[] , int path[] , Vertex S){
    int b[MaxVertexNum] ; //标记数组    
    Vertex V , W ;

    // 初始化：把边读入（这里默认了在Graph已经把不存在的边标记为了INFINITY）
    // 其次是设置路径path和标记数组
    for(V = 0  ; V < Graph->Nv ; V++){
        dist[V] = Graph->G[S][V] ; //与目标点直接相连的顶点 
        path[V] = -1 ; b[V] = FALSE ;
    }

    // 收入起点 
    dist[S] = 0 ; b[S] = TRUE ;

    // 算法核心
    while(1){
        // 寻找“未收录顶点”的最小者 
        V = FinMinDist(Graph , dist , b) ;
        if(V==ERROR){
            // 没找到的情况，代表循环应该结束   
            break;
        }
        //
        // 否则收人V并更新
        b[V] = TRUE ; 
        for(W = 0 ; W< Graph->Nv ; W++){
            // 检查W，需要更新的W满足以下条件   
            // 1.是V是邻接点  2.未被b收录
            if(b[W] == FALSE &&  Graph->G[V][W] < INFINITY){
                if(Graph ->G[V][W] < 0) return FALSE ;//不能有负边的情况的

                // 判断是否更新
                if(dist[V] + Graph[V][W] < dist[W]){
                    // 找到了新的更小值就更新   
                    dist[W] = dist[V] + Graph[V][W] ; 
                    path[W] = V ; // V是新的更小点  
                }
            }
        }

    } // END WHILE

    return TRUE ; 
}
```


```c
// 清华版
void ShortestPath_DIJ(MGraph G , int V0, PathMatrix* P , ShortPathTabel* D){
    // 图 ， 起点 ，P最短路径 ， D带权长度    
    // P[V][W] = TRUE , 则w是从v0到v当前求得最短路径上的顶点    
    // final[V] = TRUE ; 当且仅当已经求得V0到V的最短路径    

    for(v = 0 ; v < G.vexnum ; ++v){
        final[v] = FALSE ;  // 首先先将每一个
        D[v] = G.arcs[v0][v] ; 

    for(w = 0 ; w< G.vexnum ; ++w)  p[v][v] = FALSE ;  // 先设置空路径  

        if(D[V] < INFINITY){
            P[v][v0] = TRUE ; 
            p[v][v] = TRUE ; 
        }
    }

    D[V0] = 0 ; final[v0] = TRUE ; // 初始化，v0顶点属于S集 

    //开始主循环，算法的核心    
    // 每次循环得到一个v0到v的最短路径，然后加入S集
    for(i=1 ; i <G.vexnum;++i){
        min = INFINITY ; 

        for(w = 0 ; w<G.vexnum ;++w){
            if(!final[w])
                if(D[w] < min){
                    // w顶点更近的情况
                    v = w ; 
                    min = D[w] ; 
                }
        }

        final[v] = TRUE ; 
        for(w=0;w<G.vexnum; ++w){
            // 进行更新
            if(!final[w] && (min+G.arcs[v][w] < D[w])){
                D[w] = min + G.arcs[v][w] ; 
                P[w] = P[v] ; 
                P[w][w] = TRUE ;  // P[W] = P[V]+[W]
            }
                
        }
    }

}
```

## 多源最短路   
```c
bool Floyd(MGraph Graph , WeightType D[][MaxVertexNum] , Vertex path[][MaxVertex-Num]){
    // 图 ， 距离值 ， 路径结果
    Vertex i,j,k ; 

    // 初始化
    for(i=0 ; i < Graph->Nv ; i++)
        for(j=0 ; j  < Graph->Nv ; j++){
            D[i][j] = Graph->G[i][j] ; 
            path[i][j] = -1 ; 
        }

    for(k=0 ; k <Graph->Nv;k++)
        for(i=0 ; i < Graph->Nv ; i++)
            for(j=0 ; j  < Graph->Nv ; j++){
                // 检查与更新   
                if(D[i][k] + D[k][j] < D[i][j]){
                    D[i][j] = D[i][k] + D[k][j] ;
                    if(i==j && D[i][j] < 0 ){
                        // 处理负值圈   
                        return FALSE
                    }

                    // 正常情况则记录新的ijk
                    path[i][j] = k ; // 意思是从i->j的最短路径现在经过k
                }
            }
    return TRUE ; 
}

```

```c
// 清华版
void ShortestPath_FLOYD(MGrapg G , PathMatrix * p[] , DistanceMatrix * D){
    // D是带权路径
    // P[v][w][u] = TRUE , 代表u是从v->w最短路径上的点

    // 初始化
    for(v = 0 ; v <G.vexnum ; ++v){
        for(w = 0 ; w <G.vexnum ; ++w){
            D[v][w] = G.arcs[v][w] ; 

            // 初始化路径情况
            for(u = 0;u<G.vexnum ; ++u)     P[v][w][u] = FALSE ;

            //设置已有路径  
            if(D[v][w] < INFINITY){
                p[v][w][v] = TRUE ;
                P[v][w][w] = TRUE;
            }
        }
    }

    // 进行核心算法
    for(u=0 ; u<G.vexnum ; ++u)
        for(v=0 ; v<G.vexnum ; ++v)
            for(w=0 ; w<G.vexnum ; ++w){
                // 进行更新判断 
                if(D[v][u] + D[u][w] < D[v][w]){
                    D[v][w] = D[v][u] + D[u][w] ;
                    for(i = 0 ; i<G.vexnum;++i){
                        P[v][w][i] = P[v][u][i] || P[u][w][i] ; 
                    }
                }
            }

}
````


# 拓扑排序  
AOV如果有合理的拓扑序，则必定是有向无环图    
> 用顶点表示活动，用弧表示活动间的优先关系的有向图称为顶点表示活动的网（Activity On Vertex Network)，简称AOV网  

拓扑排序在输出时候的核心就是**输出没有前驱，或者说没有入度**的结点  
每次输出一个顶点V->记录并删除V->修改V的邻接点的入度 

> 此外，如果在循环查找的过程中发现没有符合“未输出且入度为0的顶点”，则说明图中存在回路   

## 简易版本拓扑 O|V|^2  
这里提供伪代码：    
```c
bool TopSort(Graph Graph , Vertex TopOrder[]){
    //TopOrder[]是排序的结果

    //遍历图，得到一个收集各顶点入度的数组 Indegree[]
    //
    for(cnt = 0 ; cnt < Graph -> Nv ; cnt++){
        V = 未输出的入度为0的顶点 ; // 可以使用直接数组遍历的方法，也可以使用下文优化的方法 
        if(不存在这样的V){
            // 没有跳出循环的情况下，找不到这种V了
            // 那么说明存在回路
            printg("图中存在回路") ; 
            break ;
        }

        TopOrder[cnt] = V ; //记录
        /* 将V和出边进行删除操作 */

        // 下面更新V的邻接点    
        for(V的每一个邻接点W)   Indegree[w]-- ;
    }

    // 检测是否成功 
    if(cnt!=Graph->Nv)  return FALSE ; 
    else return TRUE ; 

}
```

## 改进拓扑 O|V+E|  
主要是对“ V = 未输出的入度为0的顶点”一步做出了优化  
利用一个容器（这里是Queue）一直更新并存储**即将入度为0的点**    

```c
bool TopSort(LGraph Grapg , Vertex TopOrder[]){
    // 初始声明数据
    int Indegree[MaxVertexNum] , cnt ; 
    Vertex V ; 
    PtrToAdjVNode W ; 
    Queue Q = CreateQueue(Graph->Nv) ; 
    // 
    for(V=0 ; V<Graph ->Nv ; V++)   Indegree[V] = 0 ; // 初始化入度数组 

    // 遍历图完成Indegree[]*
    for(V=0;V<Graph->Nv ; V++)
        for(W = Graph->G[V].FirstEdge ; W ; W = W->Next)
            // 这里遍历W，因为是链接表的FirstEdge,实际上就是遍历了点    
            // 然后通过W相连的点，去得到下一个点的入度情况  
            Indegree[W->AdjV]++ ;  // AdjV 是W对应的点  

    for(V=0 ; V<Graph ->Nv ; V++)
        if(Indegree[V] == 0)    AddQ(Q,V) ; //将入度为0的入队列 
    
    // 进行拓扑操作 
    cnt = 0 ; 
    while(!IsEmpty(Q)){
        // 弹出并记录   
        V = DeleteQ(Q) ; 
        TopOrder[cnt++] = V ; 
        // 

        // 对于V的每个邻接点都进行更新，这里邻接点即V->AdjV 
        for(W = Graph->G[V].FirstEdge ; W ; W=W->Next){
            // 这一步不仅进行W的更新，还进行入队检测
            if(--Indegree[W->AdjV]== 0) {
                AddQ(Q,W->AdjV) ; 
            }
        }
    }

    // 进行是否成功的检测   
    if(cnt != Graph->Nv)    return FALSE ; 
    else    return TRUE ; 
}
```

# 关键路径  
关键路径是拓扑排序的重要应用    
关键路径指的是**绝对不允许延误的活动**组成的路径    
