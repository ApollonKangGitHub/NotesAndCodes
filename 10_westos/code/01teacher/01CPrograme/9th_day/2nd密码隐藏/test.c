#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>

int main()
{
	struct termios old, new;

	tcgetattr(0, &old);		
	new = old;

	new.c_lflag &= ~( ECHO | ICANON);

	tcsetattr(0,  TCSANOW ,&new);	

	char buf[20] = {0};
	

	while( (strncmp("redhat", buf, 6))){
		memset(buf, 0, 20);
		fgets(buf, 20, stdin);	
	}
	printf("buf: %s\n", buf);	

	tcsetattr(0, TCSANOW, &old);
	
	return 0;
}










