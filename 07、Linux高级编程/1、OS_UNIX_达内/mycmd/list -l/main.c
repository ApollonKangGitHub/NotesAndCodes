/*
 * 函数功能：ls -l pathname
 * 时间：2017/1/24--19时05分57秒
 * 局限性：不能模糊匹配，不能使用正则，且只能判断普通文件与目录
 *
 * */

#include<myls.h>

int main(char argc,char ** argv)
{
	if(argc != 3){
		printf("Too few parameter!");
		exit(EXIT_FAILURE);
	}

	if((argc == 3) && !(strcmp(argv[1],"-l"))){/*判断是myls -l argv[2]格式*/
		struct stat get_message = {};
		int ret_stat = stat(argv[2],&get_message);
		if(ret_stat == -1)
			error("stat %s",argv[2]);

		if(S_ISDIR(get_message.st_mode))/*判断是否是目录，是目录则进一步处理目录中个文件*/
			mylist_dir(argv[2]);
		else/*不是目录则直接处理普通文件*/
			list_message(argv[2],&get_message);	/*文件stat信息输出函数*/
	}
	else{
		printf("error in main!\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
