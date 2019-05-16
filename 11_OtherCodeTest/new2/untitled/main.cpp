#include <stdio.h>
#include <iostream>

#define MAX_T 100
#define UP_LIMIT 20000000000
#define DOWN_LIMIT 0

using namespace std;

typedef struct ballon{
    long red;
    long green;
    long blue;
}Ballon;

Ballon input[MAX_T] = {0};

long RgbMax(long r, long g, long b)
{
    long max = (r > g) ? r : g;
    max = (max > b) ? max : b;

    return max;
}
long RgbMin(long r, long g, long b)
{
    long min = (r < g) ? r : g;
    min = (min < b) ? min : b;

    return min;
}
int main(void)
{
    int n = 0, i = 0, temp = 0;
    cin >> n;
    if(n > 100){
        exit(EXIT_FAILURE);
    }

    temp = n;
    i = 0;
    while(temp--){
        cin >> input[i].red >> input[i].green >> input[i].blue;
        if(RgbMin(input[i].red, input[i].green, input[i].blue) > UP_LIMIT ||
                RgbMax(input[i].red, input[i].green, input[i].blue) < DOWN_LIMIT){
            exit(EXIT_FAILURE);
        }
        i++;
    }

    temp = i;
    i = 0;
    while(temp--){
        cout << (input[i].red + input[i].green + input[i].blue)/3 << endl;
        i++;
    }

    return 0;
}

