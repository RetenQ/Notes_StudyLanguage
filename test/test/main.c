# include <stdio.h>
# include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define ERROR -1

typedef int ElementType ;
typedef int bool ;


#define MAXDATA 9999  //设定一个哨兵作为最大堆的顶点
#define MINDATA -9999  //设定一个哨兵作为最大堆的顶点

void Swap(ElementType *a , ElementType *b){
    ElementType t = *a ;
    *a = *b ;
    *b = t ;
}

// 归并排序

// L左边起始位置  ， R 右边起始位置 ， End终点位置（右侧
void Merge(ElementType A[] , ElementType TmpA[] , int L ,int R ,int End){
    // 将有序的A[L] -> A[R-1]和 A[R]->A[End] 归并为一个有序序列
    int leftEnd , NumElements , Tmp ;
    int i ;

    leftEnd = R-1 ; //左侧终点
    Tmp = L ;  // 起始位置

    NumElements = End-L+1 ; //计算数组总数

    // 归并
    while(L <= leftEnd && R <= End){
        if(A[L] <= A[R])    TmpA[Tmp++] = A[L++] ;
        else                TmpA[Tmp++] = A[R++] ;
    }

    // 对于剩下的进行处理
    while(L <= leftEnd) TmpA[Tmp++] = A[L++] ;
    while(R <= End)     TmpA[Tmp++] = A[R++] ;

    for(i=0 ; i<NumElements ; i++,End--){
        // 复制回原数组
        A[End] = TmpA[End] ;
    }
}

// 归并函数的核心递归排序
void M_Sort(ElementType A [] , ElementType TmpA[] , int L ,int End){
    int Center ;

    if(L < End){
        Center = (L+End) / 2 ;
        M_Sort(A,TmpA,L,Center); // 递归解决左边
        M_Sort(A,TmpA,Center+1,End);// 递归解决右边

        // 进行合并操作
        Merge(A,TmpA,L,Center,End); //这里是Merge
    }
}

// 统一调用函数
void MergeSort(ElementType A[] , int N){
    ElementType *TmpA ;
    // 生成临时数组
    TmpA = (ElementType *)malloc(N * sizeof(ElementType));

    if(TmpA != NULL ){
        M_Sort(A,TmpA,0,N-1);
        // 调用结束记得释放空间
        free(TmpA );
    }else{
        printf("空间不足，失败 \n") ;
    }
}

int main(){

    return 0  ;
}
