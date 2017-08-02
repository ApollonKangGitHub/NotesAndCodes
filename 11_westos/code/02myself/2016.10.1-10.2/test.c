# include<stdio.h>
# include<stdlib.h>

#pragma pack(2)//默认为4，参数为2表示按2两个字节对齐。而不是默认的32位机的按照四位对齐

struct person
{
	int age;
	char * name;
	long long id;
};

struct node
{
	char h;
	int p;
	double k;
	int m;
};
int main (void)
{
	struct person jim = {
		20,"jim",1232323
	};
	printf("%d\t%s\t%ld\n",jim.age,jim.name,jim.id);
	printf("%d\n",sizeof(struct node));
	return 0;
}
