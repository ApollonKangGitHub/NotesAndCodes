#include <tftpLog.h>
#include <tftpType.h>
#include <tftpShell.h>
#include <tftpServer.h>
#include <tftpPublic.h>

CHAR * tftp_err_code_msg[tftp_ret_Max + 1] = {
	"OK",
	"ERROR ",
	"INVALID PARAMETER",
	"NOT FOUND",
	"NOT SUPPORT",
	"NULL MEMORY",
	"OTHER"
};

INT32 main(void)
{
	tftp_log_module_init();
	tftp_sem_module_init();
	/* 调试相关模块时打开对应debug开关 */
	#if 0
	tftp_log_debug_control(tftp_dbgSwitch_task, __TFTP_DBG_ON_);
	tftp_log_debug_control(tftp_dbgSwitch_shell, __TFTP_DBG_ON_);
	tftp_log_debug_control(tftp_dbgSwitch_server, __TFTP_DBG_ON_);
	tftp_log_debug_control(tftp_dbgSwitch_client, __TFTP_DBG_ON_);
	tftp_log_debug_control(tftp_dbgSwitch_sem, __TFTP_DBG_ON_);
	tftp_log_debug_control(tftp_dbgSwitch_send, __TFTP_DBG_ON_);
	tftp_log_debug_control(tftp_dbgSwitch_recv, __TFTP_DBG_ON_);
	tftp_log_debug_control(tftp_dbgSwitch_other, __TFTP_DBG_ON_);
	#endif
	tftp_task_module_init();
	tftp_shell_module_init();
	tftp_server_module_init();
	
	while(TRUE){

	}
	return 0;
}
