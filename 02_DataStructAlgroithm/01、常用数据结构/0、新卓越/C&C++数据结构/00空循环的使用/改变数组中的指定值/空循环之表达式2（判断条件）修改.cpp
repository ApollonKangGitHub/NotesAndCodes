/*
	2016年6月2日23:31:40
	目的：某数组中某元素，若等于key（key可以随意设定）则将该元素换成setkey（也可以随意设定）
*/
# include <stdio.h>
int main (void)
{
	int a[20] = {1,2,5,4,4,2,3,6,4,9,2,8,2,7,3,5,1,2,2,2};
	int key = 2;
	int setkey = 0;//将2全部换成0
	int i;
	for(i=0; i<20 && (a[i] != key || (a[i] = setkey) || 1); i++);
	for(i=0; i<20; i++)
		printf("%-3d",a[i]);

	return 0;
}
