#include <stdio.h>
int main (void)
{
	int n;
	scanf("%d",&n);
	int fact = 1;
	int i = 1 ;
	
	for (i=1;i<=n;i++){
	  // ��ʼ����;ѭ������������;ѭ��ÿһ���������� 
		fact *= i ;
	}
	printf("%d! = %d",n,fact);
	;return 0 ;
}
