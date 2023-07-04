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
