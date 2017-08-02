# include<stdio.h>
# include<sys/types.h>
# include<netinet/in.h>
# include<sys/socket.h>
# include<arpa/inet.h>
# include<assert.h>
# include<unistd.h>
# include<errno.h>
# include<string.h>
# include<fcdtl.h>
# include<stdlib.h>
# include<sys/epoll.h>
# include<pthread.h>

# define MAX_EVENT_NUMBER 1024
# define BUFFER_SIZE 10

/*将文件描述符设置成为非阻塞的*/
int setnoblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

/*将文件描述符fd上的EPOLLIN注册到*/
int main (int argc, char **argv)
{

	
}
