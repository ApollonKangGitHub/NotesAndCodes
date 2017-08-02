/*
	2016Äê6ÔÂ3ÈÕ00:02:21
*/
# include <stdio.h>
int main (void)
{
	int a[20] = {1,2,7,4,4,2,3,6,4,9,2,8,2,7,3,5,1,2,2,2};
	int key = 2;
	int setkey = 5;
	int i;
	for(i=0; i<20; a[i]=a[i]==key?setkey:a[i],i++);

	for(i=0; i<20; i++)
		printf("%-3d",a[i]);

	return 0;
}
