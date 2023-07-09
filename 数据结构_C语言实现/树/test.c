#include <stdio.h> 
#include <stdlib.h>

#define MaxVertexNum 100  //定义最大有100个顶点    
#define INFINITY 65535  //最大值，表示无限即两个点不相连   
#define TRUE 1 
#define FALSE 0 

typedef int ElementType ;
typedef int bool ;
typedef int Vertex ; // 顶点下标表示顶点    
typedef int WeightType ; // 权重    
typedef int DataType ;  // 存储的数据    

// AVL树的基础类型  
typedef struct AVLNode * Position; 
typedef Position AVLTree ; 

typedef struct AVLNode{
    ElementType Data ;
    AVLTree Left  ;
    AVLTree Right ; 

    int Height ; 
};

int GetHeight(AVLTree T){
    return T->Height  ;
}

int Max(int a , int b){
    return a>b ? a:b ; 
}

// 左单旋算法   
AVLTree SingLL(AVLTree A){
    // 发生了LL不平衡
    // 最终返回的是B    
    /*
        1.设置B，B是原本A的左子树   
        2.将A的左子树更新设为B的右子树  
        3.将A自身设置为B的左子树    
    */
    AVLTree B = A->Left ; 
    A->Left = B->Right ; 
    B->Right = A ; 

    // 更新高度 
    A->Height = Max(GetHeight(A->Left) , GetHeight(A->Right)) +1 ;
    B->Height = Max(GetHeight(B->Left) , GetHeight(B->Right)) +1  ; 
    //B->Height = Max(GetHeight(B->Left) , A->Height) +1  ; 

    return B ; 
}


// 右单旋算法   
AVLTree SingRR(AVLTree A){
    // 和左单选类似，用于发生了RR不平衡的情况   
    /*
        1.设置B，B是A的右子树   
        2.将A的右子树更新为B的左子树    
        3.将A自身设置为B的左子树    
    */
    AVLTree B = B->Right ; 
    A->Right = B->Left ; 
    B->Left = A  ;

    // 更新高度 
    A->Height = Max(GetHeight(A->Left) , GetHeight(A->Right)) +1 ;
    B->Height = Max(GetHeight(B->Left) , GetHeight(B->Right)) +1  ; 
}

// 左右双旋 
// 适用于LR不平衡 
// 注意，因为数据的问题，应该先对A的子树操作，再操作A。
// 实质上是先对A的子树用了RR旋转，然后对A自己做LL旋转   

AVLTree DoubleLR(AVLTree A){
    // 对A的左子树做右旋    
    // 然后对A自己做左旋    
    A->Left = SingRR(A->Left) ; 
    return SingLL(A) ;
} 

// 右左双旋 
// 适用于RL不平衡   
AVLTree DoubleRL(AVLTree A){
    A->Right = SingLL(A->Right) ; 
    return SingRR(A) ;
}

AVLTree Insert(AVLTree T , ElementType X){
    // 插入空树的情况   
    if(!T){
        T = (AVLTree)malloc(sizeof(struct AVLNode)) ; 
        T->Data = X ; 
        T->Height = 1 ; 
        T->Left = T->Right = NULL ; 
    }

    else if(X < T->Data){
        // 插入左子树的情况 
        T->Left = Insert(T->Left , X);
        // 此时只可能发生左旋的情况或者LR情况   
        if(GetHeight(T->Left) - GetHeight(T->Right) == 2){
            // 大于2的插值就是发生不平衡了
            // 下面通过插入位置来判断是哪种不平衡   
            if(X < T->Left ->Data){
                T = SingLL(T) ; //插在左边
            }else{
                T = DoubleLR(T) ; 
            }
        }
    }
    else if(X > T->Data){
        // 插在右子树的情况 
        T->Right = Insert(T->Right , X) ; 
        // 如果需要右旋 
        if(GetHeight(T->Left) - GetHeight(T->Right) == -2){
            // 同上文的判断方式 
            if(X > T->Right->Data){
                T = SingRR(T);
            }else{
                T= DoubleRL(T);
            }
        }
    }

        // 更新树高度   
    T->Height = Max(GetHeight(T->Left) ,GetHeight(T->Right)) + 1 ; 
    
    return T ; 
}


int main(){


    return 0 ; 
}