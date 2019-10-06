/*
 * File: tftpSocket.h
 * Function: 
 *     tftp客户端、服务器公共基础模块部分
 *     用于处理服务器、客户端socket创建、数据传输等功能
 * Time: 2019-10-6 11:09:20
 * Statement: 
 *     本程序仅可作学习交流之用，可在学习为目的的基础上任意传播
 *     未经授权不可以任何形式商用，凡是有通过非免费手段获取到该代码
 *     均可邮件联系，已达到净化学习交流环境的目的
 * Author: Kangruojin
 * Mail: mailbox_krj@163.com
 * CSDN: Apollon_krj
 * GITHUB: ApollonKangGitHub
 *
 */

#ifndef __TFTP_SOCKET_H_
#define __TFTP_SOCKET_H_

#include <tftpType.h>
#include <tftpPublic.h>

#define TFTP_SOCKET_BACKLOG_THREAD 	(5)
#define __TFTP_SERVER_IP_ 			"192.168.10.99"

#define __TFTP_SOCKET_SERVER_UDP_PORT_			(69)
#define __TFTP_SOCKET_SERVER_IP_ANY_ADDR_		(INADDR_ANY)
#define __TFTP_SOCKET_CLIENT_IP_ANY_ADDR_		(INADDR_ANY)

#define __TFTP_SERVER_TASK_POOL_UDP_PORT_START_	(4321)
#define __TFTP_SERVER_TASK_POOL_UDP_PORT_RAND_	(1000)
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

EXTERN tftpReturnValue_t tftp_socket_send
(
	INT32 sockfd, 
	CHAR * buf, 
	INT32 sendLen, 
	struct sockaddr_in * peerAddr,
	INT32 times,			/* 超时次数 */
	INT32 timeout,			/* 超时重传时间 */
	BOOL reTrans
);

#endif
