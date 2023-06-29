# include <stdio.h>
# include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define ERRORPOS NULL ;
#define NOFIND NULL ;
#define INFEASIBLE -1
#define OVERFLOW -2
#define bool int ;

// Status 是函数的类型，其值是函数结果状态代码
typedef int Status ;
typedef int ElementType  ;

# define MAXSIZE 100

typedef struct GNode * PtrToGNode ; 
typedef PtrToGNode GList ; 

struct GNode
{
    int Tag ; //0表示是单元素，1表示是表

    union 
    {
        ElementType Data ; 
        GList SubList ; 
    } URegion;

    PtrToGNode Next ; //指向后继结点    
};


int main(){
    return 0 ;

}




