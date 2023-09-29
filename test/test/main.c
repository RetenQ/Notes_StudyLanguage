#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void swap(int *a , int *b )
{
    int tmp = *a ;
    *a = *b ;
    *b = tmp ;
}

void quick_Sort(int a[] , int l , int r){
    if(l >= r) return ;

    int i = l - 1 ;
    int j = r + 1 ;
    int x = a[(i+j)/2] ;

    while(i<j){
            do{ i ++; }while(a[i] < x) ;
            do{ j --; }while(a[j] > x) ;

            if(i < j) swap(&a[i] , &a[j])  ;

    }

    quick_Sort(a,l,j);
    quick_Sort(a,j+1,r);

}




int main(){
    int N ;
    scanf("%d" , &N) ;
    int a [N] ;

    int i ;
    for(i = 0 ; i < N ; i++)
    {
        int tmp ;
        scanf("%d" , &tmp) ;
        a[i] = tmp ;
    }


    quick_Sort(a,0,N-1);

    for(i = 0 ; i < N ; i++)
    {
        printf("%d ",a[i]);
    }
}
