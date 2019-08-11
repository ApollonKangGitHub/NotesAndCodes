#include <tftpShell.h>
#include <tftpType.h>
#include <tftpLog.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#include <unistd.h>
#include <pthread.h>

LOCAL VOID ttp_shell_normal_menu(VOID);
LOCAL VOID ttp_shell_debug_menu(VOID);
LOCAL VOID * tftp_shell_thread_deal(VOID * argv);
LOCAL INT32 tftp_shell_thread_create(VOID);

VOID ttp_shell_normal_menu(VOID)
{
	tftp_print("\n------------------------%s MENU-------------------------", 
		__TFTP_SHELL_VERSION_);
	tftp_print("\nexit   :   Quit the TFTP server");
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
	TFTP_LOGDBG(tftp_dbgSwitch_Shell, "input=%s, len=%d", input, strlen(input));
	
	if (0 == strcmp(input, "debug on")){
		tftp_print("\ndebug switch menu is on!");
		tftp_log_debug_control(tftp_dbgSwitch_Shell, __TFTP_DBG_ON_);
	}
	else if (0 == strcmp(input, "debug off")){
		tftp_print("\ndebug switch menu is off!");
		tftp_log_debug_control(tftp_dbgSwitch_Shell, __TFTP_DBG_OFF_);
	}
	else if (0 == strcmp(input, "exit"))
	{
		exit(EXIT_SUCCESS);
	}
	else if (0 == strcmp(input, "client"))
	{

	}
	else if (0 == strcmp(input, "server"))
	{

	}
	else if (0 == strcmp(input, "thread"))
	{

	}
	else{
		tftp_print("\nInvalid input, please Re-input!");
	}
}

VOID * tftp_shell_thread_deal(VOID * argv)
{
	CHAR shellStr[__TFTP_SHELL_BUFFER_LEN_MAX_] = {0};
	ttp_shell_normal_menu();
	while(TRUE)
	{
		memset(shellStr, 0, sizeof(shellStr));
		tftp_shell_line(shellStr, sizeof(shellStr));
		
		tftp_shell_deal_input(shellStr);
		usleep(100);
	}
	
	return argv;
}
LOCAL INT32 tftp_shell_thread_create(VOID)
{
	pthread_t tid;
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	
	/* 设置分离态 */
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	/* 设置线程栈大小 */
	pthread_attr_setstacksize(&attr, __TFTP_SHELL_THREAD_STACK_SIZE_);

	/* 创建线程 */
	pthread_create(&tid, &attr, tftp_shell_thread_deal, NULL);

	/* 线程资源使用完后释放资源 */
	pthread_attr_destroy(&attr);

	return tftp_ret_Ok;
}

EXTERN INT32 tftp_shell_init(VOID)
{
	/* 创建shell线程 */
	tftp_shell_thread_create();

	/* 创建线程对应相关信号量 */

	/* 释放信号量，启动shell线程 */
}

