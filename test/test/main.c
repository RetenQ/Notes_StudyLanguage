# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

#define FALSE 0
#define TRUE 1
#define ERROR -1

// typedef int ElementType ;
typedef int bool ;


#define MAXDATA 9999  //设定一个哨兵作为最大堆的顶点
#define MINDATA -9999  //设定一个哨兵作为最大堆的顶点

// 开放地址法

// 分离链接
#define MAXTABLESIZE 100000

// 辅助函数，用于得到一个可用的素数
int NextPrime(int N){
    // 返回大于N且不超过MAXTABLESIZE的最小素数
    int i , p = (N%2) ? N+2 : N+1 ; //从奇数开始

    while (p <= MAXTABLESIZE)
    {
        for(i = (int)sqrt(p) ;  i > 2 ; i--){
            if(!(p%i))  break;  // p不是素数
        }
        if(i==2) break; // for正常结束，说明p是素数
        else p+=2 ;
    }
    return p ;
}

// 位移映射函数
int Hash(const char *Key , int TableSize){
    unsigned int H = 0 ;
    while(*Key != '\0') {
        H = (H<<5) + *Key++ ;
    }

    return H%TableSize ;
}

// 结构声明
#define KEYLENGTH 15
typedef char ElementType[KEYLENGTH+1] ;  // 使用字符串当关键字
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

    // 初始化表
    H = (HashTable)malloc(sizeof(struct TBLNode)) ;
    H->TableSize = NextPrime(TabelSize) ;

    // 分配表头
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode)) ;

    for(i = 0 ; i < H->TableSize ; i++){
        H->Heads[i].Data[0] = '\0' ;
        H->Heads[i].Next = NULL ;
    }

    return H ;
}

// 查找
Position Find(HashTable H , ElementType Key){
    Position P ;
    Index Pos ;

    Pos = Hash(Key , H->TableSize) ;
    P = H->Heads[Pos].Next ;

    // 开始逐个寻找
    while (P && strcmp(P->Data , Key))
    {
        P = P->Next ; // 不断前移
    }

    // 找到之后跳出，或者没找到跳出（没找到时返回NULL）
    return P ;
}

// 插入
bool Insert(HashTable H , ElementType Key){
    Position P , NewCell ;
    Index Pos ;

    P = Find(H,Key) ;
    if(!P){
        // 关键词未找到,则可以插入
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data , Key) ; // 将关键词写入

        Pos = Hash(Key,H->TableSize); // 初始散列位置

        // 将NewCell插入为H->Heads[Pos]链表的第一个结点
        NewCell ->Next = H->Heads[Pos].Next ;
        H ->Heads[Pos].Next = NewCell ;
        return TRUE ;
    }else{
        // 关键词存在
        printf("关键词已存在 \n") ;
        return FALSE ;
    }
}

// 释放散列表
void DestoryTable(HashTable H){
    int i ;
    Position P,Tmp ;

    // 释放每一个结点
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
