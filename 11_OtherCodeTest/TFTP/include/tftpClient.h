/*
 * File: tftpClient.h
 * Function: 
 *     tftp客户端相关代码
 *     用于注册、处理客户端上传、下载的命令行输入
 *     进行文件的上传和下载
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

#ifndef __TFTP_CLIENT_H__
#define __TFTP_CLIENT_H__

#include <tftpType.h>
#include <tftpPack.h>
#include <tftpPublic.h>

typedef struct tftpClientInfo_s {
	struct sockaddr_in _serAddr;
	struct sockaddr_in _cliAddr;
	CHAR _filePath[__TFTP_FILE_PATH_LEN_];
	CHAR _clientPath[__TFTP_FILE_PATH_LEN_];
	INT32 _socketFd;
	INT32 _fileFd;
	tftpPacktReq_t _reqPack;
}tftpClientInfo_t;

EXTERN tftpReturnValue_t tftp_client_module_init(VOID);

#endif /* __TFTP_CLIENT_H__ */
