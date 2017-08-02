/*gcc dl_function.c -l dl测试*/
# include<stdio.h>
# include<dlfcn.h>
# include<stdlib.h>

int main(void)
{
	void * handle = dlopen("./libadd.so",RTLD_NOW);

	char * error = dlerror();
	if(error != NULL){
		perror("dlopen");
		exit(EXIT_FAILURE);
	}
	int (*add)(int,int);/*dlsym返回函数指针*/

	add = dlsym(handle, "add");
	
	int sum = add(2,54);
	printf("sum = %d\n",sum);
	
	dlclose(handle);
	return 0;
}
