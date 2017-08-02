#include<stdio.h>
#include<stdlib.h>

int main(int argc, char ** argv, char ** env)
{
	extern char ** environ;
//	printf("env=%p\nenviron=%p\n",env,environ);

	char * path_value = getenv("PATH");
	printf("PATH=%s\n",path_value);

	putenv("KANGRUOJIN=123456789");
	printf("KANGRUOJIN=%s\n",getenv("KANGRUOJIN"));
	putenv("KANGRUOJIN=987654321");
	printf("KANGRUOJIN=%s\n",getenv("KANGRUOJIN"));

	setenv("KANGRUOJIN","ABCDEFG",0);
	printf("KANGRUOJIN=%s\n",getenv("KANGRUOJIN"));
	
	setenv("KANGRUOJIN","GFEDCBA",1);
	printf("KANGRUOJIN=%s\n",getenv("KANGRUOJIN"));
	return 0;
}
