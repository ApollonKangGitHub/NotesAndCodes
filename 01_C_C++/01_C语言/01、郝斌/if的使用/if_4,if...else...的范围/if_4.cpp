#include <stdio.h>

int main (void)
{
	int delta;
	printf("please input delta:\n");
	scanf("%d",&delta);

	if (delta > 0)
		printf("��������\n");
	//printf("������\n");
	else if(delta == 0)
		printf("��һ����\n");
	else
		printf("�޽�!\n");
	return 0;
}
/*
	�����
	printf("������\n");
	��䣬�����������
	��Ϊ��һ��elseû��ƥ���if
	ֻ�轫��һ��elseɾ����������������󣬵��ǳ������н���ǲ��Ե�

	���ԣ���õĸķ��ǽ�
	printf("��������\n");
	printf("������\n");
	������{}������
*/