#include <stdio.h>

int main ()
{
	int hour1,minute1;
    int hour2,minute2;

printf("�����롰��һ��Сʱ��ʱ�֡���һ����ʮΪ 1 30  "); 
scanf(" %d %d",&hour1,&minute1);
printf("�����롰�ڶ���Сʱ��ʱ�֡���������ʮΪ 3 30  "); 
scanf(" %d %d",&hour2,&minute2);	

int ih=hour2-hour1;
int im=minute2-minute1;

if (im<0){
	im=60+im;
	ih--;
}

printf("ʱ�����%dСʱ%d���ӡ�",ih,im);
	/*if���ı�׼д����
	 
	   if(��������){
	      ... 
	      }             */
	
	;return 0;
}
