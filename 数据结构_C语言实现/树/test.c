#include <stdio.h>
#include <stdlib.h>


//================
// 已完成的数据结构文件
#define FALSE 0;
#define TRUE 1   ;
#define ERROR -1 ;

typedef struct TreeNode *BinTree;
typedef BinTree Postion ;

typedef int Element;

struct TreeNode
{
    Element Data;
    BinTree Left ; 
    BinTree Right ;
};

typedef BinTree ElementType ;
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
//================



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

// 层序生成 
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

// AVL
typedef struct AVLNode * AVLPosition ;
typedef AVLPosition AVLTree ;
typedef int ElementAVL ; 
typedef struct AVLNode{
    ElementAVL Data ; 
    AVLTree Left ; 
    AVLTree Right ; 
    int Height ; 
};

int Max(int a , int b){
    return a>b ? a:b  ; 
}

int GetHight(AVLTree A){
    // 得到高度
    return A->Height ; 
}

AVLTree SingleLeftRotation(AVLTree A){
    // 左单旋   

    AVLTree B = A->Left ; 
    A->Left = B->Right ; 
    B->Right = A ; 

    // 调整高度
    A->Height = Max(GetHight(A->Left) , GetHight(A->Right)) + 1 ;
    B->Height = Max(GetHight(B->Left) , A->Height) +1 ;
}

AVLTree SingRightRotation(AVLTree A){

}

AVLTree DoubleLR_Rotation(AVLTree A){
    // 对A的左子树做一次右单旋
    A->Left = SingRightRotation(A->Left);
    // 对A自身做一次左单旋
    return SingleLeftRotation(A) ; 
}

AVLTree DoubleRL_Rotation(AVLTree A){

}

AVLTree Insert(AVLTree T , ElementAVL X){
    if(!T){
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X ; 
        T->Height = 1 ; 
        T->Left = T->Right = NULL ; 
    }
    else if(X < T->Data){
        // 插入T的左子树    
        T->Left = Insert(T->Left , X) ;
        // 检查是否需要左旋
        if(GetHight(T->Left) - GetHight(T->Right) == 2){

            // 如果需要左旋
            if(X < T->Left ->Data)  T = SingleLeftRotation(T) ; //左单旋    
            else    T= DoubleLR_Rotation(T) ; //左右双旋
        
        }
    }
    else if(X > T->Data){
            // 插入T的右子树    
            T->Right = Insert(T->Right , X); 

            // 检查是否需要右旋 
            if(GetHight(T->Left) - GetHight(T->Right) == -2){
                if(X > T->Right->Data)  T = SingRightRotation(T) ; //右单旋
                else    T = DoubleRL_Rotation(T) ; // 右左双旋
            }
    }

        // 其他情况就是树中已经有这个数据了，那么无需插入   
    T->Height = Max(GetHight(T->Left) , GetHight(T->Right)) +1 ;
    
    return T ;
}

int main(){

    return 0 ; 
}