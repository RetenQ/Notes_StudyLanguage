#include <stdio.h>
int main (void){
	int type;
	scanf("%d",&type);
	 
	switch( type ){
		//����switch(���Ʊ��ʽ��)�����Ʊ��ʽֻ���������͵Ľ���� 
		//�����е�ֵ�ж�����������䣬�����п����Ǳ�����������ʽ�ӡ��������Ͼ����default�� 
		case 1: 
			printf("����case 1");
			break ; 
		/*
		case ���� ��           �����������ǳ�����Ҳ������ֻ����������ı��ʽ�� 
		    ���......��һ����break��β�� 
		*/	
		case 2:
			printf("����case 2");
			break ; 
		case 3:
			printf("����case 3");
			//break ; ע�����break��ע��ɾ���ˣ�case=3ʱ��ִ��3Ȼ��ִ��case4��ֹͣ�� 
		case 4:
			printf("����case 4");
			break ; 
	
	default:
		printf("���⣬�ⲻ��case1234");
		//�����default��β����Ӧ��������� 
			}
	
	;return 0 ;
}

/*  caseֻ��һ��·�꣬�������Զ�ֹͣ�����������е���һ��case����ȥִ�о��ӣ��������˳��
    ���������ֱ������һ��break���ߵ���switch�������Ż�ֹͣ������ 
 */
