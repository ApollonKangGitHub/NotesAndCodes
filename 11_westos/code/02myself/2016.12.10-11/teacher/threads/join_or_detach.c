#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 4

void *BusyWork(void *t)
{
    int i;
    long tid;
    double result=0.0;
    tid = (long)t;
    printf("Thread %ld starting...\n",tid);
    for (i=0; i<1000000; i++)
    {
        result = result + i;
    }
    printf("Thread %ld done. Result = %e\n",tid, result);
    pthread_exit((void*) t);
    return(NULL);
}

int main (int argc, char *argv[])
{
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    long t;
    void *status;

    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    /*
       定义线程变量，属性对象变量和一些常见变量。属性对象变量可以根据自己的需求来设置，
       从而通过属性对象来设置线程的属性，在这里主要是设置线程的结合和分离属性。

       对属性对象变量进行初始化，并设置属性对象是结合的PTHREAD_CREATE_JOINABLE，
       第二个参数除了结合，还有分离，即PTHREAD_CREATE_DETACHED。
       本程序创建的线程都是结合，假如同学们要创建结合的，只需要改变第二个参数就可以了。
       另外，创建分离的线程，除了使用属性对象外，还可以直接使用pthread_detach(pthread_t tid)函数。

    */

    for(t=0; t<NUM_THREADS; t++) {
        printf("Main: creating thread %ld\n", t);
        rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t); 
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    for(t=0; t<NUM_THREADS; t++) {
        rc = pthread_join(thread[t], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
    }

    printf("Main: program completed. Exiting.\n");
    pthread_exit(NULL);
}
