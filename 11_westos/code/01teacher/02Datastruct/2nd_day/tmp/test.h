#ifndef _TEST_H
#define	_TEST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct data{
	int num;
	struct data *next;	
}Node;

typedef struct operations{
	Node N_data; 
	void (*print)(Node*);
	Node* (*init)(Node*, int);
	Node* (*insert)(Node*, int, int);
}Ops;

void show(Node* phead);
Node* create(Node* phead, int d);
Node* pre_insert(Node* phead, int data, int key );

#endif  /* _TEST_H  */





