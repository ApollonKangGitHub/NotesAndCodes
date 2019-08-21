#ifndef __TFTP_SOCKET_H_
#define __TFTP_SOCKET_H_

#include <tftpType.h>
#include <tftpPublic.h>

EXTERN INT32 tftp_socket_create(struct sockaddr_in * addr);

#endif