#include <bits/stdc++.h>
using namespace std;

#define MAX_K 1000
#define MAX_N 1000

int (* arr)[MAX_K + 1];
int n, k, temp_n = 0, temp_k = 0, maxLamp = 0;

int main()
{
    cin >> n;
    if(n < 1 || n > MAX_N){
        exit(EXIT_FAILURE);
    }

    arr = new int [n][MAX_K + 1];//多出的一个存放k

    temp_n = n;
    while(temp_n--){
        cin >> k;
        if(k < 1 || k > MAX_K){
            exit(EXIT_FAILURE);
        }
        arr[n - temp_n -1][0] = k;//每组数据第一个为k
        temp_k = k;
        while(temp_k--){
            cin >> arr[n - temp_n - 1][k - temp_k];//每组从下标1开始为灯泡的编号
        }
    }

    temp_n = 0;
    while(temp_n < n){
        if(arr[temp_n][0] > maxLamp){
            maxLamp = arr[temp_n][0];
        }
        temp_n++;
    }
    cout << maxLamp;

    return 0;
}
