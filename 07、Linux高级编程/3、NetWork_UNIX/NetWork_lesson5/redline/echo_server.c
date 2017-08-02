/***
 *
 * 用封装的redline函数实现粘包的处理
 *
 * */
# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include<unistd.h>
# include<sys/socket.h>
# include<arpa/inet.h>
# include<netinet/in.h>
# include<signal.h>
# include<errno.h>
# include<netdb.h>
# define MAX_BUF_LEN 128

void error_print(char * ptr)
{
		perror(ptr);
		exit(EXIT_FAILURE);
}

ssize_t readn(int fd, void * buf, size_t count)
{
	size_t nleft = count;//剩余的
	ssize_t nread;//已经读取的
	char *bufp = (char *)buf;

	while(nleft > 0){
		if( (nread = read(fd, bufp, nleft)) < 0){
			if(errno == EINTR)//被信号中断，不停止，继续处理
				continue;
			return -1;
		}
		else if(nread == 0){
			return count - nleft;//读到EOF也会终止
		}
		bufp += nread;
		nleft -=nread;
	}
	return count;
}
ssize_t writen(int fd,const  void * buf, size_t count)
{
	size_t nleft = count;//剩余的
	ssize_t nwrite;//已经发送的
	char *bufp = (char *)buf;

	while(nleft > 0){
		if( (nwrite = write(fd, bufp, nleft)) < 0){
			if(errno == EINTR)//被信号中断，不停止，继续处理
				continue;
			return -1;
		}
		else if(nwrite == 0){
			continue;
		}
		bufp += nwrite;
		nleft -= nwrite;
	}
	return count;
}
ssize_t recv_peek(int sockfd, void * buf, size_t len)
{
	while(1){
		int ret = recv(sockfd, buf, len, MSG_PEEK);
		if(ret == -1 || errno == EINTR)
			continue;
		return ret;
	}
}
ssize_t readline(int sockfd, void * buf, size_t maxline)
{
	int ret;
	int nread;
	int nleft = maxline;
	char * buf_readline = buf;

	while(1){
		int ret = recv_peek(sockfd, buf_readline, nleft);
		if(ret <= 0)
			return ret;
		nread = ret;
		int i;
		for(i = 0; i < nread; i++){
			if(buf_readline[i] == '\n'){
				ret = readn(sockfd, buf_readline, i+1);
				if(ret != i+1)
					exit(EXIT_FAILURE); 
				return ret;
			}
		}
		if(nread > nleft)
			exit(EXIT_FAILURE);
		nleft -= nread;
		ret = readn(sockfd, buf_readline, nread);
		if(ret != nread)
			exit(EXIT_FAILURE);

		buf_readline += nread;
	}
	return -1;
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

	pid = fork();
	if(pid == -1){
		error_print("fork");
	}
	if(pid == 0){
		signal(SIGUSR1,quit_tranmission);
		char send_buf[MAX_BUF_LEN]={0};
		while(fgets(send_buf, sizeof(send_buf), stdin) != NULL){
			writen(conn,send_buf,sizeof(send_buf));
			bzero(send_buf,strlen(send_buf));
		}
		exit(EXIT_SUCCESS);
	}
	else{
		char recv_buf[MAX_BUF_LEN]={0};
		while(1){
			bzero(recv_buf,strlen(recv_buf));
			int ret = readline(conn, recv_buf, sizeof(recv_buf));
			if(ret < 0)
				error_print("read");
			else if(ret == 0){
				printf("client is close!\n");
				break;
			}
			fputs(recv_buf,stdout);
		}
		kill(pid,SIGUSR1);//父进程退出循环，表示通信结束，应该给子进程发送一个信号告知，子进程也结束
		exit(EXIT_SUCCESS);
	}
	return 0;
}

