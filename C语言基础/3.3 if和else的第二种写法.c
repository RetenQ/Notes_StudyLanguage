#include <stdio.h>

int main()
{
	const double RATE=8.25 ; //const ���εı���ֻ��ֻ����
	const int STANDARD = 40;
	double pay = 0.0 ;
	int hours; //�ȶ��� hours���������û���ֵ�����hours�ĳ�ʼ�� 
	
	printf("�����빤����Сʱ�� �� ");
	scanf ( "%d", &hours); //hours�ĳ�ʼ����� 
	printf("\n");
	
	if(hours>STANDARD)
	  pay=STANDARD*RATE+(hours-STANDARD)*(RATE*1.5);
	
	else
	pay=hours*RATE;
	
	//��ʵ�ϣ����ǽ���ÿ�ζ�������� 
	
	printf("�����ǣ�%f \n",pay);  //ע�������õ���%f 
	
	
	;return 0 ;
 } 
