# include <stdio.h>
typedef struct Student 
{
	int sid;
	char name[100];
	char sex;
}ST;

int main (void)
{
	ST st;//�ȼ��� struct Student st
	struct Student * ps;//�ȼ��� ST * ps

	st.sid = 100;
	printf("%d\n",st.sid);

	return 0;
}