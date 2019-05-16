# include<stdio.h>
# pragma pack(4)

struct node1{
	int a;
	char c;
	double d;
	int f;
	//static int e;
};

struct node2{
	int a;
	struct node1 node;
};

struct node3{};
int main(void)
{
/*
	int i = 7;
	printf("%d\n%d\n",sizeof(struct node1),sizeof(struct node2));
		t
	printf("%d\n",sizeof(i++));
	printf("%d\n",i);
*/
/*
	int i = 7;
	if(1)
	{
		static int i = 10;
		i++;
	}
	printf("%d\n",i);
*/
/*
	int * ptr = 0;
	if(ptr){}
	if(""){}
	if(''){}
	if(* ptr){}
*/
	printf("%d\n",sizeof(struct node3));
	return 0;
}
