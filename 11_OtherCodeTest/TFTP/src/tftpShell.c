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

EXTERN BOOL initSucces;

/*
 * FunctionName:
 *     ttp_shell_normal_menu
 * Description:
 *     命令行菜单简略信息
 * Notes:
 *     
 */
VOID ttp_shell_normal_menu(VOID)
{
	tftpShellList_t * pTemp = gShellHead;
	INT32 index = 0;
	CHAR cmdStr[__TFTP_SHELL_BUFFER_LEN_MAX_] = {0};
	CHAR cmdChild[__TFTP_SHELL_BUFFER_LEN_MAX_] = {0};
	
	tftp_print("\r\n-------------------------------------------------------------------"); 
	tftp_print("\r\n------------------------%s MENU-------------------------", __TFTP_SHELL_VERSION_);

	while (pTemp) {
		if(pTemp->_status & __TFTP_CMD_HIDE_) {
			pTemp = pTemp->_next;
			continue;
		}
		tftp_print("\r\n");
		memset(cmdStr, 0, sizeof(cmdStr));
		for (index = 0; index < pTemp->_cmdArgc && index < __TFTP_SHELL_CMD_MAX_NUM_; index++) {
			if (pTemp->_cmdArgv._info[index]._type == tftpCmdType_cmd) {
				memset(cmdChild, 0, sizeof(cmdChild));
				tftp_sprint(cmdChild ,"%s ", pTemp->_cmdArgv._info[index]._cmdStr);
				strcat(cmdStr, cmdChild);
			}
			else {
				strcat(cmdStr, "xxx ");
			}
		}
		memset(cmdChild, 0, sizeof(cmdChild));
		tftp_sprint(cmdChild ,": %s", pTemp->_cmdArgv._info[0]._cmdDescr);
		strcat(cmdStr, cmdChild);
		tftp_print("%s", cmdStr);
		pTemp = pTemp->_next;
	}
	tftp_print("\r\n-------------------------------------------------------------------"); 	
}

/*
 * FunctionName:
 *     tftp_shell_wait_for_string
 * Description:
 *     阻塞获取命令行输入
 * Notes:
 *     
 */
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

/*
 * FunctionName:
 *     tftp_shell_line
 * Description:
 *     获取命令行字符串
 * Notes:
 *     
 */
LOCAL INT32 tftp_shell_line(CHAR * str, INT32 strLen)
{
	if (NULL == str){
		TFTP_LOGERR("Error parameter, str=%p", str);
		return -1;
	}
	
	tftp_print("\r\ntftp>");
	return tftp_shell_wait_for_string(str, strLen);
}

/*
 * FunctionName:
 *     tftp_shell_cmd_deal
 * Description:
 *     命令行字符串格式化切割成多个命令
 * Notes:
 *     
 */
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
	(VOID)clearMoreSpace(shellStr);
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

/*
 * FunctionName:
 *     tftp_shell_cmd_deal
 * Description:
 *     命令检查与执行
 * Notes:
 *     
 */
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
		if (argc != argcReg) {
			pTemp = pTemp->_next;
			continue;
		}

		for (index = 0; index < argcReg; index++) {
			/* 命令字符串检查 */
			if ((pTemp->_cmdArgv._info[index]._type == tftpCmdType_cmd)
				&& (strcasecmp(pTemp->_cmdArgv._info[index]._cmdStr, argv[index]))) {
				break;
			}
			/* 命令"__IPADDR__"检查 */
			else if (pTemp->_cmdArgv._info[index]._type == tftpCmdType_ip) {
				if(NULL == strIpv4Check(argv[index])) {
					tftp_print("\r\nError ip address:%s", argv[index]);
					break;
				}
			}
			/* 命令"__STRING__"检查 */
			else if (pTemp->_cmdArgv._info[index]._type == tftpCmdType_str) {
				if (NULL == strCmdStrCheck(argv[index])) {
					tftp_print("\r\nError string value:%s", argv[index]);
					break;
				}
			}
			/* 命令"__INT32__"检查 */
			else if (pTemp->_cmdArgv._info[index]._type == tftpCmdType_int32) {
				if (NULL == strInt32Check(argv[index])) {
					tftp_print("\r\nError 32bits int value:%s", argv[index]);
					break;
				}
			}
			/* 命令"__UINT32__"检查 */
			else if (pTemp->_cmdArgv._info[index]._type == tftpCmdType_uint32) {
				if (NULL == strUint32Check(argv[index])) {
					tftp_print("\r\nError 32bits unsigned int value:%s", argv[index]);
					break;
				}
			}
			/* 命令"__HEX32__"检查 */
			else if (pTemp->_cmdArgv._info[index]._type == tftpCmdType_hex) {
				if (NULL == strHexCheck(argv[index])) {
					tftp_print("\r\nError hex value:%s", argv[index]);
					break;
				}
			}
		}

		/* 参数格式检查完毕，并且函数默认已经注册 */
		if (index == argcReg) {
			if (pTemp->_status & __TFTP_CMD_DYN_) {
				goto __tftp_deal_function;
			}
			else {
				goto _tftp_deal_invalid_cmd;
			}
		}
		
		else {
			/* 对于参数个数相同，但是命令格式不一致进行下一条命令判断 */
			pTemp = pTemp->_next;
		}
	}

