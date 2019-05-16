# include<stdio.h>
int test(int a,char *ps);
int callback(int ca,char * ps,int(*pt)(int,char *));

 main(void) {
       printf("hello main\n");
       int ret = callback(100,"hello test",test);
       printf("ret:%d\n",ret);
       return 0;
}

