# include<stdio.h>
int test(int a,char *ps)
{
	printf("a:%d\n",a);
	printf("ps:%s\n",ps);
	return 200;
}
int callback(int ca,char * ps,int(*pt)(int,char *))
{
	printf("hello callback\n");
	return pt(ca,ps);
}

