#include <tftpClient.h>
#include <tftpType.h>
#include <tftpSem.h>
#include <tftpSocket.h>
#include <tftpShell.h>
#include <tftpPublic.h>

LOCAL INT32 gClientSockfd = 0;
LOCAL CHAR gSendBuf[__TFTP_SEND_BUG_LEN_] = {0};
LOCAL CHAR gRecvBuf[__TFTP_RECV_BUF_LEN_] = {0};

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
	struct sockaddr_in seraddr;
	INT32 sendLen = 0;
	INT32 recvLen = 0;
	INT32 ret = 0;
	
	/* 初始化服务器地址等信息 */

	/* 客户端socket创建 */
	memset(&seraddr, 0, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(__TFTP_CLIENT_DEFAULT_SOCKET_UDP_PORT_);
	seraddr.sin_addr.s_addr = __TFTP_CLIENT_DEFAULT_IP_ADDR_;
	gClientSockfd = tftp_socket_create(&seraddr);	

	/* 发送请求到服务器 */
	sendLen = 0;
	ret = tftp_socket_send(gClientSockfd, gSendBuf, sendLen, &seraddr);
}

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
										"__UINT32__{128/256/512/1024/2048/4096 Bytes, default is 512}");
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


