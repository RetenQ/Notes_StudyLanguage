# include <stdio.h>
# include <stdlib.h>

#define FALSE -1 ;
#define TRUE 1   ;
#define ERROR -1 ;

typedef int ElementType ;
typedef int bool ;

typedef struct SNode * PtrToSNode ;
struct SNode
{
    ElementType Data ;
    PtrToSNode Next ;
};

typedef PtrToSNode Stack ;

// ����
Stack InitStack(){
    Stack S ;
    S = (Stack)malloc(sizeof(struct SNode)) ;
    S -> Next = NULL ;  // ͷ���ָ��մ��������ʱΪ��

    return S ;
}

// �ж��Ƿ�Ϊ�գ���ʽջû���������
bool isEmpty(Stack S){
    return S->Next == NULL ;
}

// Push Ĭ�ϵ�һ�������ջ��,Ҳ����ͷ����Next��Ԫ�صĶ�����Ԫ��
bool Push(Stack S , ElementType x){
    PtrToSNode tmp = (PtrToSNode)malloc(sizeof(struct SNode)) ;
    tmp->Data = x ;
    tmp->Next = S->Next ;
    S->Next = tmp ;

    return TRUE ;
}

// Pop
ElementType Pop(Stack S){
    PtrToSNode FirstCell ;
    ElementType TopEle ;

    if(isEmpty(S)){
        printf("ջΪ��,POPʧ��");
        return ERROR ;
    }else{
        // �õ���ֵ
        FirstCell = S->Next ;
        TopEle = FirstCell->Data ;

        // ����ջ
        S->Next = FirstCell->Next ; //��S��Nextָ��ԭ��First����һ��Ԫ�ؼ���
        free(FirstCell );//�ͷſռ�

        return TopEle ;
    }
}

// ���Ժ���
int main(){
    Stack S = InitStack() ;
    printf("����01234�������\n");
    int k = 0 ;
    for(k = 0 ; k < 5 ; k++){
        Push(S,k) ;
    }

    printf("����Push����\n");
    for(k = 0 ; k < 6 ; k++){
        int tmp = Pop(S) ;
        if(tmp == -1){
            printf("ȡ��ʧ��");
        }else{
            printf("�˴�ȡ���� %d \n" , tmp);
        }
    }

    return 0 ;
}
