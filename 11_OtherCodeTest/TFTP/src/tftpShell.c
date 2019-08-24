#include <tftpShell.h>
#include <tftpType.h>
#include <tftpLog.h>
#include <tftpTask.h>
#include <tftpServer.h>

#include <tftpPublic.h>

LOCAL CHAR gCmdStrBuf[__TFTP_CMD_REG_STR_LEN_] = {0};
LOCAL CHAR gCmdFormat[__TFTP_SHELL_CMD_MAX_NUM_][__TFTP_SHELL_CMD_MAX_LEN_] = {0};
LOCAL tftpShellList_t * gShellHead = NULL;
LOCAL tftpShellList_t * gShellTail = NULL;

VOID ttp_shell_normal_menu(VOID)
{
	tftp_print("\r\n-------------------------------------------------------------------"); 
	tftp_print("\r\n------------------------%s MENU-------------------------", __TFTP_SHELL_VERSION_);
	tftp_print("\r\n| shellcmd      :   Display all not hide command with format      |");
	tftp_print("\r\n| sem           :   Display the sem list info                     |");
	tftp_print("\r\n| quit          :   Quit the TFTP server                          |");
	tftp_print("\r\n| client        :   Download target file with argument            |");
	tftp_print("\r\n| server        :   Start the TFTP server or close server         |");
	tftp_print("\r\n| thread        :   Display the thread list info                  |");
	tftp_print("\r\n| taskPool      :   Display the sem list info                     |");
	tftp_print("\r\n-------------------------------------------------------------------"); 
}

LOCAL INT32 tftp_shell_wait_for_string(CHAR * str, INT32 strLen)
{
	CHAR * read = 0;
	ssize_t len = (ssize_t)strLen;
	char * pLine = str;
	FILE * stream = __TFTP_STDIN_;
	INT32 getLen = 0;
	
	read = tftp_gets(pLine, len, stream);
	if(NULL == read){
		TFTP_LOGERR("Get stdin input is error, read=%p", read);
		return -1;
	}

	/* 获取shell输入的长度 */
	getLen = strlen(pLine);
	
	if((getLen > 0) && (pLine[getLen - 1] == '\n')){
		pLine[getLen - 1] = '\0';	/* 替换换行符为字符串结束符 */
	}
	
	/* 重新获取shell输入的长度 */
	getLen = strlen(pLine);

	return getLen;
}

LOCAL INT32 tftp_shell_line(CHAR * str, INT32 strLen)
{
	if (NULL == str){
		TFTP_LOGERR("Error parameter, str=%p", str);
		return -1;
	}
	
	tftp_print("\r\ntftp>");
	return tftp_shell_wait_for_string(str, strLen);
}

