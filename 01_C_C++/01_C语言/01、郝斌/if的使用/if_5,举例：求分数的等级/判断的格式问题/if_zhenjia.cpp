# include <stdio.h>

int main (void)
{
	float score;

	printf("please input your score :\n");
	scanf("%f",&score);
	
	int i = (90 <= score <=100);//�жϽ��Ϊ�߼�ֵ
	printf("%d\n",i);

	return 0;
}
/*
��score���ڵ���90ʱ����߳���Ϊ�棬�ұ߲�ִ�У�
	������Ϊ�棨1��
��scoreС��90ʱ�����Ϊ�٣��ұ�ִ��scoreС��100����Ϊ�棬
	������Ϊ�棨1��


���Խ���������Ϊ��
*/