#include <tftpClient.h>
#include <tftpType.h>
#include <tftpSem.h>
#include <tftpSocket.h>
#include <tftpShell.h>
#include <tftpPublic.h>


/*
 * FunctionName:
 *     tftp_cmd_client_handle
 * Description:
 *     tftpserver启动/关闭的命令执行函数
 * Notes:
 *     
 */
LOCAL VOID tftp_cmd_client_handle(INT32 argc, CHAR * argv[])
{
	tftp_print("\r\ntftp client start!!!");
}

LOCAL VOID tftp_client_command_init(VOID )
{
	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_cmd_client_handle, 
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


