#include <stdio.h>
void swap(); //ԭ������

int main(void){
	int a = 5 ; 
	int b = 6 ; 
	
	//ԭ��������ʱ������û��ָ�����������������波�Դ�������int
	swap(a,b); //����ʵ�ϣ����ǵĺ����������double���д�����˽����������������������ģ�
	printf("a = %d , b = %d \n",a,b);
	
	
	;return 0 ; 
}

//ע�����������double
void swap (double a , double b){
	int t = a ; 
	printf("IN SWAP,a = %f , b = %f  \n",a,b);
	a = b ; 
	
	b = t ; 
}

/*  ����
	1.
	void f(void) ��ʾf����û�в���
	void f()      ��ʾf�����Ĳ�����δ֪����ͳC�� 
	
	2.
	������Բ���������������ţ��������������
	f(a,b) ����a,b
	f((a,b))  ����(a,b)����ʱ����Ҫ����(a,b)����a,b����˶��Żᱻ�����������ʹ��
	
	3.C���Բ������ں������涨�庯��

*/
