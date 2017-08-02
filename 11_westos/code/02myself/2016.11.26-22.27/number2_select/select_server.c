# include<sys/types.h>
# include<sys/socket.h>
# include<netinet/in.h>
# include<arpa/inet.h>
# include<assert.h>
# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<string.h>
# include<errno.h>
# include<fcntl.h>

# define MAX_BUF_LEN 1024
int main(int argc, char **argv)
{
	if(argc <= 2){
		printf("usage:%s ip_address ip_address port_number\n",basename(argv[0]));
		return 1;
	}

	const char * ip = argv[1];
	const int port = atoi(argv[2]);

	int ret = 1;
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	int listenfd = socket(PF_INET, SOCK_STREAM, 0);
	assert(listenfd != -1);
	ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
	assert(ret != -1);
	ret = listen(listenfd,5);//SOMAXCONN
	assert(ret != -1);

	struct sockaddr_in client_address;
	socklen_t client_addrlength = sizeof(client_address);

	int connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlength);

	if(connfd < 0){
		printf("errno is: %d\n",errno);
		close(listenfd);
	}

	char buf[MAX_BUF_LEN];
	fd_set read_fds;//定义标准输出描述符变量(正常)
	fd_set exception_fds;//定义标准错误描述符变量（异常）
	FD_ZERO(&read_fds);//初始化清空
	FD_ZERO(&exception_fds);//初始化清空

	while(1){
		memset(buf, '\0', sizeof(buf));
		
		FD_SET(connfd, &read_fds);//设置
		FD_SET(connfd, &exception_fds);//设置

		ret = select(connfd+1, &read_fds, NULL, &exception_fds,NULL);
		if(ret < 0){
			printf("selection failure\n");
			break;
		}

		/*对于可读事件，采用普通的recv函数读取数据*/
		if(FD_ISSET(connfd, &read_fds)){
			ret = recv(connfd, buf, sizeof(buf)-1, 0);
			if(ret <= 0){
				break;
			}
			printf("get %d bytes of normal data: %s\n",ret,buf);
		}	
		/*对于异常事件，采用MSG_OOB标志的recv函数读取带外数据*/
		else if(FD_ISSET(connfd, &exception_fds)){
			ret = recv(connfd, buf, sizeof(buf)-1, MSG_OOB);
			if(ret <= 0){
				break;
			}
			printf("get %d bytes of oob data: %s\n",ret, buf);
		}
	}

	close(connfd);
	close(listenfd);

	return 0;
}
