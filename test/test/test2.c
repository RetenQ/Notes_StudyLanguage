
#include <stdio.h>
#include <stdlib.h>


//================
// ����ɵ����ݽṹ�ļ�
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
    Position Front , Rear ; //�ֱ�ָ��ͷ��β��ָ��
    int Size ; //ά��һ������
};

typedef PtrToQNode Queue;

// �����������������
Queue CreateQueue(){
    Queue Q ;
    Q = (PtrToQNode)malloc(sizeof(struct QNode));
    Q->Front = NULL ;
    Q->Rear = NULL;
    Q->Size = 0 ;

    return Q ;
}

bool isEmpty(Queue Q){
    return (Q->Front == NULL) ; // ͷ����next�ǿ�
}

int getSize(Queue Q){
    return Q->Size ;
}

// ������ɾ��
bool AddQ(Queue Q , ElementType X){
    Position tmp ;
    tmp = (PtrToNode)malloc(sizeof(struct Node)) ;
    tmp->Data = X ;
    tmp->Next = NULL ;

    if(Q->Front == NULL){
        // ������ǵ�һ�����
        // ! ע�⣬��һ������"������ͷ���"����Ҫ�ж��ǲ��ǵ�һ�������ȥ��ָ�룬�������ɽ��ֱ������ʧ�ܣ�Front��һֱָ��NULL��
        Q->Front = tmp ;
        Q->Rear = tmp ;
    }else{
        // �ǵ�һ�����
        Q->Rear->Next = tmp ; //����tmp�Ĳ���λ��
        Q->Rear = tmp ; // βָ��ָ��tmp
    }

    Q->Size++ ;
    printf("�ɹ����� %d , ��ǰsizeΪ%d \n" , Q->Rear->Data , Q->Size);

}

ElementType DeleteQ(Queue Q){
    Position FrontCell ;//һ���洢��ǰͷ����ָ��
    ElementType FrontEle ; // ͷ������

    if(isEmpty(Q)){
        printf("���пգ�ɾ��ʧ�� \n") ;
        return ERROR ;
    }else{
        // ��ȡ��Ҫ��Ԫ��
        FrontCell = Q->Front ;
        FrontEle = FrontCell->Data ;
        // �������
        if(Q->Front == Q->Rear){
            //�������ֻ��һ��Ԫ��
            Q->Front = Q->Rear = NULL; // ֱ���ÿն��о���ɾ��
        }else{
            Q->Front = FrontCell->Next ; // Frontֱ��ָ����һλ������˲���
        }

        // �ͷſռ�
        free(FrontCell) ;
        Q->Size--;
        printf("��ɳ��ӣ���ǰsizeΪ %d \n" , Q->Size) ;

        return FrontEle ;
    }
}
//================
typedef struct TreeNode *BinTree;
typedef BinTree Postion ;

struct TreeNode
{
    ElementType Data;
    BinTree Left ;
    BinTree Right ;
};


// �������
void InorderTraversal_Mid(BinTree BT){
    if(BT){
        // ������˳�� �� ���У���
        InorderTraversal_Mid(BT->Left);
        printf("%d " , BT->Data);
        InorderTraversal_Mid(BT->Right);
    }
}

// �������
void InorderTraversal_Front(BinTree BT){
    if(BT){
        // ������˳�� �� �У�����
        printf("%d " , BT->Data);
        InorderTraversal_Front(BT->Left);
        InorderTraversal_Front(BT->Right);
    }
}

// �������
void InorderTraversal_Back(BinTree BT){
    if(BT){
        // ������˳�� �� ����, ��
        InorderTraversal_Back(BT->Left);
        InorderTraversal_Back(BT->Right);
        printf("%d " , BT->Data);
    }
}

// �������
void LevelTraversal(BinTree BT){

}
