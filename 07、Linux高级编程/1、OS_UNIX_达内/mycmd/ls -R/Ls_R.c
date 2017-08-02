#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

void error_print(const char * ptr){
	perror(ptr);
	exit(EXIT_FAILURE);
}
void print_dir(const char * pathname,const char * point){
	DIR * opdir = opendir(pathname);
	if(opdir == NULL)
		error_print("opendir");
	struct dirent * redir;
	while(redir = readdir(opdir)){
		if((strcmp(redir->d_name,".") == 0) || (strcmp(redir->d_name,"..") == 0)){
			//printf("%s(%d)\n",redir->d_name,redir->d_type);
			continue;
		}
		if((point == "-r") && (redir->d_type == 4)){
			printf("\n%s(%d):\n",redir->d_name,redir->d_type);
			chdir(pathname);/*strcat() also can do it*/
			print_dir(redir->d_name,"-r");
		}
		else
			printf("  %s(%d)  ",redir->d_name,redir->d_type);
	}
	closedir(opdir);
}
int main(char argc,char ** argv){
	if(argc<=1)
		error_print("Too few parameters in function calls\n");
	else if(argc == 2)
		print_dir(argv[1],"^");
	else if((argc == 3) && (strcmp(argv[1],"-r") == 0))
		print_dir(argv[2],"-r");

	printf("\n");
	return 0;
}
