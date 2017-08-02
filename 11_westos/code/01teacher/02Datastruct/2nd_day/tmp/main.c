#include "test.h"

#if 0
struct b{
	int data;
	char* name;
};


struct a{
	char b;
	float c;
	struct b bb;
};
//-----------------------------------------------
struct a dd = {
	struct b  bb = {
		.data = 100,
		.name = "struct b";
	},
	.b = 'x',
	.c = 3.14,	
};
#endif

Ops list = {
	.print = show,
	.init = create,
	.insert = pre_insert,
};

int main()
{
	Node* head = NULL;
		
	head = list.init(head, 400);
	list.init(head, 200);
	list.init(head, 100);
	list.init(head, 300);
	list.init(head, 33);
	list.init(head, 43);
	list.print(head);
	
	head = list.insert(head, 55, 400);
	list.print(head);

	return 0;
}

