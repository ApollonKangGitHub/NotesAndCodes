#include <iostream>

using namespace std;

int main()
{
    char str[] = "Programming with CPP!";

    for(int i = 0; i<=sizeof(str)/sizeof(str[0])-2; i++){
        cout.put(*(str+i));
    }
    cout.put('\n');
    for(int i = sizeof(str)/sizeof(str[0])-2; i>=0; i--){
        cout.put(*(str+i));
    }
    cout.put('\n');
    return 0;
}

