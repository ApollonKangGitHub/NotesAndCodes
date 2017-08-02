/*************************************************************************
	> File Name: ser.c
	> Author: 
	> Mail: 
	> Created Time: 一 11/21 10:06:35 2016
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>


#define IP "127.0.0.1"
#define PORT 9999
#define MAXLINE 1024
#define SIZE 3


typedef struct server_context_st
{
    int cli_cnt; /*客户端个数*/
    int clifds[SIZE]; /**/
    fd_set allfds;
    int maxfd;
}server_context_st;


static server_context_st* s_srv_ctx=NULL;



/*=============================================================*/

static int create_server_proc(const char*ip,int port)
{
    int fd;
    struct sockaddr_in servaddr;
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd==-1)
    {
        perror("socket\n");
        exit(2);
    }

    int yes=1;
    //设置通用套接字,允许本地地址重用
    if( ( setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) )
        return -1;

    int reuse =1;
    if( ( setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int)) == -1) )
        return -1;

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family =AF_INET;
    inet_pton(AF_INET,ip,&servaddr.sin_addr);
    servaddr.sin_port = htons(port);

    if(bind(fd,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1)
    {
        perror("bind");
        return -1;
    }

    listen(fd,5);//backlog

    return fd;
}

static void accpet_client_proc(int srvfd)
{
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen =sizeof(cliaddr);
    int clifd=-1;

    printf("accept clint proc is called\n");
ACCEPT:
    clifd = accept(srvfd,(struct sockaddr*)&cliaddr,&cliaddrlen);

    if(clifd == -1)
    {
        if(errno == EINTR)
        {
            goto ACCEPT;
        }
        else
        {
            perror("accpet");
            exit(3);
        }
    }
    fprintf(stdout,"accpet a new client: %s:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);

    //将新的链接描述符添加进数组
    int i=0;
    for(i=0;i<SIZE;++i)
    {
        if(s_srv_ctx->clifds[i]<0)
        {
            s_srv_ctx->clifds[i]=clifd;
            s_srv_ctx->cli_cnt++;
            break;
        }
    }

    if(i==SIZE)
    {
        perror("too many clients\n");
        return;
    }
}

static int handle_client_msg(int fd,char* buf)
{
    printf("recv buf is: %s\n",buf);

    write(fd,buf,strlen(buf)+1);
    return 0;
}

static void recv_client_msg(fd_set* readfds)
{
    int i=0,n=0;
    int clifd;
    char buf[MAXLINE]={0};

    for(i=0;i<=s_srv_ctx->cli_cnt;++i)
    {
        clifd=s_srv_ctx->clifds[i];
        if(clifd<0)
            continue;
    

        if(FD_ISSET(clifd,readfds))
        {
            n=read(clifd,buf,MAXLINE);
            if(n<=0)
            {
                FD_CLR(clifd,&s_srv_ctx->allfds);
                close(clifd);
                s_srv_ctx->clifds[i]=-1;
                continue;
            }
    
            handle_client_msg(clifd,buf);
        }
    }
}

static void handle_client_proc(int srvfd)
{
    int clifd=-1;
    int retval=0;
    fd_set* readfds = &s_srv_ctx->allfds;
    struct timeval tv;
    int i=0;

    while(1)
    {
        FD_ZERO(readfds);
        FD_SET(srvfd,readfds);
        s_srv_ctx->maxfd= srvfd;
        

        for( i=0;i<s_srv_ctx->cli_cnt;++i)
        {
            clifd=s_srv_ctx->clifds[i];
            FD_SET(clifd,readfds);
            s_srv_ctx->maxfd = (clifd > s_srv_ctx->maxfd ? clifd:s_srv_ctx->maxfd);
        }
            retval = select(s_srv_ctx->maxfd+1,readfds,NULL,NULL,&tv);

            if(retval==-1)
            {
                perror("select\n");
                return ;
            }
            if(retval == 0)
            {
                perror("timeout\n");
                continue;
            }

            if(FD_ISSET(srvfd,readfds))
                accpet_client_proc(srvfd);
            else
                recv_client_msg(readfds);
    }
}

static int server_init()
{
    s_srv_ctx=(server_context_st*) malloc(sizeof(server_context_st));
    if(s_srv_ctx==NULL)
        return -1;

    int i=0;
    for(;i<SIZE;++i)
        s_srv_ctx->clifds[i]=-1;
    return 0;
}

int main(int argc,char* argv[])
{
    int srvfd;
    if (server_init()<0 ) return -1;

    srvfd=create_server_proc(IP,PORT);
    if(srvfd < 0)
    {
        perror("socket create or bind fail\n");
        exit(1);
    }

    handle_client_proc(srvfd);
    return 0;
}
