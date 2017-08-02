#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
#include<signal.h>
#define MAX 100

int sockfd;

void closefd(int sig){
	printf("时间服务器关闭!\n");
	sleep(1);
	close(sockfd);
	exit(EXIT_SUCCESS);
}
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
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
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
	signal(SIGINT,closefd);
	while(1){
		struct sockaddr_in from;
		socklen_t len = sizeof(from);
		res = recvfrom(sockfd, buf, MAX, 0, (struct sockaddr *)&from, &len);
		printf("客户端%s连接成功\n",inet_ntoa(from.sin_addr));
		memset(buf, 0, strlen(buf));
		time_t cur = time(NULL);
		struct tm * cu = localtime(&cur);
		sprintf(buf,"%4d-%02d-%02d %02d:%01d:%02d",cu->tm_year+1900, cu->tm_mon+1, cu->tm_mday, cu->tm_hour, cu->tm_min, cu->tm_sec);
		sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&from, len);
	}	
	return 0;
}
