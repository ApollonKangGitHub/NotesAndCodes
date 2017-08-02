#include <stdio.h>
#include <stdlib.h>

struct btree{
	char data;
	struct btree* lchild;
	struct btree* rchild;
};

int create(struct btree** t)
{
	char ch;
	scanf("%c", &ch);
	if(ch == '#'){
//		printf("in NULL\n");
		*t = NULL;
		return;
	}else{
		*t = malloc(sizeof(struct btree));
		(*t)->data = ch;
		create(&((*t)->lchild));
		create(&((*t)->rchild));
	}
}
int pre_visit(struct btree* bt)
{
	if(bt == NULL){
		return;
	} else {
		printf("%c  ", bt->data);
		pre_visit(bt->lchild);
		pre_visit(bt->rchild);
	}
}
int after_visit(struct btree* bt)
{
	if(bt == NULL){
		return;
	} else {
		after_visit(bt->lchild);
		after_visit(bt->rchild);
		printf("%c  ", bt->data);
	}
}
int mid_visit(struct btree* bt)
{
	if(bt == NULL){
		return;
	} else {
		mid_visit(bt->lchild);
		printf("%c  ", bt->data);
		mid_visit(bt->rchild);
	}
}
int count_leave(struct btree* bt)
{
	if(bt == NULL)
		return 0;
	else 	if(bt->lchild == NULL && bt->rchild == NULL)
			return 1;
		else 
			return (count_leave(bt->lchild) + count_leave(bt->rchild));
}
int high(struct btree* bt)
{
	if(bt == NULL)	
		return 0;
	else {
		int l = high(bt->lchild); 
		int r = high(bt->rchild);
		
		if(l > r)
			return l + 1;
		else 
			return r + 1;
	}	
}
int main()
{
	struct btree* T = NULL;	
	create(&T);
#if 0
	pre_visit(T);
	printf("\n");

	mid_visit(T);
	printf("\n");

	after_visit(T);
	printf("\n");
#endif
	int num = count_leave(T);
	printf("num: %d\n", num);

	int h = high(T);	
	printf("h: %d\n", h);
	
	return 0;
}









