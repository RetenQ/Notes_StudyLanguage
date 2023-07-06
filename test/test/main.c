# include <stdio.h>
# include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define ERROR -1

typedef int ElementType ;
typedef int bool ;


#define MAXDATA 9999  //�趨һ���ڱ���Ϊ���ѵĶ���
#define MINDATA -9999  //�趨һ���ڱ���Ϊ���ѵĶ���

void Swap(ElementType *a , ElementType *b){
    ElementType t = *a ;
    *a = *b ;
    *b = t ;
}

// �鲢����

// L�����ʼλ��  �� R �ұ���ʼλ�� �� End�յ�λ�ã��Ҳ�
void Merge(ElementType A[] , ElementType TmpA[] , int L ,int R ,int End){
    // �������A[L] -> A[R-1]�� A[R]->A[End] �鲢Ϊһ����������
    int leftEnd , NumElements , Tmp ;
    int i ;

    leftEnd = R-1 ; //����յ�
    Tmp = L ;  // ��ʼλ��

    NumElements = End-L+1 ; //������������

    // �鲢
    while(L <= leftEnd && R <= End){
        if(A[L] <= A[R])    TmpA[Tmp++] = A[L++] ;
        else                TmpA[Tmp++] = A[R++] ;
    }

    // ����ʣ�µĽ��д���
    while(L <= leftEnd) TmpA[Tmp++] = A[L++] ;
    while(R <= End)     TmpA[Tmp++] = A[R++] ;

    for(i=0 ; i<NumElements ; i++,End--){
        // ���ƻ�ԭ����
        A[End] = TmpA[End] ;
    }
}

// �鲢�����ĺ��ĵݹ�����
void M_Sort(ElementType A [] , ElementType TmpA[] , int L ,int End){
    int Center ;

    if(L < End){
        Center = (L+End) / 2 ;
        M_Sort(A,TmpA,L,Center); // �ݹ������
        M_Sort(A,TmpA,Center+1,End);// �ݹ����ұ�

        // ���кϲ�����
        Merge(A,TmpA,L,Center,End); //������Merge
    }
}

// ͳһ���ú���
void MergeSort(ElementType A[] , int N){
    ElementType *TmpA ;
    // ������ʱ����
    TmpA = (ElementType *)malloc(N * sizeof(ElementType));

    if(TmpA != NULL ){
        M_Sort(A,TmpA,0,N-1);
        // ���ý����ǵ��ͷſռ�
        free(TmpA );
    }else{
        printf("�ռ䲻�㣬ʧ�� \n") ;
    }
}

int main(){

    return 0  ;
}
