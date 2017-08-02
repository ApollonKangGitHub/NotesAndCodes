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
	int conn;
	if((conn = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		error_print("connect");

	pid_t pid;
	pid = fork();
	if(pid == -1){
		error_print("fork");
	}

	if(pid == 0){
		char recv_buf[MAX_BUF_LEN] = {0};
		while(1){
			bzero(recv_buf,sizeof(recv_buf));
			int ret = read(sockfd, recv_buf, sizeof(recv_buf));
			if(ret == -1)
				error_print("read");
			else if(ret == 0){
				printf("server is close!\n");
				break;
			}
			fputs(recv_buf,stdout);
		}
		close(sockfd);
		kill(getppid(),SIGUSR1);//子进程退出时也发送一个信号给父进程
		exit(EXIT_SUCCESS);
	}
	else{
		signal(SIGUSR1,quit_tranmission);
		char send_buf[MAX_BUF_LEN] = {0};
		while(fgets(send_buf,sizeof(send_buf), stdin) != NULL){
			int set = write(sockfd, send_buf, strlen(send_buf));
			if(set < 0)
				error_print("write");
			bzero(send_buf,strlen(send_buf));
		}
		close(sockfd);
//		exit(EXIT_SUCCESS);
	}
	return 0;
}

