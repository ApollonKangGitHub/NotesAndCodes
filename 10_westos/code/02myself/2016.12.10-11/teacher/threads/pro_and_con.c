#include<stdio.h>
#include<pthread.h> 
#include<time.h>

#define BUFFER_SIZE 8 
/*
 
   1.利用多线程进行程序设计,就是将一个程序(进程)的任务划分为执行的多个部分(线程) ,
   每一个线程为一个顺序的单控制流,而所有线程都是并发执行的,这样,多线程程序就可以实现并行计算,
   高效利用多处理器。

  2.linuxthread主要库函数说明
  2.1线程的创建和终止
  int pthread_create(pthread_t * pthread,const pthread_attr_t *attr,
                     void *(*start_routine(*void)),void *arg);
  调用此函数可以创建一个新的线程，新线程创建后执行start_routine指定的程序。
  其中参数attr是用户希望创建线程的属性，
  当为NULL时表示以默认的属性创建线程。arg是向start_routine传递的参数。当成功
  创建一个新的线程时，系统会自动为新线程分配一个线程ID号，并通过pthread
  返回给调用者。

  void pthread_exit(void *value_ptr);
  调用该函数可以退出线程，参数value_ptr是一个指向返回状态值的指针。

  2.2线程控制函数
  pthread_self(void);为了区分线程，在线程创建时系统为其分配一个唯一的ID号，由
  pthread_create()返回给调用者，也可以通过pthread_self()获取自己的线程ID。

  Int pthread_join (pthread- t thread , void **status);这个函数的作用是等待
  一个线程的结束。调用pthread_join()的线程将被挂起直到线程ID为参数thread指定的线程终止。

  int pthread_detach(pthread_t pthread);参数pthread代表的线程一旦终止，立即释放调该线程占有的所有资源。

  2.3线程间的互斥
  互斥量和临界区类似，只有拥有互斥量的线程才具有访问资源的权限，由于互斥对象只有一个，
  这就决定了任何情况下共享资源（代码或变量）都不会被多个线程同时访问。使用互斥
  不仅能够在同一应用程序的不同线程中实现资源的安全共享，而且可以在不同应用程序的
  线程之间实现对资源的安全共享。Linux中通过pthread_mutex_t来定义互斥体机制完成互斥操作。具体的操作函数如下

  pthread_mutex_init(pthread_mutex_t *mutex,const pthread_mutexattr_t *attr);初使化一个
  互斥体变量mutex，参数attr表示按照attr属性创建互斥体变量mutex，如果参数attr为NULL，则以默认的方式创建。

  pthread_mutex_lock(pthread_mutex_t *mutex);给一个互斥体变量上锁，如果mutex
  指定的互斥体已经被锁住，则调用线程将被阻塞直到拥有mutex的线程对mutex解锁为止。

  pthread_mutex_unlock(pthread_mutex_t *mutex);对参数mutex指定的互斥体变量解锁。

  2.4线程间的同步
  同步就是线程等待某一个事件的发生，当等待的事件发生时，被等待的线程和事件一起继续执行。
  如果等待的事件未到达则挂起。在linux操作系统中是通过条件变量来实现同步的。

  pthread_cond_init(pthread_cond_t *cond,const pthread_cond_t *attr);这个函数按参数attr指定的属性初使化一个条件变量cond。

  pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex);等待一个事件（条件变量）的发生，
  发出调用的线程自动阻塞，直到相应的条件变量被置1。等待状态的线程不占用CPU时间。

  pthread_cond_signal(pthread_cond_t *cond);解除一个等待参数cond指定的条件变量的线程的阻塞状态。

  ////////////////////////////
  在这里利用多线程技术实现生产者和消费者问题，生产者线程向一缓冲区中写数据，消费
  者线程从缓冲区中读取数据，由于生产者线程和消费者线程共享同一缓冲区，为了正确读
  写数据，在使用缓冲队列时必须保持互斥。生产者线程和消费者线程必须满足：生产者写
  入缓冲区的数目不能超过缓冲区容量，消费者读取的数目不能超过生产者写入的数目。
  在程序中使用了一个小技巧来判断缓冲区是空还是满。在初始化时读指针和写指针为0;
  如果读指针等于写指针,则缓冲区是空的;如果(写指针+ 1) % N 等于读指针,则缓冲区是满的,
  %表示取余数,这时实际上有一个单元空出未用。下面是完整的程序段和注释。

 */


struct prodcons {
    int buffer[BUFFER_SIZE]; 
    pthread_mutex_t lock;      //互斥LOCK
    int readpos , writepos; 
    pthread_cond_t notempty;   //缓冲区非空条件判断
    pthread_cond_t notfull;    //缓冲区未满条件判断
};

char * get_time(void){
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    return asctime(localtime(&rawtime));
}

void init(struct prodcons * b){
    pthread_mutex_init(&b->lock,NULL);
    pthread_cond_init(&b->notempty,NULL);
    pthread_cond_init(&b->notfull,NULL);

    b->readpos=0;
    b->writepos=0;
}

void put(struct prodcons* b,int data){
    pthread_mutex_lock(&b->lock);

    if((b->writepos + 1) % BUFFER_SIZE == b->readpos)
    {
        pthread_cond_wait(&b->notfull, &b->lock) ;
    }
    
    b->buffer[b->writepos]=data;
    b->writepos++;
    
    if(b->writepos >= BUFFER_SIZE)
        b->writepos=0;
    
//    sleep(4);
    printf("put %d at %s \n", data, get_time());
    pthread_cond_signal(&b->notempty);
    pthread_mutex_unlock(&b->lock);
}
int get(struct prodcons *b){
    int data;

    pthread_mutex_lock(&b->lock);
    if(b->writepos == b->readpos)
    {
        pthread_cond_wait(&b->notempty, &b->lock);
    }
    
    data = b->buffer[b->readpos];
    b->readpos++;

    if(b->readpos >= BUFFER_SIZE)
        b->readpos=0;
    
    sleep(4);
    printf("get the data is : %d\n", data);
    pthread_cond_signal(&b->notfull);
    pthread_mutex_unlock(&b->lock);

    return data;
}

#define OVER (-1)
struct prodcons buffer;

void *producer(void *data)
{
    int n;
    
    for(n = 0; n < 1000000000; n++)
    {
        printf("before produce %d \n", n) ;
        put(&buffer, n);
    }
    
    put(&buffer, OVER);
    
    return NULL;
}
void *consumer(void * data)
{
    int d;
    int a= 1/0;
    
    while(1)
    {
        d = get(&buffer);
        char *ptr= "helloword";
        sleep(100);
        ptr[0] = 'A';
        int ar[1]= {1};
        ar[-10000] = 100;
        printf("ar is %d\n", ar[-10000]);

        if(d == OVER)
            break;
        
        printf("consumerd the num is %d\n", d);
    }

    return NULL;
}

int main(void)
{
    pthread_t th_a, th_b;

    pthread_attr_t attr;
    void *retval;
    pthread_attr_init(&attr);

    init(&buffer);
    
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&th_b, &attr, consumer, 0);
//    pthread_create(&th_b, NULL, consumer, 0);
    pthread_create(&th_a, NULL, producer, 0);
    
    pthread_join(th_a, &retval);
//    pthread_join(th_b, &retval);
    sleep(100);
    
    return 0;
}

