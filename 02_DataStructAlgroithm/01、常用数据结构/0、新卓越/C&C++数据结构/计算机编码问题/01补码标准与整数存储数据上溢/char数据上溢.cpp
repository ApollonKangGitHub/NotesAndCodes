# include <stdio.h>
# define TEMP 20

int main (void)
{

	int distance = 1;

	/*char ��������distance��ch��ʼֵ�������ؾ�������distance��ͬ�������ݲ�ͬ*/
	while(distance < TEMP)
	{
		char ch = 'a';
		while(ch > 0)   ch += distance;
		printf("ch = %d\t",ch);
		printf("ch = %#X\n",ch);

		distance ++;
	}

	return 0;
}
