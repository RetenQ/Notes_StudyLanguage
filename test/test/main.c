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
