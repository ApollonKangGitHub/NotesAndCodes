#include "test.h"

struct operation ops = {
	.init_node = create,
	.modify = insert,
	.print = show,
};

int main()
{
	Node* head = NULL;

	
	head = ops.init_node(head, 12);
	head = ops.init_node(head, 102);
	head = ops.init_node(head, 32);
	head = ops.init_node(head, 42);
	head = ops.init_node(head, 19);
	ops.print(head);
	ops.modify(head, 100, 12);
	ops.print(head);

	return 0;
}


