#include <tftpLog.h>
#include <tftpType.h>
#include <tftpShell.h>
#include <tftpServer.h>
#include <tftpClient.h>
#include <tftpPublic.h>

BOOL initSucces = FALSE;

CHAR * tftp_err_code_msg[tftp_ret_Max + 1] = {
	"OK",
	"ERROR ",
	"INVALID PARAMETER",
	"NOT FOUND",
	"NOT SUPPORT",
	"NULL MEMORY",
	"ALREADY EXIST",
	"OTHER"
};

INT32 main(void)
{
	tftp_log_module_init();
	tftp_sem_module_init();
	tftp_task_module_init();
	tftp_shell_module_init();
	tftp_server_module_init();
	tftp_client_module_init();

	/* 初始化完成 */
	initSucces = TRUE;
	while(TRUE){
		sleep(1000);
	}
	return 0;
}
