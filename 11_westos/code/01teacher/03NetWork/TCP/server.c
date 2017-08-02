#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define _BACK_LOG_  10

int start_up(const char *ip,unsigned short port)
{
	//int socket(int domain.int type,int protocol)
	int listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock == -1)
	{
		printf("socket error:%d,%s\n",errno,strerror(errno));
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET; //ipv4
	local.sin_port = htons(port);//host->net short
	//int inet_aton(const char* strptr,struct in_addr *addrptr)
	inet_aton(ip ,&local.sin_addr);//char* -> inaddr
	//local.sin_addr.s_addr = htonl(ip);


	//banding a fixed IPadder and port,failed return -1
	if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local)) == -1)
	{	
		printf("bind error:%d,%s\n",errno,strerror(errno));
		exit(1);
	}

	if(listen(listen_sock,_BACK_LOG_) == -1)
	{
		printf("listen error:%d,%s\n",errno,strerror(errno));
		exit(1);
	}

	return listen_sock;
}

void usage(char *proc)
{
	printf("usage : %s Please input IP and port\n",proc);
}

static void wait_child(int signal)
{
	pid_t exit_id;
	while((exit_id = waitpid(-1,NULL,WNOHANG)) > 0)
	{
		printf("one child had exit,pid is %d\n",exit_id);
	}
}

static void* thread_run(void *arg)
{
	printf("create a new thread, thread_id is: %u\n",pthread_self());
	int new_client = (int)arg;
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	while(1)
	{
		//reading from new_client and store to buf
		ssize_t  _size = read(new_client,buf,sizeof(buf) - 1);
		if(_size < 0)
		{
			perror("read");
			break;
		}
		else if(_size == 0)
		{
			printf("client release!\n");
			break;
		}
		else
		{
			buf[_size] = '\0';
			printf("client:-> %s",buf);
		}
	}
	close(new_client);
}

int main(int argc ,char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}
	char *ip = argv[1];
	int port = atoi(argv[2]);

	signal(SIGCHLD,wait_child);

	struct sockaddr_in client_info; //output val
	socklen_t client_len = 0; //output val
	int listen_sock = start_up(ip,port);
	while(1)
	{
		//accept return a new socket,client's ip and port
		int new_client = accept(listen_sock,(struct sockaddr*)&client_info,&client_len);
		if(new_client < 0)
		{
			perror("accept");
			continue;
		}
		printf("connect success\n");
#ifdef _FUN1_
		printf("FUN1 only allow one client connect\n");
		char buf[1024];
		memset(buf,'\0',sizeof(buf));
		while(1)
		{
			//reading from new_client and store to buf
			ssize_t  _size = read(new_client,buf,sizeof(buf) - 1);
			if(_size < 0)
			{
				perror("read");
				break;
			}
			else if(_size == 0)
			{
				printf("client release!\n");
				break;
			}
			else
			{
				buf[_size] = '\0';
				printf("client:-> %s",buf);
			}
		}
		close(new_client);
#endif
#ifdef _FUN2_
	printf("FUN2 multiproces\n");
	pid_t id = fork();
	if(id < 0)
	{//failed
		perror("erron");
	}
	else if(id == 0)
	{//child
		char buf[1024];
		memset(buf,'\0',sizeof(buf));
		while(1)
		{
			//reading from new_client and store to buf
			ssize_t  _size = read(new_client,buf,sizeof(buf) - 1);
			if(_size < 0)
			{
				perror("read");
				break;
			}
			else if(_size == 0)
			{
				printf("client release!\n");
				break;
			}
			else
			{
				buf[_size] = '\0';
				printf("client:-> %s",buf);
			}
		}
		close(new_client);
	}
#endif
#ifdef _FUN3_
	printf("FUN3 Multi-threading\n");
	pthread_t tid;
	pthread_create(&tid,NULL,thread_run,(void*)new_client);
	pthread_detach(tid);
#endif
	}
	close(listen_sock);
	return 0;
}
