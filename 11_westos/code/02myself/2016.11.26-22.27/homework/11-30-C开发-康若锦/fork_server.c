# include<sys/socket.h>
# include<netinet/in.h>
# include<arpa/inet.h>
# include<signal.h>
# include<assert.h>
# include<stdio.h>
# include<unistd.h>
# include<string.h>
# include<stdlib.h>
# include<errno.h>

# define BUF_SIZE 1024

void stop_tranmission(int sig)
{
	printf("read a quit signal = %d,tranmission is over\n",sig);
	exit(EXIT_SUCCESS);
}
int main (int argc,char * argv[])
{
	if(argc <= 2){
		printf("usage: %s ip_address port_number\n",
		basename(argv[0]));
		return 1;
	}

	const char * ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port = htons(port);

	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	assert(sockfd >= 0);
	printf("sockfd:%d\n",sockfd);
	int ret = bind(sockfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret != -1);
	ret = listen(sockfd,SOMAXCONN);
	assert(ret != -1);

	struct sockaddr_in client;
	socklen_t client_addrlength = sizeof(client);
	int connfd = accept(sockfd,(struct sockaddr *)&client,&client_addrlength);
	printf("accept:%d\n",connfd);
	
	pid_t pid;
	pid = fork();
	if(pid == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if(pid == 0){
		char buf_send[BUF_SIZE] = {0};
		while(fgets(buf_send,sizeof(buf_send),stdin) != NULL){
			signal(SIGUSR1,stop_tranmission);
			write(connfd,buf_send,strlen(buf_send));
			if(!strcmp(buf_send,"quit\n")){
				printf("tranmission is over!\n");
				break;
			}
			memset(buf_send,0,strlen(buf_send));			
		}
		exit(EXIT_SUCCESS);
	}
	else{
		char buf_recv[BUF_SIZE] = {0};
		while(1){
			memset(buf_recv,0,sizeof(buf_recv));
			int ret = read(connfd,buf_recv, sizeof(buf_recv));
			if(ret == -1){
				perror("read");
				exit(EXIT_FAILURE);
			}
			else if(ret == 0 || !strcmp(buf_recv,"quit\n")){
				printf("tranmission is over");
				kill(getpid(),SIGUSR1);
				break;
			}
			fputs(buf_recv,stdout);
		}
		exit(EXIT_SUCCESS);
	}
	close(connfd);

	close(sockfd);
	return 0;
}
