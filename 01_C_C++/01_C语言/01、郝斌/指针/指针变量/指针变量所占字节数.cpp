# include <stdio.h>

int main (void)
{

	double arr[3]={1.1,2.2,3.3};
	double * p = arr;
	double * q = arr+1;
	double * r = arr+2;

	printf("%d  %d  %d\n",sizeof(int *),sizeof(double *),sizeof(char *));
	printf("%d  %d  %d\n",sizeof(int **),sizeof(double **),sizeof(char **));
	printf("%d  %d  %d\n",sizeof(int ***),sizeof(double ***),sizeof(char ***));
	printf("%p  %p  %p\n",p,q,r);

	return 0;
}