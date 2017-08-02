# include <stdio.h>

typedef struct Student 
{
	int sid;
	char name[100];
	char sex;
}* PST;//PST µÈ¼ÛÓÚstruct Student *

int main (void)
{
	struct Student st;
	PST ps = &st;

	ps->sid = 100;
	printf("%d\n",st.sid);

	return 0;
}