#include <stdio.h>
int main(){
	//дһ�����򣬼���ƽ�������������ƽ���������� 
	
	int x ;
	double sum = 0;
	int cnt = 0 ;
	int number [100]; //����һ�����飬���СΪ100�� 
	//int ����A [��СX] ��ʾ�������A���������Է� X��int    
	
	scanf("%d",&x);
	while (x! = -1){
		number [cnt] = x ;  //��������cntλ�õ��Ǹ���Ԫ=x ����cnt�ǵ����ģ�����x�ֱ����1��2��3....λ���ϴ�� 
		//�������е�Ԫ�ؽ��и�ֵ
		 
		sum += x ;
		cnt ++;
		scanf ("%d",&x);
	} 
	if (cnt > 0 ){
		printf("%f \n",sum/cnt);
		int i ;
		for (i = 0 ; i<cnt;i++){  //�����������ֵ��������������
		//��������:����������� 
		 
			if (number[i]>sum/cnt){//ʹ�������е�Ԫ�� 
				printf("%d \n",number[i]);
				//������iλ�õ������������������ 
			}
			
		} 
	}
	
	;return 0 ;
}
