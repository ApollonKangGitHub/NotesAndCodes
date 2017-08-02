/*编写/home/usr的守护进程，如果该目录下文件发生修改/删除/创建...等
 *则在change.log中写入变动时间、动作等信息
 * */
void sys_err(const char * buf)
{
	perror(buf);
	exit(EXIT_FAILURE);
}
void create_daemon(void)
{
	pid_t pid;
	if((pid = fork()) < 0){
		perror("daemon fork\n");
		exit(EXIT_FAILURE);
	}
	else if(pid > 0)
		exit(EXIT_SUCCESS);

	setsid();
	
	if(chdir("/") < 0){
		perror("chdir");	
		exit(EXIT_FAILURE);
	}

	umask(0);
	
	close(0);
	open("/dev/null", O_RDWR);
	dup2(0,1);
	dup2(0,2);
}
int main(void)
{
	create_daemon();

}
