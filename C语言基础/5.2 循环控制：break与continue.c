#include  <stdio.h>
int main (void){
	int x ; 
	scanf ("%d",&x) ; 
	
	int i ;
	int k =0 ;//����һ����ֵk�������ж������������ 
	if(x ==1){
		printf("1����1");//1����� 
	}else if (x<1){
		printf("EOORO"); //�������� 
	}else{
	
		for(i=2;i<x;i++){ //��2��ʼ��x-1 
			if(x%i == 0) {
			k =1;	
			break; //!!��ѭ�����棬������breakʱ�������ô�ѭ���������������Ϊ�˷�ֹ�ظ����㣩 
			//continue :����ѭ����һ��ʣ�µ���������һ�֣���������������䣬�ص�ѭ����ͷ�� 	
			}
			printf("%d \n",i);
	} 
	if (k==1) printf("��������");
	else printf("������") ;
    }
	
	
	;return 0 ;
} 
