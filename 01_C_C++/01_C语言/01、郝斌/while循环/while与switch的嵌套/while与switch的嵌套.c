# include <stdio.h>
int main (void)
{
	int i = 0;
	while(i<3)
	{
		switch(i++)//ע��˴�i��ʹ�����Լӡ�����++i�������ᷢ���仯��
		{
		case 0: 
			printf("fat  ");
			//break;
		case 1: 
			printf("hat  ");
			//break;
		case 2: 
			printf("cat  ");
			//break;
		default : 
			printf("Oh no!");
			break;
		}
		//û��break������case i�Ժ����䶼��ִ�С�
		putchar('\n');
	}
	return 0;
}