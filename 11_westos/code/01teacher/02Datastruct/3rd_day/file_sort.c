#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

	FILE *fa,*fb;
	char *ps[4]={"hello\n","hrold\n","hood\n", "bye\n"};
	
	fa=fopen("sort.txt","w");
	if(fa == NULL){
		perror("Open failure\n");
		exit(EXIT_FAILURE);
	}
	int i = 0,j = 0;
	for(i = 0; i < 4; i++)
		fputs(*(ps+i), fa);
	fclose(fa);

	char arr[4][7] = {0};

	fa=fopen("sort.txt","r");
	if(fa == NULL){
		perror("Open failure\n");
		exit(EXIT_FAILURE);
	}
	for(i = 0;i < 4; i++ )
		fgets(arr[i], 7, fa);
	fclose(fa);

	char *pa[4] = {NULL};
	for(i = 0; i < 4; i++){
		pa[i] = arr[i];
	}

	char **p2 = pa;
	char *tmp = NULL;
	for(i = 0; i < 4; i++){
		for(j=i+1; j<4; j++){
			if(1 == strcmp( *(pa+i), *(pa+j))){
				tmp = *(pa+i);
				*(pa+i) = *(pa+j);
				*(pa+j) = tmp;
			}
		}
			
	}
	
	fb = fopen("after.txt", "w+");
	if(fb == NULL){
		perror("Open failure\n");
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < 4; i++)
		fputs(pa[i], fb);
	
	fclose(fb);
}




















