#include <stdio.h>
int main (void)
{
	// do while ����ѭ����ʱ�򲻻���������������ִ��һ��ѭ������ִ����������˷���
	/*
	do
	{
	   ѭ������� 
	} while (ѭ������);
	
	*/ 
	int x;
	scanf("%d",&x); 
	int n =0;
	do
	{
		x/=10;
		n++;
	}while (x>0);
	printf("%d",n);	
	
	
	
	
	; return 0 ;
 } 
