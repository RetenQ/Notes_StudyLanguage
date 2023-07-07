# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

#define FALSE 0
#define TRUE 1
#define ERROR -1

// typedef int ElementType ;
typedef int bool ;


#define MAXDATA 9999  //�趨һ���ڱ���Ϊ���ѵĶ���
#define MINDATA -9999  //�趨һ���ڱ���Ϊ���ѵĶ���

// ���ŵ�ַ��

// ��������
#define MAXTABLESIZE 100000

// �������������ڵõ�һ�����õ�����
int NextPrime(int N){
    // ���ش���N�Ҳ�����MAXTABLESIZE����С����
    int i , p = (N%2) ? N+2 : N+1 ; //��������ʼ

    while (p <= MAXTABLESIZE)
    {
        for(i = (int)sqrt(p) ;  i > 2 ; i--){
            if(!(p%i))  break;  // p��������
        }
        if(i==2) break; // for����������˵��p������
        else p+=2 ;
    }
    return p ;
}

// λ��ӳ�亯��
int Hash(const char *Key , int TableSize){
    unsigned int H = 0 ;
    while(*Key != '\0') {
        H = (H<<5) + *Key++ ;
    }

    return H%TableSize ;
}

// �ṹ����
#define KEYLENGTH 15
typedef char ElementType[KEYLENGTH+1] ;  // ʹ���ַ������ؼ���
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

    // ��ʼ����
    H = (HashTable)malloc(sizeof(struct TBLNode)) ;
    H->TableSize = NextPrime(TabelSize) ;

    // �����ͷ
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode)) ;

    for(i = 0 ; i < H->TableSize ; i++){
        H->Heads[i].Data[0] = '\0' ;
        H->Heads[i].Next = NULL ;
    }

    return H ;
}

// ����
Position Find(HashTable H , ElementType Key){
    Position P ;
    Index Pos ;

    Pos = Hash(Key , H->TableSize) ;
    P = H->Heads[Pos].Next ;

    // ��ʼ���Ѱ��
    while (P && strcmp(P->Data , Key))
    {
        P = P->Next ; // ����ǰ��
    }

    // �ҵ�֮������������û�ҵ�������û�ҵ�ʱ����NULL��
    return P ;
}

// ����
bool Insert(HashTable H , ElementType Key){
    Position P , NewCell ;
    Index Pos ;

    P = Find(H,Key) ;
    if(!P){
        // �ؼ���δ�ҵ�,����Բ���
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data , Key) ; // ���ؼ���д��

        Pos = Hash(Key,H->TableSize); // ��ʼɢ��λ��

        // ��NewCell����ΪH->Heads[Pos]����ĵ�һ�����
        NewCell ->Next = H->Heads[Pos].Next ;
        H ->Heads[Pos].Next = NewCell ;
        return TRUE ;
    }else{
        // �ؼ��ʴ���
        printf("�ؼ����Ѵ��� \n") ;
        return FALSE ;
    }
}

// �ͷ�ɢ�б�
void DestoryTable(HashTable H){
    int i ;
    Position P,Tmp ;

    // �ͷ�ÿһ�����
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
