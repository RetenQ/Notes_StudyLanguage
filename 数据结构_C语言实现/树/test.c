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