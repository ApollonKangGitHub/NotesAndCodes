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
/*������̬���飬���뺯��*/
struct Student * CreateStudent(void)
{
	printf("���������:\n");
	char str1[20];
	gets(str1);
	printf("���ѧ���ǣ�\n");
	char str2[20];
	gets(str2);
	printf("���ǵ�������������:\n");
	char str3[20];
	gets(str3);
	printf("��������ǣ�\n");//�����䵱���ַ�������
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
/*�纯��ʹ���ڴ棬�������*/
void ShowStudent(struct Student * pst)
{
	printf("������%s\nѧ�ţ�%s\n���䣺%s\n������%s\n",pst->name,pst->sid,pst->age,pst->love);
	int i = strcmp(pst->love ,"����");//strcmp()�����ķ���ֵΪ�߼���٣�0����1�����ȽϽ����ͬ����0���٣������ͬ���ط���ֵ���棩��pst->���ܼ�"",����ᱻ�����ַ�������
	
	if(i==0)
		printf("����ɱ���\n");
	else
		printf("ף���Ҹ���\n");

	printf("%d\n",i);
}




