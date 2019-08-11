#include <tftpLog.h>
#include <tftpType.h>
#include <stdio.h>

INT32 main(void)
{
	tftp_log_init();
	
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_task, __TFTP_DEBUG_ON_);
	__SET_BIT(gDbgSwitchFlg, tftp_dbgSwitch_Server, __TFTP_DEBUG_OFF_);

	TFTP_LOGNOR("Log File Start");

	TFTP_LOGNOR("Hello world!%d,%d,%d,%d", 1, 2, 3, 4);
	TFTP_LOGDBG(tftp_dbgSwitch_task, "Hello world!%d,%d,%d,%d", 11, 22, 33, 44);
	TFTP_LOGDBG(tftp_dbgSwitch_Server, "Hello world!%d,%d,%d,%d", 111, 222, 333, 444);
	TFTP_LOGWARN("Hello world!%d,%d,%d,%d", 1111, 2222, 3333, 4444);
	TFTP_LOGNOTE("Hello world!%d,%d,%d,%d", 11111, 22222, 33333, 44444);
	TFTP_LOGERR("Hello world!%d,%d,%d,%d", 111111, 222222, 333333, 444444);

	TFTP_LOGNOR("Log File End\r\n");
	return 0;
}
