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
	/*�ṹ�帳ֵ�ĵ�һ�ַ��������Ƽ���*/
	struct Student st={100,"zhangsan",20};
	printf("%d  %s  %d\n",st.sid,st.name,st.age);

	/*�ṹ�帳ֵ�ĵڶ��ַ���*/
	st.sid = 99;
	//st.name = "lisi";//error,�����������ַ�����ֵ
	strcpy(st.name,"lisi");//strcpy()������ͷ�ļ�Ϊ# include <string.h>
	st.age = 19;
	printf("%d  %s  %d\n",st.sid,st.name,st.age);

	/*�ṹ�帳ֵ�ĵ����ַ�������ã������׳���*/
	struct Student * pst;
	pst = &st;

	pst->sid =102;//pst->sid�ȼ���(*pst).sid�ȼ���st.sid
	strcpy(pst->name,"wangwu");
	pst->age = 21;
	printf("%d  %s  %d\n\n",pst->sid,pst->name,pst->age);

	printf("pst��ռ�ڴ�=%d\n",sizeof(struct Student *));
	printf("�ṹ����ռ�ڴ�=%d\n\n",sizeof(struct Student));

	return 0;
}

