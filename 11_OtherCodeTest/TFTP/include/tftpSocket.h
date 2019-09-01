#ifndef __TFTP_SOCKET_H_
#define __TFTP_SOCKET_H_

#include <tftpType.h>
#include <tftpPublic.h>

#define TFTP_SOCKET_BACKLOG_THREAD 	(5)
#define __TFTP_RECV_BUF_LEN_ 		(8092)
#define __TFTP_SEND_BUG_LEN_		(8092)


#define __TFTP_SOCKET_SERVER_UDP_PORT_		(69)
#define __TFTP_SCKET_SERVER_IP_ADDR_		(INADDR_ANY)

EXTERN INT32 tftp_socket_create(struct sockaddr_in * addr, BOOL needBind);
EXTERN INT32 tftp_socket_listen(INT32 listenfd);
EXTERN INT32 tftp_socket_connect(INT32 sockfd, struct sockaddr_in * seraddr);
EXTERN INT32 tftp_socket_accept(INT32 listenfd, struct sockaddr_in * cliaddr);

EXTERN INT32 tftp_socket_recv
(
	INT32 sockfd, 
	CHAR * buf, 
	INT32 bufLen, 
	struct sockaddr_in * client
);

EXTERN INT32 tftp_socket_send
(
	INT32 sockfd, 
	CHAR * buf, 
	INT32 bufLen, 
	struct sockaddr_in * seraddr
);
#endif
