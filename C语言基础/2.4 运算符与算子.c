#include <stdio.h>

int main()
{
// �������ָ��������ĵĶ���������ӷ�������� +������=Ҳ������� 
//������ָ���������ֵ�������ǳ�����������һ�������ķ���ֵ 

int hour1,minute1;
int hour2,minute2;

printf("�����롰��һ��Сʱ��ʱ�֡���һ����ʮΪ 1 30  "); 
scanf(" %d %d",&hour1,&minute1);
printf("�����롰�ڶ���Сʱ��ʱ�֡���������ʮΪ 3 30  "); 
scanf(" %d %d",&hour2,&minute2);
	
int time1=hour1*60+minute1;
int time2=hour2*60+minute2;
int t=time2-time1;
printf("ʱ�����%dСʱ%d���ӡ�",t/60,t%60);

    
	;return 0 ;
	
	
 } 
