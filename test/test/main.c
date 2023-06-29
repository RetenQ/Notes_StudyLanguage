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
        printf("栈为空,POP失败");
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
