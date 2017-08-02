# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<fcntl.h>

# define BUF_SIZE 10
int main(void)
{
	int fd = open("a.txt",O_RDONLY,0666);
	if(fd == -1){
		perror("open a.txt");
		exit(EXIT_FAILURE);
	}

	char buffer[BUF_SIZE] = {0};
	int fd2 = open("b.txt",O_CREAT|O_RDWR|O_TRUNC,0666);
	if(fd2 == -1){
		perror("open b.txt");
		exit(EXIT_FAILURE);
	}

	while(1){
		int res = read(fd,buffer,sizeof(buffer));
		if(res <= 0)
			break;
		write(fd2,buffer,res);
	}
	if(close(fd) == -1 && !close(fd2) == -1){
		perror("close");
	}
	return 0;
}
