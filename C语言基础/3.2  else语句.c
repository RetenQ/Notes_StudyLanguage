#include <stdio.h>
int main()
{

int price=0;
int bill =0;

printf("�������� ");
scanf("%d",&price); 
printf("������Ʊ�� ");
scanf("%d",&bill); 

if(bill>=price)     //ע���ˣ�if��else�ķֺ�;��д��С���ź��棬��Ϊ�ⲻ�������������������ĵط� 
{
	printf("Ӧ�������� %d \n", bill-price);
}

/*���ж�����������Ϊ0ʱ����ִ�д������ڵ���䣬����ִ��else��䡣
if+else�ж���֮��֮�������ճ����� */
 
else {
	printf("���Ǯ����  \n"); 
}

printf("ִ�н���"); 

; return 0 ;
}
