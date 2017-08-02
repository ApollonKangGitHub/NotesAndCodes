/*server.c*/
#include<multiproc.h>
#include<server.h>

void sys_err(const char * ptr_err)
{
    perror(ptr_err);
    exit(EXIT_FAILURE);
}
void socket_server_create(const char * ipaddr, const char * port)
{
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen;
    int confd, ret_bind, ret_listen;
/*创建套接字socket、绑定bind、监听listen、接收accept等基本操作*/
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(ipaddr);
    serveraddr.sin_port = htons(atoi(port));

    if( (ret_bind = bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0)
        sys_err("bind");

    if( (ret_listen = listen(listenfd, BACKLOG_SIZE)) < 0)
        sys_err("listen");

    while(1){//循环监听，以保证多进程可以并发
        addrlen = sizeof(clientaddr);
again:
        if( (confd = accept(listenfd, (struct sockaddr *)&clientaddr, &addrlen)) < 0){
            if ((errno == ECONNABORTED) || (errno == EINTR))//接收到的-1是因为无请求链接
                goto again;
            else
                sys_err("accept");
        }
        fork_create(listenfd, confd, &clientaddr);//对接收到的客户端链接进行处理
    }
    close(listenfd);
}

void fork_create(const int listenfd, const int confd, const struct sockaddr_in * clientaddr)
{
    pid_t pid = fork();
    if(pid < 0)
        sys_err("fork");
    else if(pid > 0)
        close(confd);//父进程关闭上一个接收到的链接的socket秒数符，继续循环accept
    else{
        close(listenfd);//关闭继承过来的无用的文件秒数符
        deal_connect(confd, clientaddr);//子进程处理通信
        close(confd);//推出前关闭文件描述符断开链接
        exit(EXIT_SUCCESS);//子进程结束退出
    }
}
void deal_connect(const int confd, const struct sockaddr_in * clientaddr)
{
    pid_t pid = fork();
    if(pid < 0)
        sys_err("fork");
    else if(pid == 0){//处理读:保存信息到日志文件中
        write_logfile(clientaddr);//写日志
        sleep(10);//模拟其他操作
        /*信息写完后向父进程发送一个SIGCHILD结束信号*/
        kill(SIGCHLD, getppid());
        exit(EXIT_SUCCESS);
    }
    else{//处理写:回射登录状态信息
        int ret_write;
        signal(SIGCHLD, SIG_DFL);//处理子进程结束信号，采用默认处理方式(忽略)，也可以自定义并将wait()写入自定义信号处理中
        if( (ret_write = write(confd, "connect success!\n", 17)) < 0)//连接成功将链接成功的信息回射给客户端
            sys_err("write connect success");
        wait(NULL);//等待回收子进程资源
        if( (ret_write = write(confd, "quit success!\n", 14)) < 0)//wait不再阻塞，表明子进程结束，通信结束，将结束信息会射到客户端
            sys_err("write quit success");
    }
}
/*处理些日志文件的操作*/
void write_logfile(const struct sockaddr_in * clientaddr)
{
    int logfd = open("sersock.log", O_RDWR);//以可读可写的方式打开日志文件
    if(logfd < 0)
        sys_err("open sersock.log");

    char addrbuf[ADDR_PORT_SIZE] = {};
    /*将登录信息写入日志文件*/
    lseek(logfd, 0, SEEK_END);
    sprintf(addrbuf, "%s:%d    ",inet_ntoa(clientaddr->sin_addr), ntohs(clientaddr->sin_port));//将IP地址与端口号拼接到一起
    write(logfd, addrbuf,strlen(addrbuf));//将拼接好的地址信息写入日志文件

    close(logfd);
}
