# include <stdio.h>
# include <string.h>

struct Student
{
	int sid;
	char name[100];
	int age;
};
int main (void)
{
	struct Student st={100,"zhangsan",20};
	printf("%d  %s  %d\n",st.sid,st.name,st.age);

	st.sid = 99;
	//st.name = "lisi";//error,不能这样给字符串赋值
	strcpy(st.name,"lisi");//strcpy()函数的头文件为# include <string.h>
	st.age = 19;
	printf("%d  %s  %d\n",st.sid,st.name,st.age);

	return 0;
}

