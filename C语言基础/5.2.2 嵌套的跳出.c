#include <stdio.h>
int main()
{
	int x ;
	int one,two,five;
	
	//scanf("%d",&x);
	x = 2;

    int exit = 0 ;//����һ����������ȷ��break������ ������break��������break�� 
	
	for ( one=1;one<x*10/1;one++){
		
		for(two=1;two<x*10/2;two++){
			
			for(five=1;five<x*10/5;five++){
				if(one+two*2+five*5 == x*10){
					printf("������%d��1�Ǽ�%d��2�Ǽ�%d��5�ǵõ� %d Ԫ\n",one,two,five,x);
					exit = 1;
					break; 
					//goto out ; //goto���÷���β 
				}
			}	
			if(exit) break ; //ֱ��дexit�ͱ�ʾexit ==1 ; 
		}
	if(exit) break;
	}
	//break��continue ֻ��������ڵ�ѭ����  
	
	//out �� 
	;return 0 ;
	/*
	   goto A ;��������ת��A�� 
	 A :         A����ע�������ð��  
	
	*/ 
 } 
