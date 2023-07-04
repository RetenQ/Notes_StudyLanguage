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
    Position Front , Rear ; //�ֱ�ָ��ͷ��β��ָ��
    int Size ; //ά��һ�����ֵ
};

typedef PtrToQNode Queue;

// �����������������
Queue CreateQueue(){
    Queue Q ;
    Q = (PtrToQNode)malloc(sizeof(PtrToQNode));

    // ����ͷ���
    Position _head ;
    _head = (Position)malloc(sizeof(struct Node));
    _head->Data = 0 ;
    _head->Next = NULL ;

    // ��ͷβ��ָ�붼ָ��ͷ���
    Q->Front = Q->Rear = _head ; //�Ȱ�ͷβ������Ϊ�յ�ͷ���

    Q->Size = 0 ;

    return Q ;
}

bool isEmpty(Queue Q){
    return (Q->Front == Q->Rear) ;
    // ��ͷβָ����ͬһ�������ǿ�
}

// ������ɾ��
bool AddQ(Queue Q , ElementType X){
    Position tmp ;
    tmp = (PtrToNode)malloc(sizeof(struct Node)) ;
    tmp->Data = X ;
    tmp->Next = NULL ;

    if(Q->Front == NULL){
        // ������ǵ�һ�����
        Q->Front = tmp ;
        Q->Rear = tmp ;
    }else{
        // �ǵ�һ�����
        Q->Rear->Next = tmp ; //����tmp�Ĳ���λ��
        Q->Rear = tmp ; // βָ��ָ��tmp
    }
    Q->Size++;

    printf("�ɹ����� %d , ��ǰsizeΪ%d \n" , Q->Rear->Data , Q->Size);


    return TRUE ;
}

ElementType DeleteQ(Queue Q){
    // �����жϿ�
    if(isEmpty(Q)) {
        printf("�ն��У�����ʧ�� \n") ;
        return ERROR ;
    }else{

        // �Ȼ�ȡ��ӦԪ��

        Position frontP = Q->Front->Next ; //Ҫ�õ�Front��Next���Ŷԣ��൱��˳��������Ƚ���++
        ElementType ElementP = frontP ->Data ;

        if( frontP == Q->Rear){
            // ���һ��Ԫ�س��ӣ�ֱ�ӽ����й�0
            Q->Rear = Q->Front ;
        }else{
            Q->Front->Next = frontP->Next ; //ͷָ��ָ���Next�ض���Ϊԭ��P����һ��Ԫ�أ��ﵽɾ��P��Ŀ��
        }


        // ִ�в���


        // �����ͷŲ�����size�޸�
        Q->Size-- ;

        free(frontP) ;

        printf("��ɳ��� %d����ǰsizeΪ %d \n" ,ElementP, Q->Size) ;



        return ElementP ;
    }
}

// ���Ժ���
int main(){
    printf("\n���ɱ��\n");
    Queue Q = CreateQueue() ; //���Ϊ5
    printf("\n�������Ԫ��\n");
    int k = 0 ;
    for(k = 1 ; k <= 5 ;k++){
        AddQ(Q,k) ;
    }
    printf("��������Ԫ��\n");
    int tmp =0 ;
    tmp = DeleteQ(Q) ;
    printf("���ӣ� %d \n" , tmp) ;
    tmp = DeleteQ(Q) ;
    printf("���ӣ� %d \n" , tmp) ;
    printf("\n��������Ԫ��\n");
    AddQ(Q,77) ;AddQ(Q,88) ;
    printf("\n�����ټ���һ��Ԫ��\n");
    AddQ(Q,99);

    printf("��˳����г���ֱ�����п�\n");
    while(Q->Size > 0){
        tmp = DeleteQ(Q) ;
        printf("���ӣ� %d \n" , tmp) ;
    }
    return 0 ;
}
