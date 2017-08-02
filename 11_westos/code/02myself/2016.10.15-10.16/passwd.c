# include<stdio.h>
# include<termios.h>
# include<string.h>
# include<unistd.h>

# define true 1
int main(void)
{
	struct termios old,new;
	tcgetattr(0,&old);
	new = old;
	new.c_lflag &= ~(ECHO|ICANON);

	char passwd_stdin[20]={0};
	char passwd_true[]="hello";
	char ch;
	int i=0;
	int point = true;

	while(point)
	{
		tcsetattr(0, TCSANOW, &new);
		scanf("%c",&ch);
		tcsetattr(0, TCSANOW, &old);
		if(ch == '\n')
			break;
		passwd_stdin[i] = ch;

		printf("*");
		i++;
	}
	if(!strcmp(passwd_stdin,passwd_true)){
		printf("密码正确!\n");
		system("cat passwd.c");
	}
	else{
		printf("密码错误!\n");
		//system("shutdown -h now");
	}
	return 0;
}
