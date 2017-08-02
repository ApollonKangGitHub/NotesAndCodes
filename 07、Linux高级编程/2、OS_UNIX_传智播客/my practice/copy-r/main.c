/******
*时间：2017/2/18-19:57
*功能：实现简单的目录文件拷贝
*限定测试格式：mycp -r source target
*局限性：不能使用正则，功能有限
******/

#include<copy.h>
int main(int argc, char ** argv){
	if(argc != 4){
		printf("too few or lost parameter!\n");
		exit(EXIT_FAILURE);
	}
	else if(!strcmp(argv[1], "-r") || !strcmp(argv[1], "-R")){
		struct stat get_message;
		int ret_stat = stat(argv[2],&get_message);
		if(ret_stat == -1)
			sys_err("stat argv[2]");

		if(S_ISDIR(get_message.st_mode))
			deal_dir(argv[2],argv[3]);//如果argv[2]是目录则按目录递归处理
		else{//否则按照文件直接复制,局限性：复制单个文件时只能向当前目录复制
			if(strcmp(argv[2],argv[3]) == 0){
				printf("The same filename of parameter is error!\n");
				exit(EXIT_FAILURE);
			}
			deal_copy(argv[2],argv[3]);
		}
	}
	
	return 0;
}