_tftp_deal_invalid_cmd:	
	if ((NULL == pTemp) && (NULL != argv[0])
		|| !(pTemp->_status & __TFTP_CMD_DYN_)) {
		tftp_print("\r\nPlease running 'shellcmd display %s' "
					"command to display detail information only for '%s'"
					"\r\nOr enter ? / help to get help information", argv[0], argv[0]);
		return tftp_ret_Invalid;
	}
	
__tftp_deal_function:
	/* 执行具体函数 */
	(pTemp->_dealFun)(argc, argv);

	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_shell_task_deal
 * Description:
 *     shell任务主函数，负责字符串获取、格式化、检查、执行等
 * Notes:
 *     
 */
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

	while (!initSucces) {
		usleep(1000 * 10);
	}
	
	ttp_shell_normal_menu();
	while (TRUE) {
		memset(shellStr, 0, sizeof(shellStr));
		lineLen = tftp_shell_line(shellStr, sizeof(shellStr));
		if (lineLen < 1) {
			continue;
		}
		tftp_shell_line_format(shellStr, &shellArgc, shellArgv);
		tftp_shell_cmd_deal(shellArgc, shellArgv);
		usleep(1000 * 10);
	}
	
	return argv;
}

/*
 * FunctionName:
 *     tftp_shell_thread_create
 * Description:
 *     shell任务创建
 * Notes:
 *     
 */
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
 *     tftp_shell_cmd_type_get
 * Description:
 *     根据注册格式化字符串获取shell命令类型
 * Notes:
 *     
 */
LOCAL tftpCmdType_t tftp_shell_cmd_type_get(CONST CHAR * strCmd)
{
	if (NULL == strCmd) {
		return tftpCmdType_unknown;
	}
	
	TFTP_LOGDBG(tftp_dbgSwitch_shell, "strCmd=%s", strCmd);
	
	if (0 == strncmp(__TFTP_CMD_CMD_, strCmd, strlen(__TFTP_CMD_CMD_))) {
		return tftpCmdType_cmd;
	}
	else if (0 == strncmp(__TFTP_CMD_STR_, strCmd, strlen(__TFTP_CMD_STR_))) {
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
		/* 非格式化字符串默认是指令 */
		return tftpCmdType_cmd;
	}
	return tftpCmdType_cmd;
}

/*
 * FunctionName:
 *     tftp_shell_cmd_insert
 * Description:
 *     shell命令注册创建的节点插入链表
 * Notes:
 *     
 */
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
 *     tftp_shell_cmd_register
 * Description:
 *     命令shell格式解析注册函数
 * Notes:
 *     此外命令注册时，字符'{'和'}'前后均不能有空格
 */
EXTERN tftpReturnValue_t tftp_shell_cmd_register
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
		pCmdNode->_cmdArgv._info[index]._type = tftp_shell_cmd_type_get(pCmdBuf);

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
 *     tftp_shell_cmd_dyn_deal
 * Description:
 *     动态命令注册执行函数
 * Notes:
 *     
 */
