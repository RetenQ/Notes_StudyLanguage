#include <stdio.h>
//��Ϊ��Ҫ��˵��Ƕ��ѭ���ģ������ж������Ĵ��뾭���˼� 
int main(void){
	int x ; 
	x=6;
	for(x=2;x<100;x++)
	{		
		int i;
		int isPrime=1; //x������ 
		for(i=2;i<x;i++){
			if(x%i ==0){
				isPrime = 0 ;
				break;
			}
		//����ע�⣬ѭ���뱻Ƕ�׵�ѭ���У����±���(x,i)Ҫ��ͬ���������	
		}
		if(isPrime ==1){
			printf("%d \n",x);
		}
    }
	printf("\n");
	 
	;return 0 ; 
} 
