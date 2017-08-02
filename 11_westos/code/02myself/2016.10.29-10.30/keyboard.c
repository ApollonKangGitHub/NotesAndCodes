#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

struct termios tcsave;
int flsave;

#define UP    0x415b1b
#define DOWN  0x425b1b
#define LEFT  0x445b1b
#define RIGHT 0x435b1b
#define ENTER 0xa
#define ESC   0x1b
#define SPACE 0x20

int init_keyboard(void)//不回显，且输入之后立即生效
{
	int ret;
	struct termios tc;
	ret = tcgetattr(0, &tcsave);
	if(ret < 0)
		return -1;
	tc = tcsave;
	tc.c_lflag &= ~(ECHO|ICANON);
	ret = tcsetattr(0, TCSANOW, &tc);
	if(ret < 0)
		return -1;
	flsave = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, flsave|O_NONBLOCK);
	return 0;
}
void recover_keyboard(void)
{
	tcsetattr(0, TCSANOW, &tcsave);
	fcntl(0, F_SETFL, flsave);
}
int get_key(void)//获取键盘敲击键是何种键的核心
{	
	unsigned char buf[3];

	int ret = read(0, buf, sizeof(buf));
	if(ret < 0)
		return -1;
	
	int i = 0, key = 0;
	for(i=0; i<ret; i++)
		key += (buf[i]<<(i*8));
	}
	return key;
}
int is_up(int key)
{	
	return key == UP;
}
int is_down(int key)
{	
	return key == DOWN;
}
int is_left(int key)
{	
	return key == LEFT;
}
int is_right(int key)
{	
	return key == RIGHT;
}
int is_enter(int key)	
{
	return key == ENTER;
}
int is_esc(int key)
{	
	return key == ESC;
}
int is_space(int key)
{
	return key == SPACE;
}


#if 1
int main(void)
{
	int key, ret;
	ret = init_keyboard();
	if(ret < 0)
		return -1;
	while(1){
		key = get_key();
		if(key < 0)
			continue;	

		//printf("key = %x\n", key);
		if(is_left(key))
			printf("left\n");
		if(is_right(key))
			printf("right\n");
		if(is_up(key))
			printf("up\n");
		if(is_down(key))
			printf("down\n");
		if(is_enter(key))
			printf("enter\n");
		if(is_space(key))
			printf("space\n");
		if(is_esc(key)){
			printf("esc\n");
			break;
		}
		
		if(key == 'q')
			break;
	}	
	recover_keyboard();
	return 0;
}
#endif




