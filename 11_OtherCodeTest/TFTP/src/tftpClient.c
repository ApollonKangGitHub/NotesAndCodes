#include <tftpClient.h>
#include <tftpType.h>
#include <tftpSem.h>
#include <tftpSocket.h>
#include <tftpLog.h>
#include <tftpShell.h>

#include <tftpPublic.h>

LOCAL INT32 gClientSockfd = 0;
LOCAL CHAR gSendBuf[__TFTP_SEND_BUG_LEN_] = {"Hello server, I love you!"};
LOCAL CHAR gRecvBuf[__TFTP_RECV_BUF_LEN_] = {0};
struct sockaddr_in gSeraddr;
struct sockaddr_in gCliaddr;

/*
 * FunctionName:
 *     tftp_client_socket_init
 * Description:
 *     客户端通信socket初始化
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_client_socket_init(CONST CHAR * ipaddr)
{
	/* 初始化服务器地址等信息 */
	memset(&gSeraddr, 0, sizeof(gSeraddr));
	gSeraddr.sin_family = AF_INET;
	gSeraddr.sin_port = htons(__TFTP_SOCKET_SERVER_UDP_PORT_);
	gSeraddr.sin_addr.s_addr = inet_addr(ipaddr);

	/* 客户端socket创建 */
	gClientSockfd = tftp_socket_create(&gCliaddr, FALSE);	
	
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_client_cmd_handle
 * Description:
 *     tftpclient下载/上传命令
 * Notes:
 *     
 */
LOCAL VOID tftp_client_cmd_handle(INT32 argc, CHAR * argv[])
{
	tftp_print("\r\ntftp client start!!!");
	INT32 sendLen = 0;
	INT32 recvLen = 0;
	INT32 ret = 0;

	CHAR * operatr = argv[2];
	CHAR * ipaddr = argv[3];
	CHAR * filename = argv[5];
	CHAR * blksize = argv[7];
	CHAR * timeout = argv[9];

	TFTP_LOGDBG(tftp_dbgSwitch_client, \
		"operator:%s, ipaddr:%s, filename:%s, blksize:%d, timeout:%d", \
			operatr, ipaddr, filename, blksize, timeout);
	
	/* 客户端socket初始化和服务器socket结构初始化 */
	tftp_client_socket_init(ipaddr);

	/* 参数获取与判断 */

	/* 请求报文封装 */
	
	/* 发送请求到服务器 */
	sendLen = strlen(gSendBuf);
	ret = tftp_socket_send(gClientSockfd, gSendBuf, sendLen, &gSeraddr);
	while(TRUE){
		sleep(100);
	}
}

/*
 * FunctionName:
 *     tftp_client_command_init
 * Description:
 *     客户端命令注册
 * Notes:
 *     
 */
LOCAL VOID tftp_client_command_init(VOID)
{
	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_client_cmd_handle, 
		__TFTP_CMD_NORMAL_ | __TFTP_CMD_DYN_,
			"tftpclient{tftp server enable/disable}"
				"__STRING__{upload(put) or download(get)}"
					"serverip{server ip address}"
						"__IPADDR__{ip address(eg:192.168.1.100)}"
							"file{file name for get/put}"
								"__STRING__{string of file name without path}"
									"blocksize{translation blockszie(Bytes) everytimes}"
										"__UINT32__{128/256/512/1024/2048/4096 Bytes, default is 512}"
											"timeout{DATA/ACK timeout second}"
												"__UINT32__{default is 15 s}");
}

/*
 * FunctionName:
 *     tftp_client_module_init
 * Description:
 *     client模块初始化接口
 * Notes:
 *     
 */
EXTERN tftpReturnValue_t tftp_client_module_init(VOID)
{
	/* 注册客户端相关操作命令 */
	tftp_client_command_init();

	/* 打开配置文件，获取客户端下载/上传的文件路径 */
}


