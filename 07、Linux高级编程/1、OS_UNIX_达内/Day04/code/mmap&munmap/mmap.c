#include<stdio.h>
#include<sys/mman.h>
#include<unistd.h>
#include<string.h>

#define MAX 20
typedef struct Staff_message{
	char * name;
	char * id;
	float salary;
}STAME;

int main (void)
{
	STAME * pStame = (STAME *)mmap(0,sizeof(STAME),PROT_WRITE|PROT_READ|PROT_EXEC,MAP_PRIVATE|MAP_ANONYMOUS,0,0);
	if(pStame ==  MAP_FAILED){
		perror("mmap");
	}
	/*must init is NULL,else field point*/
	pStame->name = NULL;
	pStame->id = NULL;

	pStame->name = "kanguojin";
	pStame->id = "05148139";
	/*
	* array mode: 
	* char name[MAX];
	* char id[MAX];
	*strcpy(pStame->name,"kangruojin");
	*strcpy(pStame->id,"05148139");
	*/
	pStame->salary = 8888.888;

	printf("name:%s\n",pStame->name);
	printf("id:%s\n",pStame->id);
	printf("salary:%f\n",pStame->salary);

	munmap(pStame,sizeof(STAME));
	return 0;
}