VOID tftp_shell_deal_input(CONST CHAR * input)
{
	TFTP_LOGDBG(tftp_dbgSwitch_shell, "input=%s, len=%d", input, strlen(input));
	tftpReturnValue_t ret = tftp_ret_Ok;
	
	if (0 == strcmp(input, "debug on")){
		tftp_print("\r\ndebug switch menu is on!");
		tftp_log_debug_control(tftp_dbgSwitch_shell, __TFTP_DBG_ON_);
	}
	else if (0 == strcmp(input, "debug off")){
		tftp_print("\r\ndebug switch menu is off!");
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
	#if 0
	else {
		if (0 != strlen(input)) {
			tftp_print("\nInvalid input, please Re-input!");
		}
	}

	if (ret == tftp_ret_Invalid) {
		TFTP_LOGNOTE("shell inpiut return %s(%d)", tftp_err_msg(ret), ret);
	}
	#endif
}

LOCAL tftpReturnValue_t tftp_shell_line_format
(
	CHAR * shellStr, 
	INT32 * argc, 
	CHAR ** argv
)
{
	CHAR * strPtr = NULL;
	CHAR * savePtr = NULL;
	CHAR * pstr = shellStr;
	INT32 index = 0;

	if (NULL == shellStr) {
		return tftp_ret_Null;
	}
	
	TFTP_LOGDBG(tftp_dbgSwitch_shell, "shell shell string:%s", shellStr);
	(VOID)clear_more_space(shellStr);
 	TFTP_LOGDBG(tftp_dbgSwitch_shell, "shell shell string:%s", shellStr);
	
	savePtr = pstr;
	while (*savePtr != '\0') {
		strPtr = strtok_r(pstr, " ", &savePtr);
		strncpy(argv[index], strPtr, __TFTP_SHELL_CMD_MAX_LEN_);
		index++;
		pstr = NULL;
	}
	*argc = index;

	for (index = 0; index < *argc; index++) {
		TFTP_LOGDBG(tftp_dbgSwitch_shell, 
			"shell argc:%d, argv[%d]:%s", *argc, index, argv[index]);
	}
	return tftp_ret_Ok;
}

LOCAL tftpReturnValue_t tftp_shell_cmd_deal
(
	INT32 argc, 
	CHAR ** argv
)
{
	tftpShellList_t * pTemp = gShellHead;
	INT32 argcReg = 0;
	INT32 index = 0;

	if(NULL == argv) {
		return tftp_ret_Null;
	}

	for (index = 0; index < argc; index++) {
		TFTP_LOGDBG(tftp_dbgSwitch_shell, 
			 	"shell argc:%d, argv[%d]:%s", argc, index, argv[index]);
	}
	
	while (pTemp) {
		argcReg = pTemp->_cmdArgc;
		if (argc <= argcReg) {
			if (0 == strcmp(pTemp->_cmdArgv._info[0]._cmdStr, argv[0])) {
				(pTemp->_dealFun)(argc, argv);
				break;
			}
		}
		pTemp = pTemp->_next;
		index++;
	}
	
}

VOID * tftp_shell_task_deal(VOID * argv)
{
	INT32 shellArgc = 0;
	INT32 lineLen = 1;
	INT32 index = 0;
	CHAR shellStr[__TFTP_SHELL_BUFFER_LEN_MAX_] = {0};
	CHAR * shellArgv[__TFTP_SHELL_CMD_MAX_NUM_] = {NULL};
	
	TFTP_LOGDBG(tftp_dbgSwitch_shell, "shell deal thread, argv=%p", argv);

	for (index = 0; index < __TFTP_SHELL_CMD_MAX_NUM_; index++) {
		shellArgv[index] = (CHAR *)(&gCmdFormat[index]);
	}
	
	while (TRUE) {
		if (lineLen > 0) {
			ttp_shell_normal_menu();
		}
		memset(shellStr, 0, sizeof(shellStr));
		lineLen = tftp_shell_line(shellStr, sizeof(shellStr));
		tftp_shell_line_format(shellStr, &shellArgc, shellArgv);
		tftp_shell_cmd_deal(shellArgc, shellArgv);
		
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

LOCAL tftpCmdType_t tftp_cmd_type_get(CONST CHAR * strCmd)
{
	if (NULL == strCmd) {
		return tftpCmdType_unknown;
	}
	
	TFTP_LOGDBG(tftp_dbgSwitch_shell, "strCmd=%s", strCmd);
	
	if (0 == strncmp(__TFTP_CMD_STR_, strCmd, strlen(__TFTP_CMD_STR_))) {
		return tftpCmdType_str;
	}
	else if (0 == strncmp(__TFTP_CMD_INT_, strCmd, strlen(__TFTP_CMD_UINT_))) {
		return tftpCmdType_int32;
	}
	else if (0 == strncmp(__TFTP_CMD_UINT_, strCmd, strlen(__TFTP_CMD_UINT_))) {
		return tftpCmdType_uint32;
	}
	else if (0 == strncmp(__TFTP_CMD_HEX_, strCmd, strlen(__TFTP_CMD_HEX_))) {
		return tftpCmdType_hex;
	}
	else if (0 == strncmp(__TFTP_CMD_IP_, strCmd, strlen(__TFTP_CMD_IP_))) {
		return tftpCmdType_ip;
	}
	else {
		/* 非格式化字符串也是字符串 */
		return tftpCmdType_str;
	}
	return tftpCmdType_unknown;
}

LOCAL tftpReturnValue_t tftp_shell_cmd_insert(tftpShellList_t * pCmdNode)
{
	if (NULL == pCmdNode) {
		return tftp_ret_Null;
	}

	if (NULL == gShellHead) {
		gShellHead = gShellTail = pCmdNode;
		gShellTail->_next = gShellTail->_pre = NULL;
	}
	else {
		pCmdNode->_pre = gShellTail;
		pCmdNode->_next = NULL;
		gShellTail->_next = pCmdNode;
		gShellTail = pCmdNode;
	}

	return tftp_ret_Ok;
}


/*
 * FunctionName:
 *     tftp_command_register
 * Description:
 *     命令shell格式解析注册函数
 * Notes:
 *     实现上的限制，注册命令时，命令前半部分可能相同，
 *     那么注册的处理函数接口必须为同一个
 */
EXTERN tftpReturnValue_t tftp_cmd_register
(
	tftp_cmd_deal_fun function, 
	tftpCmdAbil_t ability,
	CHAR * cmd_str
)
{
	CHAR * pCmdStr = NULL;
	CHAR * pCmdSaveStr = NULL;
	CHAR * pDesSaveStr = NULL;
	CHAR * pMove = NULL;
	CHAR * pCmdBuf = NULL;
	CHAR * pDesBuf = NULL;
	INT32 index = 0;
	INT32 lenCmd = 0;
	INT32 lenDes = 0;

	tftpShellList_t * pCmdNode;
	
	TFTP_LOGDBG(tftp_dbgSwitch_shell, "tftp shell command register, cmd_str=%p", cmd_str);
	
	if (NULL == cmd_str) {
		return tftp_ret_Null;
	}

	/* 构建命令注册链表节点 */
	memset(gCmdStrBuf, 0, __TFTP_CMD_REG_STR_LEN_);
	strncpy(gCmdStrBuf, cmd_str, __TFTP_CMD_REG_STR_LEN_);
	
	pCmdNode = malloc(sizeof(tftpShellList_t));
	memset(pCmdNode, 0, sizeof(tftpShellList_t));

	pCmdStr = pMove = gCmdStrBuf;

	while (*pMove) {

		/* 解析注册信息并填充节点 */
		pCmdSaveStr = strtok_r(pCmdStr, "{", &pMove);	/* 命令 */
		pDesSaveStr = strtok_r(NULL, "}", &pMove);		/* 描述 */

		/* 找到的两个字符串进行内存申请与内容填充 */
		lenCmd = strlen(pCmdSaveStr) + 1;
		lenDes = strlen(pDesSaveStr) + 1;
		pCmdBuf = malloc(lenCmd);
		pDesBuf = malloc(lenDes);
		memset(pCmdBuf, 0, lenCmd);
		memset(pDesBuf, 0, lenDes);
		strncpy(pCmdBuf, pCmdSaveStr, lenCmd);
		strncpy(pDesBuf, pDesSaveStr, lenDes);

		/* 节点赋值 */
		pCmdNode->_cmdArgv._info[index]._cmdStr = pCmdBuf;
		pCmdNode->_cmdArgv._info[index]._cmdDescr = pDesBuf;
		pCmdNode->_cmdArgv._info[index]._type = tftp_cmd_type_get(pCmdBuf);

		index++;
		pCmdStr = NULL;
		pCmdNode->_cmdArgc = index;
	}
	
	pCmdNode->_status = ability;
	pCmdNode->_dealFun = function;
	
	TFTP_LOGDBG(tftp_dbgSwitch_shell, "argc = %d, status= 0x%x", pCmdNode->_cmdArgc, pCmdNode->_status);
	for (index = 0; index < pCmdNode->_cmdArgc; index++) {
		TFTP_LOGDBG(tftp_dbgSwitch_shell,
			"argv[%d]:, %s:%s, type=%d, ", index,
			pCmdNode->_cmdArgv._info[index]._cmdStr,
			pCmdNode->_cmdArgv._info[index]._cmdDescr,
			pCmdNode->_cmdArgv._info[index]._type);
	}

	/* 插入保存节点 */
	tftp_shell_cmd_insert(pCmdNode);

	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_shell_cmd_help_deal
 * Description:
 *     帮助命令执行函数
 * Notes:
 *     
 */
LOCAL VOID tftp_shell_cmd_help_deal
(
	INT32 argc, 
	CONST CHAR * argv
)
{
	
}

/*
 * FunctionName:
 *     tftp_shell_cmd_dyn_deal
 * Description:
 *     动态命令注册执行函数
 * Notes:
 *     
 */
LOCAL VOID tftp_shell_cmd_dyn_deal
(
	INT32 argc, 
	CONST CHAR * argv
)
{

}

/*
 * FunctionName:
 *     tftp_shell_cmd_display
 * Description:
 *     动态命令注册执行函数
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_shell_cmd_display(INT32 argc, CHAR * argv[])
{
	tftpShellList_t * pTemp = gShellHead;
	INT32 argcReg = 0;
	INT32 index = 0;

	TFTP_LOGDBG(tftp_dbgSwitch_shell, "tftp shell cmd display, argc=%d", argc);

	if (argc > 4 || argc < 1) {
		TFTP_LOGWARN("too many or few argument:%d", argc);
		return tftp_ret_Invalid;
	}
	
	tftp_print("\r\ncommand list detail information:");
	while (pTemp) {
		argcReg = pTemp->_cmdArgc;
		tftp_print("\r\n");
		for (index = 0; index < argcReg && index < __TFTP_SHELL_CMD_MAX_NUM_; index++) {
			tftp_print("[%s] ", pTemp->_cmdArgv._info[index]._cmdStr);
		}
		pTemp = pTemp->_next;
	}
	return tftp_ret_Ok;
}


/*
 * FunctionName:
 *     tftp_shell_cmd_init
 * Description:
 *     动态命令注册执行函数
 * Notes:
 *     
 */
LOCAL VOID tftp_shell_cmd_init(VOID)
{
	TFTP_LOGDBG(tftp_dbgSwitch_shell, "tftp shell module shell command register");

	tftp_cmd_register((tftp_cmd_deal_fun)tftp_shell_cmd_display, 
		__TFTP_CMD_HIDE_ | __TFTP_CMD_DYN_,
		"shellcmd{shell command display}"
			"display{display command format}"
				"command{display with tid}"
					"__STRING__{command string}");

}

EXTERN INT32 tftp_shell_module_init(VOID)
{
	TFTP_LOGNOR("tftp shell module init......");

	/* 创建shell线程 */
	tftp_shell_thread_create();

	/* 注册shell任务相关命令 */
	tftp_shell_cmd_init();

	/* 创建线程对应相关信号量 */
	
	/* 释放信号量，启动shell线程 */
}


