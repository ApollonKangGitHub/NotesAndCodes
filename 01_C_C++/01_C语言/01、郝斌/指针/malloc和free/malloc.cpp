/*
	2016��3��14��18:31:21
	malloc �� memory(�ڴ�) allocate(����)����д

*/
# include <stdio.h>
# include <malloc.h>  
# include <stdlib.h>
int main(void)
{
	system("color f0");

	int i = 5; //������4���ֽ� ��̬����
	int * p = (int *)malloc(4); //������4���ֽ� ��̬����
	printf("%d,%d\n\n\n",i,*p);//���5�����루pָ�����ڴ������ݣ�

	*p = 10; //*p ����ľ���һ��int������ ֻ����*p������ͱ������ڴ���䷽ʽ��11�е�i�����ķ��䷽ʽ��ͬ
	printf("%d,%d\n\n\n",i,*p);//���5��10

	free(p); //freep(p)��ʾ��p��ָ����ڴ���ͷŵ� 
	p = NULL;//Ϊ�˷�ֹp��ָ���ڴ��ͷź�ϵͳ�����pһ����ַʱ������ȫ������
	printf("%d,%d\n\n\n",i,*p);//���5�����루pָ�����ڴ棬�ڴ����ͷţ�

	return 0;
}
