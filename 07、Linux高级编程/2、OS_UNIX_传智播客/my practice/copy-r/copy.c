#include<copy.h>

int fd[2] = {0};

void sys_err(const char * ptr)
{
	perror(ptr);
	exit(EXIT_FAILURE);
}

void deal_dir(char *old_path,char * new_path)
{
	DIR * ret_opdir = opendir(old_path);//打开目录
	if(ret_opdir == NULL)
		sys_err("opendir");
	struct dirent * ret_redir;
	
	char buf_old[PATH_SIZE] = {};
	char buf_new[PATH_SIZE] = {};
	char buf_oldfile[PATH_SIZE] = {};
	char buf_newfile[PATH_SIZE] = {};
	
	/*获取源文件完整路径与目标位置完整路径,分别存入buf_old与buf_new中*/
	get_allpath(buf_old, buf_new, old_path, new_path);	

	while((ret_redir = readdir(ret_opdir))){//读取目录，失败或目录读完返回NULL
		if(!strcmp(ret_redir->d_name, ".") || !strcmp(ret_redir->d_name, ".."))
			continue;
		else{
			/*清除上次复制的文件路径，并填入新读取到的文件的路径*/
			init_allpath(buf_old, buf_new, buf_oldfile, buf_newfile, ret_redir->d_name);
			if((ret_redir->d_type & DT_REG) == DT_REG)//如果读到的文件是普通文件则复制
				deal_copy(buf_oldfile, buf_newfile);	
			else if((ret_redir->d_type & DT_DIR) == DT_DIR)//如果读到的是目录则递归处理目录
				deal_dir(buf_oldfile, buf_newfile);
		}
	}
}

void get_allpath(char * buf_old, char * buf_new, char * old_path, char * new_path)
{
	char buf[PATH_SIZE] = {};
	getcwd(buf,PATH_SIZE);
	chdir(old_path);
	getcwd(buf_old,PATH_SIZE);
	strcat(buf_old, "/");

	chdir(buf);
	mkdir_newdir(new_path);
	chdir(new_path);
	getcwd(buf_new, PATH_SIZE);
	strcat(buf_new,"/");

}
void init_allpath(char * buf_old, char * buf_new, char * buf_oldfile, char * buf_newfile, char * name)
{
	memset(buf_oldfile, 0, PATH_SIZE);
	memset(buf_newfile, 0, PATH_SIZE);
	strcpy(buf_oldfile, buf_old);
	strcat(buf_oldfile, name);
	strcpy(buf_newfile, buf_new);
	strcat(buf_newfile, name);

}
void mkdir_newdir(char * new_path)
{
	DIR * ret_opdir = opendir(new_path);
	if(ret_opdir == NULL){
		int ret_mkdir = mkdir(new_path, DIR_MODE);
		if(ret_mkdir == -1)
			sys_err("mkdir newdir");
	}
}
void deal_copy(char *old_file, char * pathname)
{
	struct stat get_message;
	int ret_stat = stat(pathname, &get_message);	
	if(ret_stat == -1 && errno != ENOENT)//文件信息读取失败，并且不是因为无该文件造成的
		sys_err("stat in copy.c of deal_copy");
	
	fd[0] = open(old_file, O_RDONLY);
	if(fd[0] == -1)
		sys_err("open oldfile in copy_file");
	fd[1] = open(pathname, O_CREAT | O_TRUNC | O_RDWR, FILE_MODE);
	if(fd[1] == -1)
		sys_err("open newfile in copy_file");

	read_write();

	close(fd[0]);
	close(fd[1]);
}	
void read_write(void)
{
	char buf[BUF_SIZE] = {};
	int ret_read, ret_write;
	while((ret_read = read(fd[0], buf, BUF_SIZE)) > 0){
		ret_write = write(fd[1], buf, strlen(buf));
		if(ret_write == -1)
			sys_err("write newfile");
	}
}
