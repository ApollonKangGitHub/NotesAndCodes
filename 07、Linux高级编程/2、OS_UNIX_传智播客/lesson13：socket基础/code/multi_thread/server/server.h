#ifndef _SERVER_H_
#define _SERVER_H_

#include<multithread.h>
#include<pthread.h>
#include<fcntl.h>
#include<errno.h>

#define BACKLOG_THREAD 32
#define MAX_THREAD_NUM 256
#define IPADDR_SIZE 15

struct thread_info{
	struct sockaddr_in cliaddr;
	int connfd;
};

void socket_server_create(const char *, const char *);
void accept_conn(const int);
void * deal_conn(void *);

#endif
