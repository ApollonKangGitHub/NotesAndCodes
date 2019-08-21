#include <tftpSocket.h>
#include <tftpType.h>
#include <tftpLog.h>

#include <tftpPublic.h>

EXTERN INT32 tftp_socket_create
(
	struct sockaddr_in * addr
)
{
	INT32 ret = 0;
	socklen_t len = 0;

	if (NULL == addr) {
		TFTP_LOGERR("Error parameter addr:%p", addr);
		return -1;
	}

	INT32 sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		TFTP_LOGERR("create socket fail!");
		tftp_perror("create fail reason is");
		return -1;
	}

	len = sizeof(struct sockaddr_in);

	/* 绑定sockfd套接字和指定端口 */
	ret = bind(sockfd, (struct sockaddr *)addr, len);
	if (ret < 0) {
		TFTP_LOGERR("bind socket fd fail, sockfd=%d, port=%u", sockfd, ntohs(addr->sin_port));
		tftp_perror("bind fail reason is");
		close(sockfd);
		return -1;
	}
	
	return sockfd;
}

 
