/*
2016/10/30--15:11:58
*/
#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

/*键盘部分键的buffer值*/
#define UP    0x415b1b
#define DOWN  0x425b1b
#define LEFT  0x445b1b
#define RIGHT 0x435b1b

/*蛇及蛋的一些参数*/
#define WIDTH 15		//蛇和蛋的节点宽度
#define WIDTH_WALL 5		//边界墙的厚度
#define BETWEEN 2		//蛇身每个节点之间的空隙宽度
#define LEFT_CHEEK 105		//左边内边框列数
#define RIGHT_CHEEK 1300	//右边内边框列数
#define UP_CHEEK 105		//上边内边框行数
#define DOWN_CHEEK 700		//下边边框行数
#define XRES 1376		//每行像素数
#define EASY 200000		//低难度延时微秒数
#define HARD 100000		//中难度延时微秒数
#define VERY_HARD 50000		//高难度延时微秒数

#define	 RGB888(r, g, b)     ((0XFF & r) << 16 | (0XFF & g) << 8 | (b & 0XFF))	//为一个像素填充RGB888格式的颜色

/*蛇及蛋的节点结构体*/
typedef struct Snake_Node{
	struct Snake_Node * pNext;
	struct Snake_Node * pPre;
	int x;//节点x坐标
	int y;//节点y坐标
}SNAKE;

/*获取本机显卡的参数全局变量*/
struct termios tcsave;
int flsave;

int InitKeyBoard(void);			//屏幕设置为不回显，且键盘输入无需按回车而立即生效
void RecoverKeyBoard(void);		//恢复系统默认设置
int GetKey(void);			//获取输入的键盘键值
void LoveEatSnake(unsigned long *);	//游戏启动主函数
int TroubleChoose(void);		//难度选择
void CreateCheek(unsigned long *);	//游戏界面边框初始化
SNAKE * NewNode(int, int);		//创建并初始化新节点
int FillColor(unsigned long *, SNAKE *);//将节点颜色填充
SNAKE * NewEgg(unsigned long *);	//随机生成新的蛋
SNAKE * NewSnake(unsigned long * addr);	//创建新的一条小蛇
SNAKE * Move(SNAKE *,int);		//将尾节点移至为头节点
SNAKE * EatEggSuccess(SNAKE *,SNAKE *);	//吃蛋成功时的处理函数
void GameOver(unsigned long *);		//GAME OVER 输出
int CollideBody(SNAKE *);		//碰到身体死

