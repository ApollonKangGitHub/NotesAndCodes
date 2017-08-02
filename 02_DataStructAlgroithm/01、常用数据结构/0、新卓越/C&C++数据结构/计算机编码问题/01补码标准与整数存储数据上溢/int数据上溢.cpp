# include <stdio.h>
# include <sys/timeb.h>

int main (void)
{

	struct timeb t1,t2;
	int i = 1;
	int t;

	/*int i的溢出*/
	ftime(&t1);
	while(i>0)
		i += 1;/*退出循环时，i是最小值*/
	ftime(&t2);

	printf("i = %d\n",i);
	t = (t2.time-t1.time)*1000+(t2.millitm-t1.millitm); /* 计算时间差 */
    printf("用时%ld毫秒\n",t);

	printf("i = %#X\n",i);
	printf("\n");

	return 0;
}
