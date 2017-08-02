
#include <stdio.h>

#define MAX (10000)

int ar[MAX]= {0,0,0,0};

int main()
{
    int i=0;
    for(i=0; i< MAX; i++)
        ar[i] = i;
    for(i=0; i < MAX; i++)
        printf("i=%ld\n", ar[i]);
}
