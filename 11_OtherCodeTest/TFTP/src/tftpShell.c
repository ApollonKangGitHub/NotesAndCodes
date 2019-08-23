#include <tftpShell.h>
#include <tftpType.h>
#include <tftpLog.h>
#include <tftpTask.h>
#include <tftpServer.h>

#include <tftpPublic.h>

VOID ttp_shell_normal_menu(VOID)
{
	tftp_print("\n------------------------%s MENU-------------------------", __TFTP_SHELL_VERSION_);
	tftp_print("\nsem           :   Display the sem list info");
	tftp_print("\nquit          :   Quit the TFTP server");
	tftp_print("\nclient        :   Download target file with argument");
	tftp_print("\nserver        :   Start the TFTP server or close server");
	tftp_print("\nthread        :   Display the thread list info");
	tftp_print("\ntaskPool      :   Display the sem list info");
	tftp_print("\n-------------------------------------------------------------------"); 
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
		tftpTaskStruct_t tstructId = 0;
		tstructId = tftp_task_get_structId();
		exit(EXIT_SUCCESS);
		/* do something, last to destroy all task */
		
		//(VOID)tftp_task_destroy(tstructId);
	}
	else if (0 == strcmp(input, "client")) {

	}
	else if (0 == strcmp(input, "server")) {

	}
	else if (0 == strcmp(input, "thread")) {
		tftp_task_list_display();
	}
	else if (0 == strcmp(input, "sem")) {
		tftp_sem_list_display();
	}
	else if (0 == strcmp(input, "taskPool")) {
		tftp_task_pool_display();
	}
	else {
		if (0 != strlen(input)) {
			tftp_print("\nInvalid input, please Re-input!");
		}
	}
}

VOID * tftp_shell_task_deal(VOID * argv)
{
	CHAR shellStr[__TFTP_SHELL_BUFFER_LEN_MAX_] = {0};
	TFTP_LOGDBG(tftp_dbgSwitch_shell, "shell deal thread, argv=%p", argv);

	while (TRUE) {
		ttp_shell_normal_menu();
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
	memset(&shellTask, 0, sizeof(tftpTaskInfo_t));

	shellTask._pid = 0;
	shellTask._tid = 0;
	shellTask._taskStructid = 0;
	shellTask._deal_function = tftp_shell_task_deal;
	shellTask._stackSize = __TFTP_SHELL_TASK_STACK_SIZE_;
	shellTask._detachState = __TFTP_TASK_DETACHED_;
	strncpy(shellTask._name, __TFTP_TASK_NAME_SHELL_, __TFTP_TASK_NAME_LENGTH_);

	/* 初始化shell线程 */
	tftp_task_create_init(&shellTask);

	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_command_register
 * Description:
 *     命令shell格式解析注册函数
 * Notes:
 *     命令注册格式:分为两部分参数，
 *     命令执行函数和命令注册格式化字符串，具体如：
 * 	   tftp_command_register(tftp_cmd_del_task_info, 
 *         __TFTP_CMD_HIDE_ | __TFTP_CMD_DYN_,
 *         "tftpThread(1, 'destription for tftpThread'){"
 *	          "display(2, 'display some information'){"
 *		          "__STRING__(0, 'string for thread name'),"
 *		          "__NUMBER__(0, 'thread id type is tid'),"
 *		          "__OVER__(0, 'flag over for cmd register')"
 *		      "}"
 *         "}"
 *     );
 *
 */
EXTERN tftpReturnValue_t tftp_command_register
(
	tftp_cmd_deal_fun function, 
	CONST CHAR * cmd_str
)
{
	/* 解析注册信息 */

	/* 构建命令注册链表节点 */

	/* 挂载节点 */
}

/*
 * FunctionName:
 *     tftp_shell_command_help_deal
 * Description:
 *     帮助命令执行函数
 * Notes:
 *     
 */
LOCAL VOID tftp_shell_command_help_deal
(
	INT32 argc, 
	CONST CHAR * argv
)
{
	
}

/*
 * FunctionName:
 *     tftp_shell_command_dynmaic_deal
 * Description:
 *     动态命令注册执行函数
 * Notes:
 *     
 */
LOCAL VOID tftp_shell_command_dynmaic_deal
(
	INT32 argc, 
	CONST CHAR * argv
)
{

}


/*
 * FunctionName:
 *     tftp_shell_cmd_init
 * Description:
 *     
 * Notes:
 *     
 */
LOCAL VOID tftp_shell_command_init(VOID)
{
	//tftp_command_register(tftp_shell_command_help_deal, "");
	//tftp_command_register(tftp_shell_command_dynmaic_deal, "");
}
EXTERN INT32 tftp_shell_module_init(VOID)
{
	TFTP_LOGNOR("tftp shell module init......");

	/* 创建shell线程 */
	tftp_shell_thread_create();

	/* 创建线程对应相关信号量 */

	/* 释放信号量，启动shell线程 */
}


