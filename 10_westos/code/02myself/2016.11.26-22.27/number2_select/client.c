# include<sys/socket.h>
# include<netinet/in.h>
# include<arpa/inet.h>
# include<signal.h>
# include<assert.h>
# include<stdio.h>
# include<unistd.h>
# include<string.h>
# include<stdlib.h>

#define BUF_SIZE 1024

int main (int argc,char * argv[])
{
	if(argc <= 2){
		printf("usage: %s ip_address port_number\n",
		basename(argv[0]));
		return 1;
	}

	const char * ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in server_address;
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family = AF_INET;
	
	inet_pton(AF_INET,ip,&server_address.sin_addr);
	server_address.sin_port = htons(port);

	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	assert(sockfd >= 0);
	printf("sockfd:%d\n",sockfd);
	int connfd = connect(sockfd, (struct sockaddr *)&server_address,sizeof(server_address));	

//	char buffer_recv[BUF_SIZE] = {0};
	char buffer_send[BUF_SIZE] = {0};
	while(1){
		if(connfd < 0){
			printf("connection failed\n");
		}
		else{
			memset(buffer_send,0,BUF_SIZE);
//			memset(buffer_recv,0,BUF_SIZE);
			
			printf("client:");
			fgets(buffer_send,BUF_SIZE,stdin);
			send(sockfd, buffer_send, strlen(buffer_send), 0);
			if(strcmp(buffer_send,"quit\n") == 0){
				printf("Communications is over!\n");
				break;
			}	
/*			
			int ret = recv(sockfd,buffer_recv,BUF_SIZE-1,0);
			if(strcmp(buffer_recv,"quit\n") == 0){
				printf("Communications is over!\n");
				break;
			}
			printf("server:%s",buffer_recv);
*/			
		}
	}	
	close(connfd);
	close(sockfd);

	return 0;
}
