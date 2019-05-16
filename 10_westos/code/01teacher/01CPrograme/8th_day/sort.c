#include <stdio.h>

#define	N	10

struct sort{
	int *arr;
	void (*pinsert)(int*, int);
	void (*pshow)(int*, int);
	void (*pchoose)(int*, int);
};

void choose(int* pa, int len)
{
	int i, j, k;
	for(i=0; i<len-1; i++){
		k = i;
		for(j=i+1; j<len; j++){
			if(*(pa + k) > *(pa + j)){
				k = j;		
			}
		}
		int  t = *(pa + k);
		*(pa + k) = *(pa + i);
		*(pa + i) = t;
#if 0
//	if(k-i){
		(*(pa + i)) = (*(pa + i)) + (*(pa + k));
		printf("k + i: %d\t", *(pa + i));
		(*(pa + k)) = (*(pa + i)) - (*(pa + k));
		printf("k: %d\t", *(pa + k));
		(*(pa + i)) = (*(pa + i)) - (*(pa + k));
		printf("i: %d\t", *(pa + i));
		printf("*********************************************\n");
//	}
#endif
	}
}
void insert(int* pa, int len)
{
	int i=0, j = 0, tmp = 0;
	for(i=1; i<len; i++){
		tmp = *(pa + i);
		for(j=i-1; j>=0 && tmp < *(pa + j); j--)
			*(pa + j + 1) = *(pa + j);
		*(pa + j + 1) = tmp;
	}
}
void show(int *pa, int len)
{
	int i  = 0;
	for(i=0; i<len; i++)	
		printf("%d\t", *(pa + i));
	printf("\n");
} 
int main()
{
	struct sort method = {
		.pinsert = insert,
		.pshow = show,
		.pchoose = choose,
	};

	int a[N] = {-1, 23, 9, 12, 0, 3, 8, -3, 4, 0};	
	int b[11] = {1, 2, 9, 12, 10, 3, 8, -3, 4, 0, 100};	

#if 1
	method.arr = a;
	method.pinsert(method.arr, 10);	
	method.pshow(method.arr, 10);
	method.arr = b;
	method.pchoose(b, 11);
	method.pshow(b, 11);
#endif
	return 0;	
}











