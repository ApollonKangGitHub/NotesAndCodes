#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAX 100
void error_print(const char * ptr_err){
	perror(ptr_err);
	exit(EXIT_FAILURE);
}
int main(char argc,char **argv)
{
	if(argc <= 2){
		printf("Two few parameter\n");
		exit(EXIT_FAILURE);
	}
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
		error_print("socket");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
//	inet_aton(argv[1],&addr.sin_addr);/*与inet_addr函数效果一样*/
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));
	int res = bind(sockfd, (struct sockaddr *)&addr,sizeof(addr));
	if(res == -1)
		error_print("bind");
	printf("绑定成功！\n");

	char buf[MAX] = {};
	res = read(sockfd, buf, MAX);
	if(res == -1)
		error_print("read");
	printf("read size is:%d\tmessage is:%s\n",res,buf);
	
	close(sockfd);
	return 0;
}
