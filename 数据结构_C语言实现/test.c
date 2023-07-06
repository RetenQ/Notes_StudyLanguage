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


int main(){

    return 0  ;
}