int main(void)
{
	struct fb_var_screeninfo  vinfo;

	int fd = open("/dev/fb0", O_RDWR);
	if(fd < 0){
		perror("open err. \n");
		exit(EXIT_FAILURE);
	}
	int ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
	if(ret < 0){
		perror("ioctl err. \n");
		exit(EXIT_FAILURE);
	}
	printf("%d\n%d\n%d\n",vinfo.xres,vinfo.yres,vinfo.bits_per_pixel);	
	unsigned long * addr = mmap(NULL, (vinfo.xres*vinfo.yres*vinfo.bits_per_pixel)>>3, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//	LoveEatSnake(addr);
//	GameOver(addr);
	
	return 0;
}

int InitKeyBoard(void)
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
void RecoverKeyBoard(void)
{
	tcsetattr(0, TCSANOW, &tcsave);
	fcntl(0, F_SETFL, flsave);
}
int GetKey(void)
{	
	unsigned char buf[3];

	int ret = read(0, buf, sizeof(buf));
	if(ret < 0)
		return -1;
	
	int i = 0, key = 0;
	for(i=0; i<ret; i++)
		key += (buf[i]<<(i*8));

	return key;
}

void LoveEatSnake(unsigned long * addr)
{
	int key = 0, ret = 0, distance = 0, point = LEFT, trouble = 0;
	system("clear");
	trouble = TroubleChoose();
	
	CreateCheek(addr);
	SNAKE * pNewEgg = NewEgg(addr);
	SNAKE * pHead = NewSnake(addr);
	ret = InitKeyBoard();

	/*碰墙死*/
	while((pHead->y < DOWN_CHEEK - WIDTH - BETWEEN) && (pHead->y > UP_CHEEK) && (pHead->x > LEFT_CHEEK) && (pHead->x < RIGHT_CHEEK - WIDTH - BETWEEN))
	{
		system("clear");
			CreateCheek(addr);/*窗口格式化*/
		
		distance = pow(pNewEgg->x - pHead->x, 2) + pow(pNewEgg->y - pHead->y, 2);/*判断是否撞到边界*/
		if(distance < pow(WIDTH,2) ){
			pHead = EatEggSuccess(pHead,pNewEgg);
			pNewEgg = NewEgg(addr);
		}/*判断吃蛋是否成功*/

		key = GetKey();
		/*若键盘输入方向和当前运动方向相反，则point不变，继续保持*/
		if((key > 0) && ((point==LEFT && key!=RIGHT) || (point==RIGHT && key!=LEFT) || (point==UP && key!=DOWN) || (point==DOWN && key!=UP)))
				point = key;

		pHead = Move(pHead, point);/*蛇移动一次*/
		FillColor(addr, pNewEgg);/*为蛋填充颜色*/
		FillColor(addr, pHead);/*为蛇填充颜色*/
		if(CollideBody(pHead) == 0)/*如果碰到自己身体，游戏结束*/
			break;	
		usleep(trouble);/*睡眠trouble微秒*/
	}
	
	RecoverKeyBoard();/*恢复系统默认显示*/
}
int TroubleChoose(void)
{
	int trouble,choose;
	printf("Please choose degree of difficulty:\n1.easy\n2.hard\n3.very hard\n");
	scanf("%d",&choose);
	switch(choose){
		case 1:
			trouble = EASY;
			break;
		case 2:
			trouble = HARD;
			break;
		case 3:
			trouble = VERY_HARD;
			break;
		default:
			trouble = HARD;
			printf("error choose,set 2!");
			break;
	}
	return trouble;

}
void CreateCheek(unsigned long * addr)
{
	int i , j;
	for(i = UP_CHEEK - WIDTH_WALL; i < DOWN_CHEEK + WIDTH_WALL; i++)
		for(j = LEFT_CHEEK - WIDTH_WALL; j < LEFT_CHEEK; j=j++)
			*(addr + i*XRES + j) = RGB888(0, 0XFF,0XFF );/*画左边一竖*/
	for(i = UP_CHEEK - WIDTH_WALL; i < DOWN_CHEEK + WIDTH_WALL; i++)
		for(j = RIGHT_CHEEK; j < RIGHT_CHEEK + WIDTH_WALL; j++)
			*(addr + i*XRES + j) = RGB888(0, 0XFF, 0XFF);/*画右边一竖*/
	for(i = UP_CHEEK - WIDTH_WALL; i < UP_CHEEK; i++)
		for(j = LEFT_CHEEK; j<RIGHT_CHEEK;j++)
			*(addr + i*XRES + j) = RGB888(0, 0XFF, 0XFF);/*画上边一横*/
	for(i = DOWN_CHEEK; i < DOWN_CHEEK + WIDTH_WALL; i++)
		for(j = LEFT_CHEEK; j < RIGHT_CHEEK; j++)
			*(addr + i*XRES + j) = RGB888(0, 0XFF, 0XFF);/*画下边一横*/
}
SNAKE * NewNode(int x, int y)
{	
	SNAKE *  pNew = (SNAKE *)malloc(sizeof(SNAKE));/*为新节点分配内存*/
	
	pNew->x = x; /*设定横坐标*/
	pNew->y = y; /*设定纵坐标*/
	pNew->pNext = NULL;
	pNew->pPre = NULL;

	return pNew;
}

int FillColor(unsigned long * addr, SNAKE * pHead)
{
	int i, j;
	SNAKE * p = pHead;

	do{
		for(i = p->y; i < p->y + WIDTH; i++)
			for(j = p->x; j < p->x + WIDTH; j++)/*根据顶点坐标（p->x,p->y）与节点宽WIDTH确定填色范围*/
				*(addr + i*XRES + j) = RGB888(0XFF,0XFF,0);/*填充色为黄色*/
		p = p->pNext;
	}while(p && p != pHead);
}

SNAKE * NewEgg(unsigned long * addr)
{
	int x, y;
	srand(time(NULL));
	
	x = rand()%(RIGHT_CHEEK - LEFT_CHEEK - WIDTH) + LEFT_CHEEK;
	y = rand()%(DOWN_CHEEK - UP_CHEEK - WIDTH) + UP_CHEEK;
	SNAKE * pNew = NewNode(x, y);
	FillColor(addr,pNew);/*为“蛋”填充颜色*/
	return pNew;
}

SNAKE * NewSnake(unsigned long * addr)
{
	SNAKE * pHead = NewNode(700,411);
	SNAKE * pBody = NewNode(705,411);
	SNAKE * pTail = NewNode(710,411);/*为蛇初始化创建三个节点（蛇首、身、尾）*/
	
	pTail->pPre = pHead->pNext = pBody;
	pTail->pNext = pBody->pPre = pHead;
	pHead->pPre = pBody->pNext = pTail;/*双向链表，连接各个节点*/
	
	FillColor(addr,pHead);/*为蛇填充颜色*/
	return pHead;
}

SNAKE * Move(SNAKE * pHead, int point)
{
	pHead = pHead->pPre;
	if( point == LEFT || point == RIGHT ){
		pHead->x = (point == LEFT) ? (pHead->pNext->x - (WIDTH+BETWEEN)) : (pHead->pNext->x + (WIDTH+BETWEEN));/*左移减，右移加*/
		pHead->y = pHead->pNext->y;
	}
	if(point == UP || point == DOWN){
		pHead->y = (point == UP) ? (pHead->pNext->y - (WIDTH+BETWEEN)) : (pHead->pNext->y + (WIDTH+BETWEEN));/*上移加，下移减*/
		pHead->x = pHead->pNext->x;
	}
	return pHead;
}
SNAKE * EatEggSuccess(SNAKE * pHead,SNAKE * pNewEgg)
{	
	pNewEgg->pNext = pHead;
	pNewEgg->pPre = pHead->pPre;
	pHead->pPre->pNext = pNewEgg;
	pHead = pHead->pPre = pNewEgg;

	return pHead;
}

void GameOver(unsigned long * addr)
{
	int i = 0;

	CreateCheek(addr);
	for(i = 0;i < 30; i++)
		printf("\n");
	for(i = 0;i < 10; i++)
		printf("\t");
	printf("GAME OVER!\n\n");
	for(i = 0;i < 25; i++)
		printf("\n");
}
int CollideBody(SNAKE * pHead)
{
	SNAKE * p = pHead->pNext->pNext;
	int distance;
	while(p!=pHead){
		distance = pow(p->x - pHead->x, 2) + pow(p->y - pHead->y, 2);
		if( distance < pow(WIDTH,2) ){
			return 0;
		}
		p = p->pNext;
	}
	return 1;
}
