#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void error_print(const char * ptr_err){
	perror(ptr_err);
	exit(EXIT_FAILURE);
}
int main(char argc, char ** argv)
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
		error_print("socket");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
//	inet_aton(argv[1],&addr.sin_addr);
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));

	char * buf = "hello world!";
	int res = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));
	if(res == -1)
		error_print("sendto");
	printf("sendto size is:%d\tmessage is:%s\n",res,buf);
	
	close(sockfd);
	return 0;
}
