# include<stdio.h>

int test (char *ps)
{
/*
 *不可以传递ps++,因为后加传递不了变化的值，传过去再变化就没用了
 * */
/*
 	if(*ps == '\0')
		return 0;
	else
		test(++ps);//++ps传过去，ps就成了++ps=ps+1
	printf("%c",*(ps-1));
*/
	if(*ps == '\0')
		return 0;
	else
		test(ps+1);//ps+1传过去，ps不是ps+1
	printf("%c",*ps);
}
int main(void)
{
	char * str = "hello";

	test(str);
	return 0;
}
