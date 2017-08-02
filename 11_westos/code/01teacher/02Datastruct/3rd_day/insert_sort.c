#include <stdio.h>  

void insert_sort(int *a, int len);  
void show(int *a, int len);  

int main()  
{  
    int a[7] = {1, 3, 20, 15, 7, 11, 4};  

    insert_sort(a, 7);  
//    show(a, 7);  

    return 0;  
}  
void insert_sort(int *a, int n)  
{ 	
	int i = 0; 
    for (i=1; i<n; ++i)  
    {  
        int x = a[i];  
        int j = i - 1;  
        while (j>-1 && a[j] > x)  
        {  
            a[j+1] = a[j];  
            --j;  
        }  
        a[j+1] = x;  
    }  
}  

void show(int *a, int n)  
{ 	
	int i = 0; 
	for(i=0; i<n; ++i)  
		printf("%d\n", a[i]);  
}  





















