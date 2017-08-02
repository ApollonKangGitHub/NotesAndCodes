# include<sys/socket.h>
# include<netinet/in.h>
# include<arpa/inet.h>
# include<signal.h>
# include<assert.h>
# include<stdio.h>
# include<unistd.h>
# include<string.h>
# include<stdlib.h>

#define MAX_SEND_SIZE 1024

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
	printf("sock:%d\n",sockfd);
	if(connect(sockfd, (struct sockaddr *)&server_address,sizeof(server_address)) < 0){
		printf("connection failed\n");
	}
	else{
		char normal_data[MAX_SEND_SIZE];
		
		while(1){
			memset(normal_data,0,MAX_SEND_SIZE);
			printf("server:");
			fgets(normal_data,MAX_SEND_SIZE,stdin);
			send(sockfd, normal_data, strlen(normal_data), 0);
		}
	}
	close(sockfd);
	return 0;
}
