# include <stdio.h>
# include <malloc.h>

int main (void)
{
	while (1)
	{
		int *p = (int *)malloc(1000);//���������־�����������������Խ�������ٶ�Խ��

		//free(p);//�ɽ�p��ָ���ڴ��ͷţ��Դ˴ﵽ�����ò�����Ŀ��
	}
	return 0;
}