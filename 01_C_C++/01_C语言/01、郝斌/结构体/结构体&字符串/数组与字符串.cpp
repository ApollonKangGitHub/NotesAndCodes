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
	//st.name = "lisi";//error,�����������ַ�����ֵ
	strcpy(st.name,"lisi");//strcpy()������ͷ�ļ�Ϊ# include <string.h>
	st.age = 19;
	printf("%d  %s  %d\n",st.sid,st.name,st.age);

	return 0;
}

