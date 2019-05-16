/*无未加密的文件，所有文件的查看都是加密的文件解密后查看，登录密码为:HelloRedhat*/
# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include<termios.h>
# include<unistd.h>

void decrypt_passwd(FILE *fpasswd_decrypt,char *passwd_arr);/*登录密码解密存入函数中的数组，不对外公开*/
void input_passwd(const struct termios *old);/*登录判断*/
void show();/*登录后的用户查看文件*/
void encrypt_file(FILE* fa, FILE* fb);//文件解密
void sort_file();//文件排序
void error();//出错信息显示

void error()
{
	perror("open err！\n");
	exit(EXIT_FAILURE);
}

void decrypt_passwd(FILE *fpasswd_decrypt,char *passwd_arr)
{
	char ch;
	int i=0;
	while((ch = fgetc(fpasswd_decrypt)) != EOF)
	{
		ch = ~ch;
		ch = ch-1;
		ch = ~ch;
		passwd_arr[i] = ch;
		i++;
	}
}
void input_passwd(const struct termios *old)
{
	FILE *fpasswd_decrypt = fopen("passwd_decrypt.txt","r");
	if(NULL == fpasswd_decrypt)	error();
	char passwd_arr[20] = {0};
	char passwd_input[20] = {0};
	int i = 0;
	int passwd;

	decrypt_passwd(fpasswd_decrypt,passwd_arr);
	while( (passwd = strncmp(passwd_arr,passwd_input,strlen(passwd_arr))) && (3-i))
	{
		printf("You have %d times opportunity to input，Please input your passwd：\n",3-i);
		memset(passwd_input, 0, 20);
		fgets(passwd_input, 20, stdin);
		i++;
	}
	//printf("passwd_arr:%s\n",passwd_arr);
	//printf("passwd_input:%s\n",passwd_input);
	
	tcsetattr(0, TCSANOW, old);/*传过来的是old的地址，故无需再取地址*/
	if(passwd != 0)
	{
		printf("Your passwd not right，exit!\n");
		exit(EXIT_FAILURE);
	}
}

void decrypt_file(FILE* fb, FILE* fc)
{
	char ch;
	while( (ch = fgetc(fb)) != EOF){
		ch = ~ch;
		ch = ch - 1;
		fputc(ch, fc);
	}
}

void show()
{
	//没有加密的file_a.txt源文件已经删除
	FILE *fb = fopen("file_b.txt", "r");	
	if(fb == NULL)
		error();
	FILE *fc = fopen("file_c.txt", "w");	
	if(fc == NULL)
		error();
	decrypt_file(fb, fc);
	
	//sort_file(fc)；
	fclose(fb);
	fclose(fc);

	system("cat file_c.txt");//查看解密后的文件file_c.txt
	system("rm -rf file_c.txt");//查看完成之后自行删除生成的解密文件file_c.txt
}
int main(void)
{
	struct termios old,new;
	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &new);

	input_passwd(&old);//输入密码与解密后的系统密码比较，相同则登录
	show();

	return 0;
}
