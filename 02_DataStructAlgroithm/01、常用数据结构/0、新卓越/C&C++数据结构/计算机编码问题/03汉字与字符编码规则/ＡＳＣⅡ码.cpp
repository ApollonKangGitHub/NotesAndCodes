# include <stdio.h>
int main (void)
{
	int asc = 0;
	int n = 0;
	for(asc; asc < 128; asc++)
	{
		if(asc < 7 || asc > 13)//����7-14�ģ��ӣâ��Ӧ���ַ�������ȷ��ʾ��������������
		{
			n++;
			if(0 == (n-1)%5) 
				printf("\n");
			printf("�ַ�%c��ASC��ֵΪ%d\t",asc,asc);
		}
	}

	printf("%\n");
	return 0;
}