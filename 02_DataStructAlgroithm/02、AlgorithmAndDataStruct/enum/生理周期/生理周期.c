/*
 *����(p)���ڣ�23��
 *����(e)���ڣ�28��
 *����(i)���ڣ�33��
 *����p��e��i�����ڣ�����d�������һ��p��e��i��ͬһ�������k����d��������
*/
#include <stdio.h>

int main(void)
{
	int p,e,i,d,k;
	printf("Please enter p e i d:\n");
	scanf("%d%d%d%d",&p,&e,&i,&d);

	for(k=d+1; (k-p)%23; k++);//Ѱ����һ�������߷���
	for(; (k-e)%28; k+=23);//Ѱ����һ������������˫�߷�
	for(; (k-i)%33; k+=23*28);//Ѱ����һ�����������̡����̸߷�����ͬһ�������

	printf("next pQ/eQ/iQ at same day to 'set d' distance is:%d\n",k-d);
	return 0;
}