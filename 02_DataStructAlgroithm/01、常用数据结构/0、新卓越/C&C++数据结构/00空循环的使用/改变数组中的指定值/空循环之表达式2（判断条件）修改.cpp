/*
	2016��6��2��23:31:40
	Ŀ�ģ�ĳ������ĳԪ�أ�������key��key���������趨���򽫸�Ԫ�ػ���setkey��Ҳ���������趨��
*/
# include <stdio.h>
int main (void)
{
	int a[20] = {1,2,5,4,4,2,3,6,4,9,2,8,2,7,3,5,1,2,2,2};
	int key = 2;
	int setkey = 0;//��2ȫ������0
	int i;
	for(i=0; i<20 && (a[i] != key || (a[i] = setkey) || 1); i++);
	for(i=0; i<20; i++)
		printf("%-3d",a[i]);

	return 0;
}
