#include <iostream>

using namespace std;

#define M_MAX 100000
#define N1ADDN2_MAX 100
#define MOD_VALUE 1000000007

int method = 0;
//no表示已经用过的v2元素
void calcMethod(int n1, int n2, int m, int *v1, int *v2)
{
    if(m <= 0){
        if(m == 0){
            method++;
        }
        return;
    }

    //用到n2的元素
    for(int i = 0; i < n2; i++){
        if(v2[i] != -1){
            int temp = v2[i];
            v2[i] = -1;
            calcMethod(n1, n2, m-temp, v1, v2);
        }
    }
    //不用到n2的元素
    for(int i = n1-1; i >= 0; i--){
        calcMethod(n1, n2, m-v1[i], v1, v2);
    }
}

int main(void)
{
    int n1=0, n2=0, m=0;
    cin >> n1 >> n2 >> m;
    if((n1+n2) < 0 || (n1+n2) > N1ADDN2_MAX){
        exit(EXIT_FAILURE);
    }

    int temp_n1 = n1, temp_n2 = n2;
    int * pN1_value = new int[n1];
    int * pN2_value = new int[n2];

    while(temp_n1){
        cin >> pN1_value[n1 - temp_n1];
        temp_n1--;
    }
    while(temp_n2){
        cin >> pN2_value[n2 - temp_n2];
        temp_n2--;
    }

    calcMethod(n1, n2, m, pN1_value, pN2_value);
    cout << method % MOD_VALUE;
    return 0;
}
