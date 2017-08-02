/*
	2016年6月3日00:02:59
	目的：某数组中某元素，若等于key（key可以随意设定）则将该元素换成setkey（也可以随意设定）
*/
# include <stdio.h>
int main (void)
{
	int a[20] = {1,2,5,4,4,2,3,6,4,9,2,8,2,7,3,5,1,2,2,2};
	int key = 2;
	int setkey = 5;//将2全部换成5
	int i;
	for(i=0; i<20; i++)
	{
		if(a[i] == key)
			a[i] = setkey;
	}
	for(i=0; i<20; i++)
		printf("%-3d",a[i]);

	return 0;
}
