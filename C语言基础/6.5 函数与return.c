#include <stdio.h> ��
//��ʹ��void���͵ĺ���ʱ��������û�з���ֵ�ģ�Ҳ���ǿ���û��return 
int max (int a,int b)
{//����ֵ��int���͵ĺ���max 
	int ret ; 
	if(a>b){
		ret = a ; 
	}else {
		ret = b ; 
	}
	return ret ; //����һ��ret����ֵ��������һ��������������ж��return��䣬����return��һ��Ҫ��β�������ⲻ�ǵ�һ���ڣ�ϰ�߲��ã� 
}

int main () {
/* return 
1.return ��ֹͣ���������У����ҷ���һ��ֵ
2.д��  return <ֵ> ;  ����  return[���ʽ] ;
 
*/
int a,b,c ; 
c = max(12,10);
printf("%d \n ",c);


return 0 ; 
}