LOCAL VOID tftp_shell_cmd_dyn_deal
(
	INT32 argc, 
	CONST CHAR * argv[]
)
{
	VOLATILE BOOL enable = FALSE;
	VOLATILE BOOL disable = FALSE;
	VOLATILE tftpShellList_t * pTemp = gShellHead;
	CONST CHAR * cmdName = argv[2];
	CONST CHAR * cmdEnable = argv[3];
	VOLATILE BOOL enableAll = FALSE;
	
	enableAll = (0 == strcasecmp(cmdName, "all")) ? (TRUE) : (FALSE);
	enable = (0 == strcasecmp(cmdEnable, "enable")) ? (TRUE) : (FALSE);
	disable = (0 == strcasecmp(cmdEnable, "disable")) ? (TRUE) : (FALSE);

	if (0 == strcasecmp(cmdEnable, "dynamic")) {
		tftp_print("\r\nplease don't try disable this command:%s!!!", cmdName);
	}
	
	while (pTemp) {
		if ((0 == strcasecmp(cmdName, pTemp->_cmdArgv._info[0]._cmdStr)) || enableAll
			&& (strcasecmp("dynamic", pTemp->_cmdArgv._info[0]._cmdStr))) {
			
			if (enable && !(pTemp->_status & __TFTP_CMD_DYN_)) {
				pTemp->_status &= 0;
				pTemp->_status |= (__TFTP_CMD_NORMAL_) | (__TFTP_CMD_DYN_);
				tftp_print("\r\n%s is already dynamic register success!", pTemp->_cmdArgv._info[0]._cmdStr);
			}
			else if (disable && (pTemp->_status & __TFTP_CMD_DYN_)) {
				pTemp->_status &= 0;
				pTemp->_status |= __TFTP_CMD_HIDE_;
				tftp_print("\r\n%s is already delete register success!", pTemp->_cmdArgv._info[0]._cmdStr);
			}
			/* 只enable一个，则enable后直接结束 */
			if (!enableAll) {
				break;
			}
		}
		pTemp = pTemp->_next;
	}

	if (!pTemp && (strcasecmp(cmdName, "all"))) {
		tftp_print("\r\n%s is not a valid command name", cmdName);
	}
}

/*
 * FunctionName:
 *     tftp_shell_cmd_display
 * Description:
 *     显示命令的输入格式
 * Notes:
 *     
 */
LOCAL tftpReturnValue_t tftp_shell_cmd_display(INT32 argc, CHAR * argv[])
{
	tftpShellList_t * pTemp = gShellHead;
	INT32 argcReg = 0;
	INT32 index = 0;
	CHAR * pcmd = argv[2];

	TFTP_LOGDBG(tftp_dbgSwitch_shell, "tftp shell cmd display, argc=%d", argc);
	
	tftp_print("\r\ncommand list detail information:");
	while (pTemp) {
		if(pTemp->_status & __TFTP_CMD_HIDE_) {
			pTemp = pTemp->_next;
			continue;
		}
		argcReg = pTemp->_cmdArgc;
		if ((0 == strcasecmp(pcmd, "all")) || (0 == strcmp(pcmd, pTemp->_cmdArgv._info[0]._cmdStr))) {
			tftp_print("\r\n\t------------------------------command:%s [start]", pTemp->_cmdArgv._info[0]._cmdStr);
			for (index = 0; index < argcReg && index < __TFTP_SHELL_CMD_MAX_NUM_; index++) {
				tftp_print("\n\t%-16s:%s ", 
					pTemp->_cmdArgv._info[index]._cmdStr,
					pTemp->_cmdArgv._info[index]._cmdDescr);
			}
			tftp_print("\r\n\t------------------------------command:%s [end]\r\n", pTemp->_cmdArgv._info[0]._cmdStr);
		}

		/* 找到后直接结束 */
		if (0 == strcasecmp(pcmd, pTemp->_cmdArgv._info[0]._cmdStr)) {
			break;
		}
		pTemp = pTemp->_next;
	}

	if ((!pTemp) && strcasecmp(pcmd, "all")) {
		tftp_print("\r\nnot found '%s' this command, please check it", pcmd);
	}
	
	return tftp_ret_Ok;
}

/*
 * FunctionName:
 *     tftp_shell_cmd_display
 * Description:
 *     显示命令的输入格式，命令行菜单详细信息
 * Notes:
 *     
 */
LOCAL VOID tftp_shell_detail_menu(VOID)
{
	INT32 argc = 3;
	CHAR * argv[3] = {"shellcmd", "display", "all"};
	tftp_shell_cmd_display(argc, argv);
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
	
	tftp_shell_cmd_register((tftp_cmd_deal_fun)ttp_shell_normal_menu, 
		__TFTP_CMD_NORMAL_ | __TFTP_CMD_DYN_, 
			"?{shell command help menu with simple information}");

	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_shell_detail_menu, 
		__TFTP_CMD_NORMAL_ | __TFTP_CMD_DYN_, 
			"help{shell command help menu with detail all}");

	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_shell_cmd_dyn_deal, 
		__TFTP_CMD_HIDE_ | __TFTP_CMD_DYN_, 
			"dynamic{shell command dynamic register(enable/disable)}"
				"command{shell command dynamic register}"
					"__STRING__{command do you want to dynamic register}"
						"__STRING__{enable or disable}");
		
	tftp_shell_cmd_register((tftp_cmd_deal_fun)tftp_shell_cmd_display, 
		__TFTP_CMD_NORMAL_ | __TFTP_CMD_DYN_,
			"shellcmd{Display command with format for special command}"
				"display{display command format}"
					"__STRING__{command string}");
}

/*
 * FunctionName:
 *     tftp_shell_module_init
 * Description:
 *     shell模块初始化
 * Notes:
 *     
 */
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


