#include <unistd.h>
#include <stdio.h>


int i;
int g_tag = 10;
int lock = 0;
int *p2 = &g_tag;
int **ptr = &p2;
int main(){
	pid_t pid, pid1;
	int tag = 10;
	//printf("main test.......\n");
	int *p1 = &g_tag;
	char *argv[] = {"/bin/ls", 0};
	printf("father  getpid=%d\n", getpid());
	//pid1 = fork();
	pid = fork();
	if(pid==0)
	{
		printf("getpid=%d, getppid=%d\n", getpid(), getppid());
		tag = 100;
		g_tag = 100;
	//	sleep(1000);
		printf("child pid=%d, tag=%d, g_tag=%d\n", getpid(), tag, g_tag);
		printf("&g_tag=%p, &tag=%p\n", &g_tag, &tag);
		//sleep(5);
		ptr = &p1;
		int *p2 = &tag;
		ptr = &p2;
		//printf("p1=%p,*ptr=%p\n", p1, *ptr);
		//execv(argv[0], argv);
		if(lock == 0)
		{
			for(i=0;i<30;i++)
			{

				g_tag = i;
				printf("i=%d\n",g_tag);
			}
			lock = 1;
		}
		//_exit(0);
	}
	if(pid==0)
	{
		printf("getpid1=%d, getppid1=%d\n", getpid(), getppid());
	}
	else {
		//sleep(30);
		printf("father pid=%d, tag=%d, g_tag=%d\n", getpid(), tag, g_tag);
		//printf("main end............\n");
		//printf("&g_tag=%p, &tag=%p\n", &g_tag, &tag);
		//printf("father p1=%p,*ptr=%p\n", p1, *ptr);
		//_exit(0);
	}
	//return 0;
	//printf("father p1=%p,*ptr=%p\n", p1, *ptr);
//	wait(NULL);
}
