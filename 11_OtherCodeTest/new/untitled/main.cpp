#include<iostream>
#include<vector>

using namespace std;

int n, sum;
bool flag = false;

void calc(vector<int>& a, int pos, int part) {
    if(flag || part > sum)//flag为true或part已经超出则直接返回
        return;
    if (part == sum){//有满足条件的直接flag置为true并返回
        flag = true;
        return;
    }

    for(int i=pos; i<n; i++) {
        part += a[i];
        calc(a, i+1, part);
        if(flag){//计算完后再进行一次flag判断
            return;
        }
        part -= a[i];
    }
}

int main(void){
    cin >> n >> sum;

    if(n <= 0 || sum <= 0){
        exit(EXIT_FAILURE);
    }

    vector<int> a(n);

    for(int i=0; i<n; i++){
        cin >> a[i];
        if(a[i] < 0){
            exit(EXIT_FAILURE);
        }
    }

    calc(a, 0, 0);

    if(flag){
        cout << "perfect";
    }
    else{
        cout << "good";
    }

    return 0;
}
