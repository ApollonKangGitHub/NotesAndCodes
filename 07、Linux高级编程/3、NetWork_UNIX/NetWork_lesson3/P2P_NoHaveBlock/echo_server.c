# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include<unistd.h>
# include<sys/socket.h>
# include<arpa/inet.h>
# include<netinet/in.h>
# include<signal.h>

# define MAX_BUF_LEN 128

void error_print(char * ptr)
{
		perror(ptr);
		exit(EXIT_FAILURE);
}

void quit_tranmission(int sig)
{
	printf("recv a quit signal = %d\n",sig);
	exit(EXIT_SUCCESS);
}
int main(void)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error_print("socket");
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = 1234;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	/*inet_aton("127.0.0.1",&servaddr.sin_addr);*/

	/*不必等待TIME_WAIT状态结束便可重启服务器*/
	int on = 1;
	if( setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)) < 0)
		error_print("setsockopt");
	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		error_print("bind");
	if(listen(sockfd, SOMAXCONN) < 0)
		error_print("listen");
	
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	int conn;
	if((conn = accept(sockfd,(struct sockaddr*)&peeraddr,&peerlen)) < 0)
		error_print("accept");
	pid_t pid;
/*
	socklen_t servlen = sizeof(servaddr);
	getsockname(conn,(struct sockaddr*)&servaddr,&servlen);
	getpeername(conn,(struct sockaddr*)&peeraddr,&peerlen);
	printf("server_port = %d,  client_port = %d\n",servaddr.sin_port,peeraddr.sin_port);
*/
	pid = fork();
	if(pid == -1){
		error_print("fork");
	}
	if(pid == 0){
		signal(SIGUSR1,quit_tranmission);
		char send_buf[MAX_BUF_LEN]={0};
		while(fgets(send_buf, sizeof(send_buf), stdin) != NULL){
			write(conn,send_buf,strlen(send_buf));
			bzero(send_buf,strlen(send_buf));
		}
		exit(EXIT_SUCCESS);
	}
	else{
		char recv_buf[MAX_BUF_LEN]={0};
		while(1){
			bzero(recv_buf,strlen(recv_buf));
			int ret = read(conn, recv_buf, sizeof(recv_buf));
			if(ret < 0)
				error_print("read");
			else if(ret == 0){
				printf("client is close!\n");
				break;
			}
			fputs(recv_buf,stdout);
		}
		kill(pid,SIGUSR1);//父进程退出循环，表示通信结束，应该给子进程发送一个信号告知，子进程也结束
	//	exit(EXIT_SUCCESS);
	}
	return 0;
}

