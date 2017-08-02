#include <stdio.h>
#include <stdlib.h>

int a[100], n;

void quicksort(int left, int right)
{
    int i, j, t, temp;
    if(left>right)
        return;

    temp = a[left];
    i = left;
    j = right;

    while(i != j){
        while(a[j]>=temp && i<j)
            j--;
        while(a[i]>=temp && i<j)
            i++;

        if(i<j){
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }

    a[left] = a[i];
    a[i] = temp;

    quicksort(left, i-1);
    quicksort(i+1, right);
    }
    return;
}

int main()
{
    int i, j;

    scanf("%d", &n);//输入你要输入多少个数
    for(i=1; i<=n; i++){
        scanf("%d", &a[i]);
    }//分别将这些自己输入的数读取到数组中
    quicksort(1, n);


    for(j=1; j<=n; j++){
         printf("%d ", a[j]);
    }//将排好的数打印出来
    return 0;


}
