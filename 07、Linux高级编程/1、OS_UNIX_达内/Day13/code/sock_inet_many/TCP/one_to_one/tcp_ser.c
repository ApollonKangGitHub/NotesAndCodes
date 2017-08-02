#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define QUE_MAXLEN 	20
#define BUF_MAXLEN 		100
void error_print(const char * ptr_err){
	perror(ptr_err);
	exit(EXIT_FAILURE);
}
int main(char argc, char ** argv)
{
	if(argc <= 2){
		printf("Too few parameter!\n");
		exit(EXIT_FAILURE);
	}

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
		error_print("socket");
	struct sockaddr_in ser_addr;
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
	ser_addr.sin_port = htons(atoi(argv[2]));

	int res = bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
	if(res == -1)
		error_print("bind");
	printf("bind ok!\n");
	listen(sockfd, QUE_MAXLEN);

	struct sockaddr_in cli_addr;
	socklen_t len = sizeof(cli_addr);
	int clifd = accept(sockfd, (struct sockaddr *)&cli_addr, &len);
	char * buf_ipaddr = inet_ntoa(cli_addr.sin_addr);
	printf("%s连接成功!\n",buf_ipaddr);
	
	char buf_read[BUF_MAXLEN] = {};
	res = read(clifd, buf_read, BUF_MAXLEN);
	if(res == -1)
		error_print("read");
	printf("接收了%d字节,内容为：%s\n",res,buf_read);
	char buf_write[BUF_MAXLEN] = "message is get!";
	res = write(clifd,buf_write,strlen(buf_write));
	if(res == -1)
		error_print("write");
	printf("发送成功，发送内容为:%s\n",buf_write);
	close(clifd);
	close(sockfd);
	return 0;
}
