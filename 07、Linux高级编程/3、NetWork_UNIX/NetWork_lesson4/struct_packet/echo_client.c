/***
 *
 * 局域网一般不会出现粘包问题
 *但是在广域网上必须考虑
 *自定义readn函数与writen函数发送定长包
 *解决TCP的粘包问题
 *Server与Client都需要采用定长包接受发送
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
# define MAX_BUF_LEN 128
	
typedef struct packet{
	int len;
	char buf[MAX_BUF_LEN];
}PACKET;
	
void error_print(char * ptr)
{
		perror(ptr);
		exit(EXIT_FAILURE);
}

ssize_t readn(int fd, void * buf, size_t count)
{
	size_t nleft = count;//剩余的
	ssize_t nread;//已经读取的
	char *buf_read = (char *)buf;

	while(nleft > 0){
		if( (nread = read(fd, buf_read, nleft)) < 0){
			if(errno == EINTR)//被信号中断，不停止，继续处理
				continue;
			return -1;
		}
		else if(nread == 0){
			return count - nleft;//读到EOF也会终止
		}
		buf_read += nread;
		nleft -=nread;
	}
	return count;
}
ssize_t writen(int fd,const  void * buf, size_t count)
{
	size_t nleft = count;//剩余的
	ssize_t nwrite;//已经发送的
	char *buf_write = (char *)buf;

	while(nleft > 0){
		if( (nwrite = write(fd, buf_write, nleft)) < 0){
			if(errno == EINTR)//被信号中断，不停止，继续处理
				continue;
			return -1;
		}
		else if(nwrite == 0){
			continue;
		}
		buf_write += nwrite;
		nleft -= nwrite;
	}
	return count;
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
	int conn;
	if((conn = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		error_print("connect");

	pid_t pid;
	pid = fork();
	if(pid == -1){
		error_print("fork");
	}

	if(pid == 0){
		PACKET recv_buf;
		int n;
		while(1){
			bzero(&recv_buf,sizeof(recv_buf));
			int ret = readn(sockfd, &recv_buf, 4);//先接收包头
			if(ret == -1)
				error_print("readn");
			else if(ret < 4){
				printf("server is close!\n");
				break;
			}
			n = ntohl(recv_buf.len);
			ret = readn(sockfd, recv_buf.buf, n);//再接收数据
			if(ret == -1)
				error_print("readn");
			else if(ret < n){
				printf("server is close!\n");
				break;
			}
			fputs(recv_buf.buf,stdout);
		}
		close(sockfd);
		kill(getppid(),SIGUSR1);//子进程退出时也发送一个信号给父进程
		exit(EXIT_SUCCESS);
	}
	else{
		signal(SIGUSR1,quit_tranmission);
		PACKET send_buf;
		bzero(&send_buf,sizeof(send_buf));
		int n;
		while(fgets(send_buf.buf,sizeof(send_buf.buf), stdin) != NULL){
			n = strlen(send_buf.buf);
			send_buf.len = htonl(n);
			int set = writen(sockfd, &send_buf, n+4);//发送定长包，用sizeof，但是会增加网络负担
			if(set < 0)
				error_print("writen");
			bzero(&send_buf,sizeof(send_buf));
		}
		close(sockfd);
		exit(EXIT_SUCCESS);
	}
	return 0;
}

