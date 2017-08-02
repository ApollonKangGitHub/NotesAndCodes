#include<multithread.h>
#include<server.h>

void sys_err(const char * ptr_err)
{
	perror(ptr_err);
	exit(EXIT_FAILURE);
}

void socket_server_create(const char * ipaddr, const char * port)
{
	struct sockaddr_in seraddr;
	int listenfd, ret;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		sys_err("socket create");
	
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = inet_addr(ipaddr);
	seraddr.sin_port = htons(atoi(port));

	if( (ret = bind(listenfd, (struct sockaddr*)&seraddr, sizeof(seraddr))) < 0)
		sys_err("bind server address");
	
	if((ret = listen(listenfd, BACKLOG_THREAD)) < 0)
		sys_err("listen");

	accept_conn(listenfd);
	close(listenfd);
}

void accept_conn(const int listenfd)
{
	int connfd, i = 0;
	pthread_t tid;
	socklen_t addrlen;
	pthread_attr_t attr;//线程状态信息
	struct thread_info thread[MAX_THREAD_NUM];//存储线程信息，用于函数指针传参
	struct sockaddr_in cliaddr;//客户端信息

	pthread_attr_init(&attr);
	/*设置为分离状态,也可以在线程处理函数中，用pthread_detach()进行分离状态设置，但是效率稍差*/
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	while(1){
		addrlen = sizeof(cliaddr);
again:	
		if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &addrlen)) < 0){
			if(errno == EINTR || errno == ECONNABORTED)	
				goto again;
			else
				sys_err("accept");
		}
		thread[i].connfd = connfd;
		thread[i].cliaddr = cliaddr;
		
		pthread_create(&tid, &attr, deal_conn, (void *)&thread[i]);
		pthread_attr_destroy(&attr);//线程资源使用完后释放资源

		i++;
		if(i == MAX_THREAD_NUM){//超过线程总数限制，服务器主线程结束
			printf("Too many connect!\n");
			pthread_exit((void *)(-1));
		}
	}
}
void * deal_conn(void *arg)
{
	struct thread_info * conn = (struct thread_info *)(arg);//无类型指针转换为自定义客户端信息类型指针
	int ret;
	char recvbuf[BUF_SIZE] = {};//接受缓冲区
	char sendbuf[BUF_SIZE] = {};//回射缓冲区
	char ipaddr[IPADDR_SIZE] = {};
	int port = ntohs((conn->cliaddr).sin_port);//客户端端口
	strcpy(ipaddr, inet_ntoa((conn->cliaddr).sin_addr));//客户端IP地址

	int fd = open("sersock.log", O_RDWR);
	lseek(fd, 0, SEEK_END);
	sprintf(recvbuf, "%s:%d\n", ipaddr, port);
	if( (ret = write(fd, recvbuf, strlen(recvbuf))) <0 )//将客户端登录状态写入日志文件
		sys_err("write sersock.log");
	close(fd);

	printf("%s:%d is connect success!\n", ipaddr, port);
	while(1){
		bzero(recvbuf, strlen(recvbuf));
		bzero(sendbuf, strlen(sendbuf));

		if((ret = read(conn->connfd, recvbuf, sizeof(recvbuf))) == 0){
			printf("The client %s:%d is over!\n", ipaddr, port);
			break;
		}
		sprintf(sendbuf, "Server recv messge:%s", recvbuf);//拼接一部分回射提示信息
		if( (ret = write(conn->connfd, sendbuf, strlen(sendbuf))) < 0)
			sys_err("write");
	}
	close(conn->connfd);
	pthread_exit(NULL);
}
