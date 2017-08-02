# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include<unistd.h>
# include<sys/socket.h>
# include<arpa/inet.h>
# include<netinet/in.h>

# define MAX_BUF_LEN 128

void error_print(char * ptr)
{
		perror(ptr);
		exit(EXIT_FAILURE);
}
void do_tranmission(int conn)
{
	char recv_buf[MAX_BUF_LEN];
		while(1){
			bzero(recv_buf,sizeof(recv_buf));
	
			int ret = read(conn, recv_buf, sizeof(recv_buf));
			if(ret < 0)
				error_print("read");
			if(ret == 0){
				printf("pid = %d client child proccess is over or close\n",getpid());
				break;//客户端Ctrl+C结束通信时退出循环
			}
			fputs(recv_buf,stdout);
	
			int set = write(conn, recv_buf, ret);
			if(set < 0)
				error_print("write");
		}

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
	pid_t pid;

	while(1){
		if((conn = accept(sockfd,(struct sockaddr*)&peeraddr,&peerlen)) < 0)
			error_print("accept");
		printf("ip = %s\tport = %d\n",inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

		pid = fork();
		if(pid == -1)
			error_print("fork");
		if(pid == 0){
				printf("tranmission of new child pid = %d\n",getpid());
				close(sockfd);//子进程不需要处理监听，只处理父进程接受到的连接进行通信
			do_tranmission(conn);
			exit(EXIT_SUCCESS);//do_tranmission结束时通信结束，为该客户端开辟的子进程也应该被销毁
		}
		else
			close(conn);//父进程处理新建连接，要关闭原有接受到的conn，并且父子进程共享套接口
	}
	return 0;
}

