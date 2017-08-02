/*拷贝完成后可以用MD5校验文件完整性*/

#include<multiproccp.h>

void sys_err(const char * ptr_err)
{
	perror(ptr_err);
	exit(EXIT_FAILURE);
}
void deal_multi_process_copy(const char * oldfilepath, const char * newfile)
{
	struct stat file_msg;
	int ret, fsize, fd;
	if((ret = stat(oldfilepath, &file_msg)) < 0)
		sys_err("stat");

	fsize = file_msg.st_size;

	if((fd = open(newfile, O_CREAT|O_RDWR|O_TRUNC, 0777)) < 0)/*创建一个空文件*/
		sys_err("open newfile");

	lseek(fd, fsize-1, SEEK_SET);//扩大新文件至源文件一般大小
	write(fd, "\0", 1);//使得创建的空文件生效
	
	close(fd);
	multi_process_mmap(fsize, oldfilepath, newfile);
}

void multi_process_mmap(const int fsize, const char * oldfilepath, const char * newfile)
{
	int num, other, time = 0, max, n = 0, m = 0;
	int gsize = DFL_PROC_NUM * MMAP_SIZE;

	time = fsize / gsize;/*可达到最大进程数上限的组数,最大组进程个数为DFL_PROC_NUM*/
	num = (fsize % gsize) / MMAP_SIZE;/*非最大组的进程组进程个数*/
	other = fsize % MMAP_SIZE;/*不足一个进程映射大小的字节数目*/
	
	printf("%d\t%d\n", time, num);
	
	while(time - n){/*如达不到进程上限，time为0直接就退出,如能达到上线，就需多次创建进程组并回收*/
		m = 0;/*已创建子进程个数每次重新创建进程组都需要重新赋0*/
		while(DFL_PROC_NUM - m){//创建进程个数达到上线结束创建
			fork_mmap((n*DFL_PROC_NUM + m)*MMAP_SIZE, oldfilepath, newfile);/*创建进程并映射处理*/
			m++;/*进程数加1*/
		}
		n++;
		recovery_process_resource();/*回收进程*/
	}
	
	max = n * m * MMAP_SIZE;
	m = 0;
	while(num - m){
		fork_mmap(max + m * MMAP_SIZE, oldfilepath, newfile);
		m++;
	}	
	if(other != 0)
		fork_mmap(max + m * MMAP_SIZE, oldfilepath, newfile);

	recovery_process_resource();
}

void recovery_process_resource(void)
{
	pid_t gid = getpid();
	int ret;
	while(1)
		if((ret = waitpid(-gid, NULL, WCONTINUED)) == -1)
			break;
}
void fork_mmap(const int whence, const char * oldfilepath, const char * newfile)
{
	pid_t pid = fork();
	if(pid < 0)
		sys_err("fork");
	if(pid == 0){
		int point = 0, fdnew, fdold;
		if((fdold = open(oldfilepath, O_RDONLY)) < 0)/*打开源文件*/
			sys_err("open oldfile");
		if((fdnew = open(newfile, O_RDWR)) < 0)/*打开空文件*/
			sys_err("open newfile");
	
		char * addrnew = NULL, *addrold = NULL;
		mmap_file_memory(whence, fdnew, PROT_READ|PROT_WRITE, MAP_SHARED, &addrnew);
		mmap_file_memory(whence, fdold, PROT_READ, MAP_PRIVATE, &addrold);
	
		while(point < MMAP_SIZE){
			addrnew[point] = addrold[point];
			point++;
		}
		munmap(addrnew, MMAP_SIZE);
		munmap(addrold, MMAP_SIZE);
		
		exit(EXIT_SUCCESS);
	}
}

void mmap_file_memory(const int whence,const int fd, const int prot, const int flags, char ** addr)
{
		*addr = mmap(NULL, MMAP_SIZE, prot, flags, fd, whence);
		if(*addr == MAP_FAILED)
			sys_err("mmap");
		close(fd);
}
