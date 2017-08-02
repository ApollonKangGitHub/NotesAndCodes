#include <stdio.h>

struct node{
	int data;
	struct node* tmp;
};

int main()
{
	struct node n;
	struct node n1;
	struct node n2;

	n.data = 200;
	n.tmp = &n1;

	n1.data = 300;
	n1.tmp = &n2;

	n2.data = 400;
	n2.tmp = NULL;

	printf("data: %d\n", n.data);	
	printf("data: %d\n", (n.tmp)->data);	
	printf("data: %d\n", (n.tmp)->tmp->data);	

	return 0;
}





