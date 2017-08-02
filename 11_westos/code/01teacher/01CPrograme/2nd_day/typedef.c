
cd linux-2.6.35/
cd arch/
	保留 arm/  x86/,其他删除
cd linux-2.6.35/
	ctags -R ./ 
		----> tags 
vim 
	末行模式：
	: ta size_t  
	ctrl + 】   跳转关键字

typedef unsigned short	mode_t;
typedef unsigned short	nlink_t;
typedef long		off_t;
typedef int		pid_t;
typedef unsigned short	ipc_pid_t;
typedef unsigned short	uid_t;
typedef unsigned short	gid_t;
typedef unsigned int	size_t;
typedef int		ssize_t;
typedef int		ptrdiff_t;
typedef long		time_t;
typedef long		clock_t;
typedef int		timer_t;
typedef int		clockid_t;
typedef int		daddr_t;
typedef char *		caddr_t;
typedef unsigned short	uid16_t;
typedef unsigned short	gid16_t;
typedef unsigned int	uid32_t;
typedef unsigned int	gid32_t;

