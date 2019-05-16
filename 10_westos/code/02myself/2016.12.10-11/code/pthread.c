# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<wait.h>
# include<pthread.h>

pthread_mutex_t mutex;

/*子线程运行的函数，首先获得互斥锁，然后暂停5s，再释放该互斥锁*/
void * another(void * arg)
{
	printf("int child thread, lock the mutex\n");
	pthread_mutex_lock(&mutex);
	sleep(5);
	pthread_mutex_unlock(&mutex);
}

int main(void)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_t id;
	pthread_create(&id, NULL, another, NULL);
#if 0
	/*父进程中的主线程暂停1s，已确保在执行fork操作之前，子线程已经开始运行并且获得了互斥变量mutex*/
	sleep(1);
	int pid = fork();
	if(pid < 0){
		pthread_join(id, NULL);
		pthread_mutex_destory(&mutex);
		return 1;
	}
	else if(pid == 0){
		pritnf("I am in the child,want to get the lock\n");
		/*子线程从父线程继承了互斥锁mutex的状态，该互斥锁处于锁住的状态,这是由父进程中的子线程执行pthread_mutex_lock引起的，因此，下面这句加锁操作会一直阻塞，*/

	}
#endif
	return 0;
}
