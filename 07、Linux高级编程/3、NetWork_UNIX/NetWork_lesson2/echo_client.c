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

	char recv_buf[MAX_BUF_LEN] = {0};
	char send_buf[MAX_BUF_LEN] = {0};
	while(fgets(send_buf,sizeof(send_buf), stdin) != "quit\n"){
		int set = write(sockfd, send_buf, strlen(send_buf));
		if(set < 0)
			error_print("write");
		int ret = read(sockfd, recv_buf, sizeof(recv_buf));
		if(ret < 0)
			error_print("read");
		fputs(recv_buf,stdout);
		bzero(recv_buf,sizeof(recv_buf));
		bzero(send_buf,sizeof(send_buf));
	}

	close(sockfd);
	return 0;
}

