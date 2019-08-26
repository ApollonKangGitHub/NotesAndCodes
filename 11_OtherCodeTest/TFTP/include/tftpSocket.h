#ifndef __TFTP_SOCKET_H_
#define __TFTP_SOCKET_H_

#include <tftpType.h>
#include <tftpPublic.h>

#define TFTP_SOCKET_BACKLOG_THREAD 5

EXTERN INT32 tftp_socket_create(struct sockaddr_in * addr);
EXTERN INT32 tftp_socket_listen(INT32 listenfd);
EXTERN INT32 tftp_socket_accept(INT32 listenfd, struct sockaddr_in * cliaddr);

#endif