#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100  //���������100������
#define INFINITY 65535  //���ֵ����ʾ���޼������㲻����
#define TRUE 1
#define FALSE 0

typedef int Vertex ; // �����±��ʾ����
typedef int WeightType ; // Ȩ��
typedef int DataType ;  // �洢������

// Ȼ����Ʊ�
typedef struct ENode * PtrToENode ;

struct ENode{
    Vertex V1,V2 ;
    WeightType Weight ; /* Ȩ�� */
};
typedef PtrToENode Edge ;

/* �ڽӵ㶨�� */
typedef struct AdjVNode *PtrToAdjVNode ;
struct AdjVNode{
    Vertex AdjV ;
    WeightType Weight ;
    PtrToAdjVNode Next ;
};

// �����ͷ���
typedef struct Vnode{
    PtrToAdjVNode FirstEdge ;
    DataType Data ;
} AdjList [MaxVertexNum] ;

// ͼ���
typedef struct GNode *PtrToGNode ;
struct GNode
{
    int Nv ; // ����
    int Ne ; // ����
    AdjList G ; // �ڽӱ�
};
typedef PtrToGNode LGraph ;

//��ʼ��
LGraph CreateGraph(int length){
    Vertex V ;
    LGraph Graph ;

    Graph = (LGraph)malloc(sizeof(struct GNode)) ;
    Graph->Nv = length ; // ������
    Graph->Ne = 0  ;

    //��ʼ���ڽӱ��ͷָ��
    for(V=0 ; V<Graph->Nv ; V++){
        Graph->G[V].FirstEdge = NULL ; //
    }

    return Graph ;
}

void InsertEdge(LGraph Graph , Edge E){
    // �����<V1,V2>

    PtrToAdjVNode NewNode ; //�����½��
    // ��ʼ���½�� , ΪV2�����µ��ڽӵ�
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode)) ;
    NewNode ->AdjV = E->V2 ;
    NewNode ->Weight = E->Weight;

    // ��V2����V1�ı�ͷ
    NewNode->Next = Graph->G[E->V1].FirstEdge ;
    Graph->G[E->V1].FirstEdge = NewNode ;

    // ���������ͼ����Ҫ˳������<V2,V1>
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode)) ;
    NewNode ->AdjV = E->V1 ;
    NewNode ->Weight = E->Weight;
    // ��V1����V2�ı�ͷ
    NewNode->Next = Graph->G[E->V2].FirstEdge ;
    Graph->G[E->V2].FirstEdge = NewNode ;

    // Graph->Ne����ֵ������BuildGraph�н�����ָ��
}

LGraph BuildGraph(){
    LGraph Graph ;
    Edge E ;
    Vertex V ;
    int Nv,i ;
    printf("���붥����\n");
    scanf("%d" , &Nv) ;
    printf("���붥�����ɹ�\n");

    Graph = CreateGraph(Nv);
    printf("����ͼ�ɹ�\n");

    printf("\n������� \n");
    scanf("%d",&(Graph->Ne)) ; //����

    printf("����߳ɹ� \n === \n �ߣ�%d ����: %d  \n" ,Graph->Nv , Graph->Ne);
    if(Graph->Ne != 0){
        // ����
        E = (Edge)malloc(sizeof(struct ENode)) ;

        for(i=0;i<Graph->Ne;i++){
            scanf("%d %d %d",&E->V1 , &E->V2,&E->Weight) ;

            printf("���� �� %d �� %d , Ȩ�� %d \n",E->V1,E->V2,E->Weight);

            InsertEdge(Graph,E) ;
        }
    }

    //����ж������ݵ�Ҫ��Ļ��������������
    // for(V=0;V<Graph->Nv;V++)    scanf("%d",&(Graph->G[V].Data)) ;

    return Graph ;
}

// ����
void Visit(Vertex V){
    printf("���ڷ��ʶ��� %d \n" , V) ;
}

void DFS(LGraph Graph , Vertex V ,int* Visited ,  void(*Visit)(Vertex)){
    // ��VΪ����s�����DFS
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
