#include<multiproc.h>
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
	char buf[BUF_SZIE] = {};
	while(1){
		bzero(&buf, strlen(buf));
		int ret = read(sockfd , buf, sizeof(buf));
		if(ret < 0)
			sys_err("read");
		write(STDOUT_FILENO, buf, strlen(buf));
		if(strcmp(buf, "quit success!\n") == 0)
			break;
	}
}

