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
