#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>

void error_print(const char * ptr_err){
	perror(ptr_err);
	exit(EXIT_FAILURE);
}
int main(void)
{
	int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sockfd == -1)
		error_print("socket");
	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path,"a.sock");
	int res = connect(sockfd, (struct sockaddr *)&addr,sizeof(addr));
	if(res == -1)
		error_print("connect");
	printf("连接成功！\n");

	char * buf = "hello world!";
	res = write(sockfd, buf, strlen(buf));
	if(res == -1)
		error_print("write");
	printf("write size is:%d\tmessage is:%s\n",res,buf);
	
	close(sockfd);
	return 0;
}
