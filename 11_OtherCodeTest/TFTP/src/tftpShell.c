#include <tftpShell.h>
#include <tftpType.h>
#include <tftpLog.h>
#include <tftpTask.h>

#include <tftpPublic.h>

LOCAL VOID ttp_shell_normal_menu(VOID);
LOCAL VOID ttp_shell_debug_menu(VOID);
LOCAL VOID * tftp_shell_thread_deal(VOID * argv);
LOCAL INT32 tftp_shell_thread_create(VOID);

VOID ttp_shell_normal_menu(VOID)
{
	tftp_print("\n------------------------%s MENU-------------------------", 
		__TFTP_SHELL_VERSION_);
	tftp_print("\nquit   :   Quit the TFTP server");
	tftp_print("\nclient :   Download target file with argument");
	tftp_print("\nserver :   Start the TFTP server or close server");
	tftp_print("\nthread :   Display the thread info");
	tftp_print("\n--------------------------------------------------------"); 
}

VOID ttp_shell_debug_menu(VOID)
{
	
}

INT32 tftp_shell_wait_for_string(CHAR * str, INT32 strLen)
{
	CHAR * read = 0;
	ssize_t len = (ssize_t)strLen;
	char * pLine = str;
	FILE * stream = __TFTP_STDIN_;
	INT32 getLen = 0;
	
	read = tftp_gets(pLine, len, stream);
	if(NULL == read){
		TFTP_LOGERR("\nGet stdin input is error, read=%p", read);
		return tftp_ret_Error;
	}

	/* 获取shell输入的长度 */
	getLen= strlen(pLine);
	
	if((getLen > 0) && (pLine[getLen - 1] == '\n')){
		pLine[getLen - 1] = '\0';	/* 替换换行符为字符串结束符 */
	}

	return tftp_ret_Ok;
}

INT32 tftp_shell_line(CHAR * str, INT32 strLen)
{
	if (NULL == str){
		TFTP_LOGERR("Error parameter, str=%p", str);
		return tftp_ret_Error;
	}
	
	tftp_print("\ntftp>");
	tftp_shell_wait_for_string(str, strLen);
	
	return tftp_ret_Ok;
}

VOID tftp_shell_deal_input(CONST CHAR * input)
{
	TFTP_LOGDBG(tftp_dbgSwitch_shell, "input=%s, len=%d", input, strlen(input));
	
	if (0 == strcmp(input, "debug on")){
		tftp_print("\ndebug switch menu is on!");
		tftp_log_debug_control(tftp_dbgSwitch_shell, __TFTP_DBG_ON_);
	}
	else if (0 == strcmp(input, "debug off")){
		tftp_print("\ndebug switch menu is off!");
		tftp_log_debug_control(tftp_dbgSwitch_shell, __TFTP_DBG_OFF_);
	}
	else if (0 == strcmp(input, "quit")) {
		tftpTid_t tid = 0;
		tid = tftp_task_get_tid();
		/* 如果服务器还在运行，需要将主线程放到后台执行... */

		/* do something, last to destroy task */
		
		(VOID)tftp_task_destroy(tid);
	}
	else if (0 == strcmp(input, "client")) {

	}
	else if (0 == strcmp(input, "server")) {

	}
	else if (0 == strcmp(input, "thread")) {
		INT32 taskIndex = __TFTP_TASK_ID_START_;
		INT32 taskNum = 0;
		tftpTaskInfo_t taskInfo;
		memset(&taskInfo, 0, sizeof(tftpTaskInfo_t));

		/* 各个条目信息 */
		tftp_print("\r\n%-16s%-16s%-16s%-16s", 
			"taskName", "stackSize(B)", "taskId", "detachStatus");
		
		while (taskNum = tftp_task_get_info(taskIndex, &taskInfo))	{
			TFTP_LOGDBG(tftp_dbgSwitch_shell, "\r\n%-16s%-16d%-16lld%-16s[taskIndex = %d, taskNum=%d]", \
				taskInfo._name, taskInfo._stackSize, taskInfo._tid, (taskInfo._detachState == __TFTP_TASK_DETACHED_) \
					? "detach" : "attach", taskIndex, taskNum);

			tftp_print("\r\n%-16s%-16d%-16lld%-16s",
				taskInfo._name, taskInfo._stackSize, taskInfo._tid,
					(taskInfo._detachState == __TFTP_TASK_DETACHED_) ? "detach" : "attach");
			if (taskIndex >= taskNum) {
				break;
			}
			else {
				taskIndex++;
			}
		}
	}
	else {
		if (0 != strlen(input)) {
			tftp_print("\nInvalid input, please Re-input!");
		}
	}
}

VOID * tftp_shell_thread_deal(VOID * argv)
{
	CHAR shellStr[__TFTP_SHELL_BUFFER_LEN_MAX_] = {0};
	ttp_shell_normal_menu();
	while (TRUE) {
		memset(shellStr, 0, sizeof(shellStr));
		tftp_shell_line(shellStr, sizeof(shellStr));
		
		tftp_shell_deal_input(shellStr);
		usleep(1000);
	}
	
	return argv;
}
LOCAL INT32 tftp_shell_thread_create(VOID)
{
	tftpTaskInfo_t shellTask;
	CHAR taskName[__TFTP_TASK_NAME_LENGTH_] = {__TFTP_TASK_NAME_SHELL_};
	
	memset(&shellTask, 0, sizeof(tftpTaskInfo_t));

	shellTask._tid = -1;
	shellTask._deal_function = tftp_shell_thread_deal;
	shellTask._stackSize = __TFTP_SHELL_THREAD_STACK_SIZE_;
	shellTask._detachState = __TFTP_TASK_DETACHED_;
	strncpy(shellTask._name, taskName, __TFTP_TASK_NAME_LENGTH_);

	/* 初始化shell线程 */
	tftp_task_create_init(&shellTask);

	return tftp_ret_Ok;
}

EXTERN INT32 tftp_shell_module_init(VOID)
{
	/* 创建shell线程 */
	tftp_shell_thread_create();

	/* 创建线程对应相关信号量 */

	/* 释放信号量，启动shell线程 */
}

