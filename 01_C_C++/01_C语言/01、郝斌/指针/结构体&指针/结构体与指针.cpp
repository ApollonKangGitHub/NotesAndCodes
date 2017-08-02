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
	/*结构体赋值的第一种方法，不推荐！*/
	struct Student st={100,"zhangsan",20};
	printf("%d  %s  %d\n",st.sid,st.name,st.age);

	/*结构体赋值的第二种方法*/
	st.sid = 99;
	//st.name = "lisi";//error,不能这样给字符串赋值
	strcpy(st.name,"lisi");//strcpy()函数的头文件为# include <string.h>
	st.age = 19;
	printf("%d  %s  %d\n",st.sid,st.name,st.age);

	/*结构体赋值的第三种方法，最常用！不容易出错*/
	struct Student * pst;
	pst = &st;

	pst->sid =102;//pst->sid等价于(*pst).sid等价于st.sid
	strcpy(pst->name,"wangwu");
	pst->age = 21;
	printf("%d  %s  %d\n\n",pst->sid,pst->name,pst->age);

	printf("pst所占内存=%d\n",sizeof(struct Student *));
	printf("结构体所占内存=%d\n\n",sizeof(struct Student));

	return 0;
}

