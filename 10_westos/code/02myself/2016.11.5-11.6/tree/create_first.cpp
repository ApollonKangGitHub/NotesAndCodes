#include<stdio.h>
#include<stdlib.h>

typedef struct BinaryTree{
	char data;
	struct BinaryTree * pLeft;
	struct BinaryTree * pRight;
}BTREE;

void pre_create(BTREE **);
void pre_traversal(BTREE *);
void mid_traversal(BTREE *);
void after_traversal(BTREE *);
int deep_tree(BTREE *);
int count_leave(BTREE *);

int main(void)
{
	BTREE * pRoot;
	pre_create(&pRoot);
	printf("���������");
	pre_traversal(pRoot);
	printf("\n���������");
	mid_traversal(pRoot);
	printf("\n���������");
	after_traversal(pRoot);
	
	int deep = deep_tree(pRoot);
	printf("\n�������Ϊ��%d",deep);
	int count = count_leave(pRoot);
	printf("\nҶ�ӽڵ����Ϊ��%d\n",count);
	return 0;
}

void pre_create(BTREE ** pRoot)
{
	char num;
	scanf("%c",&num);
	if(num == '^'){
		*pRoot = NULL;
	}
	else{
		*pRoot = (BTREE *)malloc(sizeof(BTREE));
		(*pRoot)->data = num;
		pre_create(&((*pRoot)->pLeft));
		pre_create(&((*pRoot)->pRight));
	}
}
void pre_traversal(BTREE * pRoot)
{
	if(pRoot == NULL){
		return;
	}
	else{
		printf("%-4c",pRoot->data);
		pre_traversal(pRoot->pLeft);
		pre_traversal(pRoot->pRight);
	}
}

void mid_traversal(BTREE * pRoot)
{
	if(pRoot == NULL){
		return;
	}
	else{
		mid_traversal(pRoot->pLeft);
		printf("%-4c",pRoot->data);
		mid_traversal(pRoot->pRight);
	}
}

void after_traversal(BTREE * pRoot)
{
	if(pRoot == NULL){
		return;
	}
	else{
		after_traversal(pRoot->pLeft);
		after_traversal(pRoot->pRight);
		printf("%-4c",pRoot->data);
	}
}

int deep_tree(BTREE * pRoot)
{
	if(pRoot == NULL)	
		return 0;
	else {
		int deep_left = deep_tree(pRoot->pLeft); 
		int deep_right = deep_tree(pRoot->pRight);
		
		if(deep_left > deep_right)
			return deep_left + 1;
		else 
			return deep_right + 1;
	}	
}

int count_leave(BTREE * pRoot)
{
	if(pRoot == NULL)
		return 0;
	else 	if(pRoot->pLeft == NULL && pRoot->pRight == NULL)
			return 1;
		else 
			return (count_leave(pRoot->pLeft) + count_leave(pRoot->pRight));
}


