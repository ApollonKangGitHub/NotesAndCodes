#ifndef __TEST_H
#define __TEST_H

#include <stdio.h>
#include <stdlib.h>

typedef	struct node{
	int data;
	struct node* next;
	struct node* pre;
}Node;

struct operation {
	struct node* (*init_node)(struct node*, int);
	void (*modify)(struct node*, int, int);
	void (*print)(struct node*);
};

Node* create(Node*, int);
void show(Node*);
void insert(Node*, int, int);


#endif





