#include <tftpSocket.h>
#include <tftpType.h>
#include <tftpLog.h>

#include <tftpPublic.h>

/*
 * FunctionName:
 *     tftp_socket_create
 * Description:
 *     创建通信用的UDP套接字，并绑定端口
 * Notes:
 *     
 */
EXTERN INT32 tftp_socket_create
(
	struct sockaddr_in * addr
)
{
	INT32 ret = 0;
	socklen_t len = 0;

	if (NULL == addr) {
		TFTP_LOGERR("Error parameter addr = %p", addr);
		return -1;
	}

	INT32 sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		TFTP_LOGERR("create socket fail, errno = %d!", errno);
		tftp_perror("create fail reason is");
		return -1;
	}

	len = sizeof(struct sockaddr_in);

	/* 绑定sockfd套接字和指定端口 */
	ret = bind(sockfd, (struct sockaddr *)addr, len);
	if (ret < 0) {
		TFTP_LOGERR("bind socket fd fail, sockfd = %d, port = %u, errno = %d", \
			sockfd, ntohs(addr->sin_port), errno);
		tftp_perror("bind fail reason is");
		close(sockfd);
		return -1;
	}
	
	return sockfd;
}

/*
 * FunctionName:
 *     tftp_socket_listen
 * Description:
 *     监听TCP套接字，tftp用不到
 * Notes:
 *     
 */
EXTERN INT32 tftp_socket_listen(INT32 listenfd)
{
	INT32 ret = 0;
	ret = listen(listenfd, TFTP_SOCKET_BACKLOG_THREAD);
	if (ret < 0) {
		TFTP_LOGERR("listen fd = %d fail, backlog = %d, errno = %d", \
			listenfd, TFTP_SOCKET_BACKLOG_THREAD, errno);
		tftp_perror("listen fail reason is");
		return -1;
	}
	return 0;
}

/*
 * FunctionName:
 *     tftp_socket_accept
 * Description:
 *     接收TCP连接请求，tftp用不到
 * Notes:
 *     
 */
EXTERN INT32 tftp_socket_accept(INT32 listenfd, struct sockaddr_in * cliaddr)
{
	INT32 connfd = -1;
	socklen_t addrlen;

	if (NULL == cliaddr) {
		TFTP_LOGERR("invalid cliaddr, cliaddr = %p, errno = %d", cliaddr, errno);
		return -1;
	}
	
	addrlen = sizeof(struct sockaddr_in);	
	again:
	connfd = accept(listenfd, (struct sockaddr *)cliaddr, &addrlen);
	if (connfd < 0) {
		if(errno == EINTR || errno == ECONNABORTED) {
			usleep(1000);
			goto again;
		}
        	
		TFTP_LOGERR("accept listen fd fail, listenfd = %d, errno = %d", listenfd, errno);
		tftp_perror("accept fail reason is");
		return -1;
	}

	return connfd;
}

/*
 * FunctionName:
 *     tftp_socket_recv
 * Description:
 *     接收UDP数据
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_socket_recv
(
	INT32 sockfd, 
	CHAR * buf, 
	INT32 bufLen, 
	struct sockaddr_in * client
) 
{
	INT32 ret = 0;
	socklen_t sockLen = 0;

	if (NULL == buf) {
		return tftp_ret_Null;
	}

	sockLen = sizeof(struct sockaddr_in);
	ret = recvfrom(sockfd, buf, (size_t)bufLen, 0, (struct sockaddr *)client, &sockLen);
	if (ret < 0) {
		TFTP_LOGERR("recv data from fd fail, sockfd = %d, errno = %d", sockfd, errno);
		tftp_perror("recv fail reason is");
		return -1;
	}
}

 
