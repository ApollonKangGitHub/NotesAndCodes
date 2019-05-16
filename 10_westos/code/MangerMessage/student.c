# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>

# define PRINT1 "***********************************************************************\n"


typedef struct Information{
	char math[8];
	char chinese[8];
	char english[8];
	char name[15];
	char number[10];
	char sex[5];
	char age[3];
	struct Information * pNext;
}INFOR;

void user_login(const char *, const char *);
void user_choose_interface(void);
void quit_interface(void);
void user_interface(void);
INFOR * logging_message(void);
void show_message(INFOR *);
int main(void)
{
	user_choose_interface();
	
	return 0;
}

void user_choose_interface(void)
{
	int choice;
	system("clear");
	printf(PRINT1);
	printf("Wlcome To Student Information Management System!\n\n");
	printf("1.Enter User Of Teacher Home\n");
	printf("2.Quit System\n\n");
	printf(PRINT1);
	scanf("%d",&choice);

	switch(choice)
	{
		case 1:system("clear");
			user_interface();
			break;
		case 2:quit_interface();
			exit(EXIT_FAILURE);
			break;
		default:printf("Input Error,Please input your choose again(1~2):\n");
			break;
	}
}
void quit_interface(void)
{
	printf("Quit...\n");
	sleep(1);
	printf("Quit Is Success!\n");
	sleep(1);
}
void user_interface(void)
{
	int choice;
	INFOR * pHead = NULL;

	printf(PRINT1);
	printf("Welcome To User Of Teacher Home!\n\n");
	printf("1.列出所有学生信息\n");
	printf("2.录入学生信息\n");
	printf("3.插入学生信息");
	printf("4.根据学籍号删除学生\n");
	printf("5.根据学生姓名删除学生\n");
	printf("6.根据学好查询学生\n");
	printf("0.退出用户界面\n\n");
	printf(PRINT1);

	printf("Please input your choose:\n");
	scanf("%d",&choice);

	switch(choice)
	{
		case 1://show_message(pHead);
			break;
		case 2:pHead = logging_message();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 0:quit_interface();
			user_choose_interface();
			break;
		default:printf("Input Error,Please input your choose again(1~3):\n");
			break;
	}
}

INFOR * logging_message(void)
{
	int choice = 1;
	INFOR * pHead = NULL;
	INFOR * pNew = NULL;
	FILE * fp = fopen("student.txt","rw+");
	if(NULL == fp){
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while(choice)
	{
		system("clear");
		pNew = (INFOR *)malloc(sizeof(INFOR));
		if(NULL == pNew){
			printf("内存分配失败，无法录入成绩！\n");
			exit(EXIT_FAILURE);
		}
		memset(pNew,0,sizeof(INFOR));
#if 1		
		printf("请输入学生姓名：");
		scanf("%s",pNew->name);
		printf("请输入学生年龄：");
		scanf("%s",pNew->age);
		printf("请输入学生性别：");
		scanf("%s",pNew->sex);
		printf("请输入学生学号：");
		scanf("%s",pNew->number);
		printf("请输入学生数学成绩：");
		scanf("%s",pNew->math);
		printf("请输入学生语文成绩：");
		scanf("%s",pNew->chinese);
		printf("请输入学生英语成绩：");
		scanf("%s",pNew->english);
#endif		
		pNew->pNext = pHead;
		pHead = pNew;
	
		if(0 == fwrite(pNew,1,sizeof(INFOR),fp)){
			perror("fwrite");
			exit(EXIT_FAILURE);
		}
		
		printf("继续录入？是选1，否选0：");
		scanf("%d",&choice);
	}
	fflush(fp);	
	if(fclose(fp)){
		perror("fclose");
		exit(EXIT_FAILURE);
	}

	user_interface();
	return pHead;
}

void show_message(INFOR * pHead)
{
	FILE * fp = fopen("student.txt","r");
	if(fp){
		printf("fopen");
		exit(EXIT_FAILURE);
	}
	
	char * read[sizeof(INFOR)];
	while(fp){
		memset(read,0,sizeof(INFOR));
		gets(read,sizeof(INFOR),fp);
		
		INFOR * pRead = (INFOR *)read;

		printf("%s\n",pRead->name);
		printf("%s\n",pRead->number);
		printf("%s\n",pRead->sex);
		printf("%s\n",pRead->age);
		printf("%s\n",pRead->math);
		printf("%s\n",pRead->chinese);
		printf("%s\n",pRead->english);
	}

	fflush(fp);
	fclose(fp);
#if 0
	INFOR * pRead = pHead;
	printf("%s\n",pRead->name);
	printf("%s\n",pRead->number);
	printf("%s\n",pRead->sex);
	printf("%s\n",pRead->age);
	printf("%s\n",pRead->math);
	printf("%s\n",pRead->chinese);
	printf("%s\n",pRead->english);
#endif

}








