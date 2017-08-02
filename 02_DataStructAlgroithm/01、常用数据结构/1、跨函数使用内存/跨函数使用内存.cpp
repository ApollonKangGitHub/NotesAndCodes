# include <stdio.h>
# include <malloc.h>
# include <string.h>
# include <stdlib.h>

struct Student
{
	char sid[10];
	char age[10];
	char name[20];
	char love[20];
};

struct Student * CreateStudent(void);
void ShowStudent(struct Student * pst);

int main(void)
{
	struct Student * pst;

	pst = CreateStudent();
	ShowStudent(pst);

	return 0;
}
/*创建动态数组，输入函数*/
struct Student * CreateStudent(void)
{
	printf("你的姓名是:\n");
	char str1[20];
	gets(str1);
	printf("你的学号是：\n");
	char str2[20];
	gets(str2);
	printf("你是单身狗还是恋爱中:\n");
	char str3[20];
	gets(str3);
	printf("你的年龄是：\n");//将年龄当做字符串处理
	char str4[10];
	gets(str4);


	system("cls");

	struct Student * pst = (struct Student*)malloc(sizeof(struct Student));

	strcpy(pst->sid,str2);
	strcpy(pst->age ,str4);
	strcpy(pst->name,str1);
	strcpy(pst->love,str3);

	return pst;
}
/*跨函数使用内存，输出函数*/
void ShowStudent(struct Student * pst)
{
	printf("姓名：%s\n学号：%s\n年龄：%s\n恋爱否：%s\n",pst->name,pst->sid,pst->age,pst->love);
	int i = strcmp(pst->love ,"单身狗");//strcmp()函数的返回值为逻辑真假（0或者1），比较结果相同返回0（假）结果不同返回非零值（真），pst->不能加"",否则会被当作字符串处理。
	
	if(i==0)
		printf("你真可悲！\n");
	else
		printf("祝你幸福！\n");

	printf("%d\n",i);
}




