#include <stdio.h>
int main()
{
	int a,b,c;
	printf("��������������") ;
	scanf("%d %d %d",&a,&b,&c) ;	
	int max=0;
    //��if���������������ʱ��ִ�е���������һ��if����һ��if-else��䣬�����Ƕ�׵�if��� 
	if(a>b)	{
		if(a>c){
			max=a;
		}
		
		else {
			max=c;
		}
		
		}
		
		
	else{
			if(b>c){
				max=b;
			}
		else{
		max=c;
		}
	}
	// !!! �����else���Ǻ������if��ƥ�䣡��������ģ��д����ţ��Ǹ��ݴ����ŵĻ��ֵķ�Χƥ��ģ�
	//�������Ƿϻ���������ʽ�����ܰ�ʾelse��ƥ��	
		
	//������ô�����ֻ��˵��ע��{}�Ķ�Ӧ��fuck
	
	//����Ҳ�����ü�Ҫ���ifelseд����൫���з��� 
	printf("The max is %d \n",max);
	; return 0 ;
}
