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
	struct sockaddr_in * addr,
	BOOL needBind
)
{
	INT32 ret = 0;
	BOOL bAddrReuse  = TRUE;
	BOOL bPortReuse = TRUE;
	socklen_t addrLen = 0;

	if (NULL == addr) {
		TFTP_LOGERR("Error parameter addr = %p", addr);
		return -1;
	}

	INT32 sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		TFTP_LOGERR("create socket fail, errno = %d!", errno);
		tftp_perror("\r\ncreate fail reason is");
		return -1;
	}

	/* 给socket设置SO_REUSEADDR属性,设定套接字地址复用 */
	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &bAddrReuse, sizeof(bAddrReuse));
	if (ret < 0) {
		TFTP_LOGERR("set socket option optname %d fail, errno = %d", SO_REUSEADDR, errno);
		tftp_perror("\r\nset socket option SO_REUSEADDR fail reason is");
		tftp_close(sockfd);
		return -1;
	}

	if (!needBind) {
		return sockfd;
	}
	
	/* 设置SO_REUSEPORT属性，实现端口复用 */
	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &bPortReuse, sizeof(bPortReuse));
	if (ret < 0) {
		TFTP_LOGERR("set socket option optname %d fail, errno = %d", SO_REUSEPORT, errno);
		tftp_perror("\r\nset socket option SO_REUSEPORT fail reason is");
		tftp_close(sockfd);
		return -1;
	}

	/* 绑定sockfd套接字和指定端口 */
	addrLen = sizeof(struct sockaddr_in);
	ret = bind(sockfd, (struct sockaddr *)addr, addrLen);
	if (ret < 0) {
		TFTP_LOGERR("bind socket fd fail, sockfd = %d, port = %u, errno = %d", \
			sockfd, ntohs(addr->sin_port), errno);
		tftp_perror("\r\nbind fail reason is");
		tftp_close(sockfd);
		return -1;
	}
	
	return sockfd;
}

/*
 * FunctionName:
 *     tftp_socket_recv
 * Description:
 *     接收UDP数据
 * Notes:
 *     
 */
EXTERN INT32 tftp_socket_recv
(
	INT32 sockfd, 
	CHAR * buf, 
	INT32 bufLen, 
	struct sockaddr_in * client
) 
{
	INT32 ret = 0;
	socklen_t addrLen = 0;

	if (NULL == buf) {
		return -1;
	}

	addrLen = sizeof(struct sockaddr_in);
	ret = recvfrom(sockfd, buf, (size_t)bufLen, 0, (struct sockaddr *)client, &addrLen);
	if (ret < 0) {
		TFTP_LOGERR("recv data from sockfd fail, sockfd = %d, errno = %d", sockfd, errno);
		tftp_perror("\r\nrecv fail reason is");
		return -1;
	}
	return ret;
}

/*
 * FunctionName:
 *     tftp_socket_send
 * Description:
 *     发送UDP数据
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_socket_send
(
	INT32 sockfd, 
	CHAR * buf, 
	INT32 sendLen, 
	struct sockaddr_in * peerAddr,
	INT32 times,			/* 超时次数 */
	INT32 timeout,			/* 超时重传时间 */
	BOOL reTrans			/* 是否重传，FALSE为不重传 */
) 
{
	socklen_t addrLen = 0;
	INT32 times_alreay = 0;
	INT32 ret = 0;
	fd_set rdfds;
	struct timeval tv;

	if (NULL == buf || NULL == peerAddr) {
		return -1;
	}
	
timeout_send:
	addrLen = sizeof(struct sockaddr_in);
	ret = sendto(sockfd, buf, sendLen, 0, (struct sockaddr *)peerAddr, addrLen);
	if (ret < 0) {
		TFTP_LOGERR("send data to sockfd fail, sockfd = %d, errno = %d", sockfd, errno);
		tftp_perror("\r\nsend fail reason is");
		return tftp_ret_Error;
	}

	if (!reTrans) {
		return tftp_ret_Ok;
	}
	
	times_alreay++;

	/* 超超时重传次数大于最大值，则结束传输 */
	if (times_alreay > times) {
		TFTP_LOGERR("send data to sockfd wait recv timeout, sockfd = %d, times = %d, timeout = %d, times_alreay = %d", \
			sockfd, times, timeout, times_alreay);
		return tftp_ret_Error;
	}
	else {
		/* 设置监听描述符集，为指定socket fd */
		FD_ZERO(&rdfds);
		FD_SET(sockfd, &rdfds);

		/* 设置超时时间 */
		tv.tv_sec = timeout;
		tv.tv_usec = 0;

		/* 超时等待 */
		ret = select(sockfd + 1, &rdfds, NULL, NULL, &tv);
		if (ret < 0) {
			TFTP_LOGERR("select for sockfd fail, sockfd = %d, errno = %d", sockfd, errno);
			tftp_perror("\r\nselect fail reason is");
			return tftp_ret_Error;
		}
		else if (0 == ret) {
			goto timeout_send;
		}
		else if (FD_ISSET(sockfd, &rdfds)){
			return tftp_ret_Ok;
		}
	}
	
	return tftp_ret_Ok;
}

#define __TFTP_SOCKET_UDP_ 	(1)
#define __TFTP_SOCKET_TCP_	(!__TFTP_SOCKET_UDP_)
#if __TFTP_SOCKET_TCP_
/*
 * FunctionName:
 *     tftp_socket_connect
 * Description:
 *     TCP客户端连接服务器，tftp用不到
 * Notes:
 *     
 */
EXTERN INT32 tftp_socket_connect
(
	INT32 sockfd, 
	struct sockaddr_in * seraddr
)
{
	INT32 ret = 0;
	socklen_t addrLen = sizeof(struct sockaddr_in);

	ret = connect(sockfd, (struct sockaddr *)seraddr, addrLen);
	if (ret < 0) {
		TFTP_LOGERR("connect to server fd = %d fail, errno = %d", sockfd, errno);
		tftp_perror("\r\nconnect fail reason is");
		return -1;
	}
	return ret;
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
		tftp_perror("\r\nlisten fail reason is");
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
		tftp_perror("\r\naccept fail reason is");
		return -1;
	}

	return connfd;
}
#endif /* __TFTP_SOCKET_TCP_ */

 
