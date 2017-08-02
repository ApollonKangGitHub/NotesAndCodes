#include<multithread.h>
#include<client.h>

void sys_err(const char * ptr_err)
{
	perror(ptr_err);
	exit(EXIT_FAILURE);
}
void socket_client_create(const char * ipaddr, const char * port)
{
	struct sockaddr_in serveraddr;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(ipaddr);
	serveraddr.sin_port = htons(atoi(port));

	int ret = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if(ret < 0)
		sys_err("connect");
	
	deal_connect(sockfd);

	close(sockfd);
}

void deal_connect(const int sockfd)
{
	char sendbuf[BUF_SIZE] = {};
	char recvbuf[BUF_SIZE] = {};
	int ret;
	while( fgets(sendbuf, sizeof(sendbuf), stdin) ){
		if((ret = write(sockfd, sendbuf, strlen(sendbuf))) < 0)
			sys_err("write sockfd");
		if((ret = read(sockfd, recvbuf, sizeof(recvbuf))) < 0)
			sys_err("read");
		if((ret = write(STDOUT_FILENO, recvbuf, ret)) < 0)
			sys_err("write stdout");
		bzero(sendbuf, strlen(sendbuf));
		bzero(recvbuf, strlen(recvbuf));
	}
}

