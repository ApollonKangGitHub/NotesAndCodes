# include <stdio.h>
# include <sys/timeb.h>

int main (void)
{

	struct timeb t1,t2;
	int i = 1;
	int t;

	/*int i�����*/
	ftime(&t1);
	while(i>0)
		i += 1;/*�˳�ѭ��ʱ��i����Сֵ*/
	ftime(&t2);

	printf("i = %d\n",i);
	t = (t2.time-t1.time)*1000+(t2.millitm-t1.millitm); /* ����ʱ��� */
    printf("��ʱ%ld����\n",t);

	printf("i = %#X\n",i);
	printf("\n");

	return 0;
}
