# include<stdio.h>
# include<string.h>

int main(void)
{
	extern char ** environ;/*environ全局变量建议不要修改*/
	char ** p = environ;/*修改局部变量*/
	/*遍历打印环境表*/
	while(*p){
		printf("%s\n",*p);
		p++;
	}

	/*找出制定环境变量并打印*/
	p = environ;
	while(*p){
		if(strncmp(*p,"PATH=",5) == 0){
			printf("\n\n\n%s\n",*p);
			break;
		}
		p++;
	}
	return 0;
}
